#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;
};
typedef struct node* node;
struct BT{
    node root;
};
typedef struct BT* BT;

node create_node(int k){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->key = k;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}
void insert(BT T,node z){
    node x,y;
    y = NULL;
    x = T->root;
    while(x != NULL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        T->root = z;
    }
    else if(z->key<y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
}

int height(node root){
    if(root == NULL){
        return 0;
    }
    else{
        int hl = height(root->left);
        int hr = height(root->right);
        if(hl > hr){
            return hl + 1;
        }
        else{
            return hr + 1;
        }
    }
}
void check_AVL(node root,int* flag){
    if(root == NULL){
        return;
    }
    else{
        int bf = (height(root->left) - height(root->right));
        if(bf > 1 || bf < -1){
            *flag = 0;
        }
        check_AVL(root->left,flag);
        check_AVL(root->right,flag);
    }
}
int main(){
    int k;
    char ch;
    BT T;
    T = (BT)malloc(sizeof(struct BT));
    T->root = NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%d",&k);
                node x = create_node(k);
                insert(T,x);
                break;
            }
            case 'c':{
                int flag = 1;
                check_AVL(T->root,&flag);
                printf("%d\n",flag);
                break;
            }
            case 't':{
                return 0;
            }
        }
    }
}