//Q4-b B-Tree

#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode *C[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf);
void traverse(BTreeNode* root);
BTreeNode* insert(BTreeNode* root,int k);
BTreeNode* deleteNode(BTreeNode* root,int k);
void removeFromNonLeaf(BTreeNode* root,int idx);
void fill(BTreeNode* root,int idx);
void borrowFromPrev(BTreeNode* root,int idx);
void borrowFromNext(BTreeNode* root,int idx);
void merge(BTreeNode* root,int idx);

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    int i;
    node->leaf = leaf;
    node->n = 0;
    for(i=0;i<2*T;i++) node->C[i]=NULL;
    return node;
}

void traverse(BTreeNode* root) {
    int i;
    if(root!=NULL) {
        for(i=0;i<root->n;i++) {
            if(!root->leaf) traverse(root->C[i]);
            printf("%d ",root->keys[i]);
        }
        if(!root->leaf) traverse(root->C[i]);
    }
}

BTreeNode* search(BTreeNode* root, int k) {
    int i=0;
    while(i<root->n && k>root->keys[i]) i++;
    if(i<root->n && k==root->keys[i]) return root;
    if(root->leaf) return NULL;
    return search(root->C[i], k);
}

void splitChild(BTreeNode* x, int i) {
    BTreeNode* y=x->C[i];
    BTreeNode* z=createNode(y->leaf);
    int j;
    z->n=T-1;
    for(j=0;j<T-1;j++) z->keys[j]=y->keys[j+T];
    if(!y->leaf) {
        for(j=0;j<T;j++) z->C[j]=y->C[j+T];
    }
    y->n=T-1;
    for(j=x->n;j>=i+1;j--) x->C[j+1]=x->C[j];
    x->C[i+1]=z;
    for(j=x->n-1;j>=i;j--) x->keys[j+1]=x->keys[j];
    x->keys[i]=y->keys[T-1];
    x->n+=1;
}

void insertNonFull(BTreeNode* x,int k) {
    int i=x->n-1;
    if(x->leaf) {
        while(i>=0 && k<x->keys[i]) {
            x->keys[i+1]=x->keys[i];
            i--;
        }
        x->keys[i+1]=k;
        x->n+=1;
    } else {
        while(i>=0 && k<x->keys[i]) i--;
        i++;
        if(x->C[i]->n==2*T-1) {
            splitChild(x,i);
            if(k>x->keys[i]) i++;
        }
        insertNonFull(x->C[i],k);
    }
}

BTreeNode* insert(BTreeNode* root,int k) {
    if(root==NULL) {
        root=createNode(1);
        root->keys[0]=k;
        root->n=1;
        return root;
    }
    if(root->n==2*T-1) {
        BTreeNode* s=createNode(0);
        s->C[0]=root;
        splitChild(s,0);
        int i;
        if(k>s->keys[0]) i=1; else i=0;
        insertNonFull(s->C[i],k);
        return s;
    } else {
        insertNonFull(root,k);
        return root;
    }
}

int findKey(BTreeNode* root,int k) {
    int idx=0;
    while(idx<root->n && root->keys[idx]<k) idx++;
    return idx;
}

void removeFromLeaf(BTreeNode* root,int idx) {
    int i;
    for(i=idx+1;i<root->n;i++) root->keys[i-1]=root->keys[i];
    root->n--;
}

int getPredecessor(BTreeNode* root,int idx) {
    BTreeNode* cur=root->C[idx];
    while(!cur->leaf) cur=cur->C[cur->n];
    return cur->keys[cur->n-1];
}

int getSuccessor(BTreeNode* root,int idx) {
    BTreeNode* cur=root->C[idx+1];
    while(!cur->leaf) cur=cur->C[0];
    return cur->keys[0];
}

void removeFromNonLeaf(BTreeNode* root,int idx) {
    int k=root->keys[idx];
    if(root->C[idx]->n>=T) {
        int pred=getPredecessor(root,idx);
        root->keys[idx]=pred;
        root->C[idx]=deleteNode(root->C[idx],pred);
    } else if(root->C[idx+1]->n>=T) {
        int succ=getSuccessor(root,idx);
        root->keys[idx]=succ;
        root->C[idx+1]=deleteNode(root->C[idx+1],succ);
    } else {
        merge(root,idx);
        root->C[idx]=deleteNode(root->C[idx],k);
    }
}

void borrowFromPrev(BTreeNode* root,int idx) {
    BTreeNode* child=root->C[idx];
    BTreeNode* sibling=root->C[idx-1];
    int i;
    for(i=child->n-1;i>=0;i--) child->keys[i+1]=child->keys[i];
    if(!child->leaf) {
        for(i=child->n;i>=0;i--) child->C[i+1]=child->C[i];
    }
    child->keys[0]=root->keys[idx-1];
    if(!child->leaf) child->C[0]=sibling->C[sibling->n];
    root->keys[idx-1]=sibling->keys[sibling->n-1];
    child->n+=1;
    sibling->n-=1;
}

void borrowFromNext(BTreeNode* root,int idx) {
    BTreeNode* child=root->C[idx];
    BTreeNode* sibling=root->C[idx+1];
    int i;
    child->keys[child->n]=root->keys[idx];
    if(!child->leaf) child->C[child->n+1]=sibling->C[0];
    root->keys[idx]=sibling->keys[0];
    for(i=1;i<sibling->n;i++) sibling->keys[i-1]=sibling->keys[i];
    if(!sibling->leaf) {
        for(i=1;i<=sibling->n;i++) sibling->C[i-1]=sibling->C[i];
    }
    child->n+=1;
    sibling->n-=1;
}

void merge(BTreeNode* root,int idx) {
    BTreeNode* child=root->C[idx];
    BTreeNode* sibling=root->C[idx+1];
    int i;
    child->keys[T-1]=root->keys[idx];
    for(i=0;i<sibling->n;i++) child->keys[i+T]=sibling->keys[i];
    if(!child->leaf) {
        for(i=0;i<=sibling->n;i++) child->C[i+T]=sibling->C[i];
    }
    for(i=idx+1;i<root->n;i++) root->keys[i-1]=root->keys[i];
    for(i=idx+2;i<=root->n;i++) root->C[i-1]=root->C[i];
    child->n+=sibling->n+1;
    root->n--;
    free(sibling);
}

void fill(BTreeNode* root,int idx) {
    if(idx!=0 && root->C[idx-1]->n>=T) borrowFromPrev(root,idx);
    else if(idx!=root->n && root->C[idx+1]->n>=T) borrowFromNext(root,idx);
    else {
        if(idx!=root->n) merge(root,idx);
        else merge(root,idx-1);
    }
}

BTreeNode* deleteNode(BTreeNode* root,int k) {
    int idx=findKey(root,k);
    if(idx<root->n && root->keys[idx]==k) {
        if(root->leaf) removeFromLeaf(root,idx);
        else removeFromNonLeaf(root,idx);
    } else {
        if(root->leaf) return root;
        int flag=(idx==root->n)?1:0;
        if(root->C[idx]->n<T) fill(root,idx);
        if(flag && idx>root->n) root->C[idx-1]=deleteNode(root->C[idx-1],k);
        else root->C[idx]=deleteNode(root->C[idx],k);
    }
    if(root->n==0) {
        BTreeNode* tmp=root;
        if(root->leaf) root=NULL;
        else root=root->C[0];
        free(tmp);
    }
    return root;
}

int main() {
    BTreeNode* root=NULL;
    int choice,key;
    while(1) {
        printf("\n1.Insert\n2.Delete\n3.Traverse\n4.Exit\nEnter choice: ");
        scanf("%d",&choice);
        if(choice==1) {
            printf("Enter key to insert: ");
            scanf("%d",&key);
            root=insert(root,key);
        } else if(choice==2) {
            printf("Enter key to delete: ");
            scanf("%d",&key);
            root=deleteNode(root,key);
        } else if(choice==3) {
            printf("B-Tree: ");
            traverse(root);
            printf("\n");
        } else break;
    }
    return 0;
}


