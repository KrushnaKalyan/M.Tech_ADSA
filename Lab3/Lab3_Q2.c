//Q2 BST

#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left,*right;
};

struct Node* createNode(int value){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=value;
    newNode->left=newNode->right=NULL;
    return newNode;
}

struct Node* insert(struct Node* root,int value){
    if(root==NULL) return createNode(value);
    if(value<root->data) root->left=insert(root->left,value);
    else if(value>root->data) root->right=insert(root->right,value);
    return root;
}

struct Node* minValueNode(struct Node* node){
    struct Node* current=node;
    while(current&&current->left!=NULL) current=current->left;
    return current;
}

struct Node* deleteNode(struct Node* root,int key){
    if(root==NULL) return root;
    if(key<root->data) root->left=deleteNode(root->left,key);
    else if(key>root->data) root->right=deleteNode(root->right,key);
    else{
        if(root->left==NULL){
            struct Node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL){
            struct Node* temp=root->left;
            free(root);
            return temp;
        }
        struct Node* temp=minValueNode(root->right);
        root->data=temp->data;
        root->right=deleteNode(root->right,temp->data);
    }
    return root;
}

void inorder(struct Node* root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root){
    if(root!=NULL){
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

int main(){
    struct Node* root=NULL;
    int n,i,val,del,newval;
    printf("Enter number of nodes: ");
    scanf("%d",&n);
    printf("Enter values: ");
    for(i=0;i<n;i++){
        scanf("%d",&val);
        root=insert(root,val);
    }
    printf("Inorder traversal: ");
    inorder(root);
    printf("\nPreorder traversal: ");
    preorder(root);
    printf("\nPostorder traversal: ");
    postorder(root);
    printf("\nEnter value to delete: ");
    scanf("%d",&del);
    root=deleteNode(root,del);
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\nEnter a new value to insert: ");
    scanf("%d",&newval);
    root=insert(root,newval);
    printf("Inorder after new insertion: ");
    inorder(root);
    printf("\nPreorder after new insertion: ");
    preorder(root);
    printf("\nPostorder after new insertion: ");
    postorder(root);
    return 0;
}

