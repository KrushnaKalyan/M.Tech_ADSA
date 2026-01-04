#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct FibNode {
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

FibNode* create_node(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibHeap* create_heap() {
    FibHeap *heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

void fib_heap_insert(FibHeap *H, FibNode *x) {
    if (H->min == NULL) {
        H->min = x;
    } else {
        x->left = H->min;
        x->right = H->min->right;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n++;
}

void fib_heap_link(FibHeap *H, FibNode *y, FibNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate(FibHeap *H) {
    int D = (int)(log(H->n) / log(2)) + 2;
    FibNode **A = (FibNode**)calloc(D, sizeof(FibNode*));

    FibNode *w = H->min;
    int num_roots = 0;

    FibNode *x = w;
    do {
        num_roots++;
        x = x->right;
    } while (x != w);

    while (num_roots > 0) {
        int d = x->degree;
        FibNode *next = x->right;

        while (A[d] != NULL) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *temp = x; x = y; y = temp;
            }
            fib_heap_link(H, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;

        x = next;
        num_roots--;
    }

    H->min = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i] != NULL) {
            if (H->min == NULL) {
                H->min = A[i];
                H->min->left = H->min->right = H->min;
            } else {
                A[i]->left = H->min;
                A[i]->right = H->min->right;
                H->min->right->left = A[i];
                H->min->right = A[i];
                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }
    free(A);
}

FibNode* fib_heap_extract_min(FibHeap *H) {
    FibNode *z = H->min;
    if (z != NULL) {
        if (z->child != NULL) {
            FibNode *child = z->child;
            do {
                child->parent = NULL;
                child = child->right;
            } while (child != z->child);

            FibNode *zleft = z->left;
            FibNode *zchild_left = z->child->left;

            zleft->right = z->child;
            z->child->left = zleft;
            zchild_left->right = z->right;
            z->right->left = zchild_left;
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right)
            H->min = NULL;
        else {
            H->min = z->right;
            consolidate(H);
        }
        H->n--;
    }
    return z;
}

void cut(FibHeap *H, FibNode *x, FibNode *y) {
    if (x->right == x)
        y->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }
    y->degree--;

    x->left = H->min;
    x->right = H->min->right;
    H->min->right->left = x;
    H->min->right = x;

    x->parent = NULL;
    x->mark = 0;
}

void cascading_cut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z != NULL) {
        if (y->mark == 0)
            y->mark = 1;
        else {
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}

void fib_heap_decrease_key(FibHeap *H, FibNode *x, int k) {
    if (k > x->key) {
        printf("Error: new key is greater than current key.\n");
        return;
    }

    x->key = k;
    FibNode *y = x->parent;

    if (y != NULL && x->key < y->key) {
        cut(H, x, y);
        cascading_cut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}

void fib_heap_delete(FibHeap *H, FibNode *x) {
    fib_heap_decrease_key(H, x, INT_MIN);
    fib_heap_extract_min(H);
}

void print_tree(FibNode *node, int depth) {
    if (node == NULL) return;

    FibNode *start = node;
    do {
        // Indentation for levels
        for (int i = 0; i < depth; i++)
            printf("   ");

        // Print node key
        printf("%d\n", start->key);

        // Print children with increased depth
        if (start->child != NULL)
            print_tree(start->child, depth + 1);

        start = start->right;
    } while (start != node);
}

void print_heap(FibHeap *H) {
    if (H->min == NULL) {
        printf("Heap is empty.\n");
        return;
    }

    printf("\n--- Fibonacci Heap Structure ---\n");
    print_tree(H->min, 0);
    printf("--------------------------------\n");
}


/* ---- HELPER TO SEARCH NODE (for user operations) ---- */

FibNode* search_node(FibNode *root, int key) {
    if (root == NULL) return NULL;

    FibNode *start = root;
    do {
        if (start->key == key) return start;

        FibNode *res = search_node(start->child, key);
        if (res) return res;

        start = start->right;
    } while (start != root);

    return NULL;
}

/* ----------------- MAIN MENU ----------------- */

int main() {
    FibHeap *H = create_heap();
    int choice, key, newkey;

    while (1) {
        printf("\n==== Fibonacci Heap Menu ====\n");
        printf("1. Insert\n");
        printf("2. Find Minimum\n");
        printf("3. Extract Minimum\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Print\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);
            fib_heap_insert(H, create_node(key));
            printf("Inserted %d\n", key);
            break;

        case 2:
            if (H->min)
                printf("Minimum = %d\n", H->min->key);
            else
                printf("Heap is empty.\n");
            break;

        case 3: {
            FibNode *m = fib_heap_extract_min(H);
            if (m)
                printf("Extracted Min = %d\n", m->key);
            else
                printf("Heap is empty.\n");
            break;
        }
        case 4:
            printf("Enter key to decrease: ");
            scanf("%d", &key);
            printf("Enter new key: ");
            scanf("%d", &newkey);

            FibNode *node = search_node(H->min, key);
            if (!node) printf("Key not found.\n");
            else {
                fib_heap_decrease_key(H, node, newkey);
                printf("Key decreased.\n");
            }
            break;

        case 5:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            node = search_node(H->min, key);
            if (!node) printf("Key not found.\n");
            else {
                fib_heap_delete(H, node);
                printf("Key deleted.\n");
            }
            break;
            
        case 6:
            print_heap(H);
            break;
    
        case 7:
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
