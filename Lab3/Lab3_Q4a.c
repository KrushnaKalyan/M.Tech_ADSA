//Q4-a  AVL Tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *n) {
    if(n == NULL) return 0;
    return n->height;
}

Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Node *n) {
    if(n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* insert(Node* node, int key) {
    if(node == NULL) return createNode(key);
    if(key < node->data) node->left = insert(node->left, key);
    else if(key > node->data) node->right = insert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if(balance > 1 && key < node->left->data) return rightRotate(node);
    if(balance < -1 && key > node->right->data) return leftRotate(node);
    if(balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while(current->left != NULL) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if(root == NULL) return root;
    if(key < root->data) root->left = deleteNode(root->left, key);
    else if(key > root->data) root->right = deleteNode(root->right, key);
    else {
        if((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if(temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if(root == NULL) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if(balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if(balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrder(Node* root) {
    if(root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if(root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, key;
    while(1) {
        printf("\n1.Insert\n2.Delete\n3.Preorder\n4.Inorder\n5.Exit\nEnter choice: ");
        scanf("%d", &choice);
        if(choice == 1) {
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
        } else if(choice == 2) {
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
        } else if(choice == 3) {
            printf("Preorder: ");
            preOrder(root);
            printf("\n");
        } else if(choice == 4) {
            printf("Inorder: ");
            inOrder(root);
            printf("\n");
        } else break;
    }
    return 0;
}

