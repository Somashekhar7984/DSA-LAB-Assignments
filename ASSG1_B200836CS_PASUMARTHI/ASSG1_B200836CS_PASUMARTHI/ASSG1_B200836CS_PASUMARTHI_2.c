#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
};
typedef struct node *node;
struct BT{
    node root;
};
typedef struct BT *BT;
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
void inorder(node x){
    if(x == NULL){
        return;
    }
    else{
        inorder(x->left);
        printf("%d ",x->key);
        inorder(x->right);
    }
}
void preorder(node x){
    if(x == NULL){
        return;
    }
    else{
        printf("%d ",x->key);
        preorder(x->left);
        preorder(x->right);
    }
}
void postorder(node x){
    if(x == NULL){
        return;
    }
    else{
        postorder(x->left);
        postorder(x->right);
        printf("%d ",x->key);
    }
}
node search(node x,int k){
    while(x != NULL && k != x->key){
        if(k < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    return x;
}
int level(node root,node x){
    int count = 1;
    while(root != NULL && x->key != root->key){
        if(x->key < root->key){
            root = root->left;
            count++;
        }
        else{
            root = root->right;
            count++;
        }
    }
    return count;
}
node min(node x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}
node max(node x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}
node successor(BT T,node x){
    node y;
    if(x->right != NULL){
        node z;
        z = (node)malloc(sizeof(struct node)); 
        z = min(x->right);
        return z;
    }
    y = x->parent;
    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    } 
    return y;
}
node predecessor(BT T,node x){
    node y;
    if(x->left != NULL){
        return max(x->left);
    }
    y = x->parent;
    while(y != NULL && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}
void transplant(BT T,node u,node v){
    if(u->parent == NULL){
        T->root = v; 
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != NULL){
        v->parent = u->parent;
    }
}
void delete(BT T,node z){
    node y;
    if(z->left == NULL){
        transplant(T,z,z->right);
    }
    else if(z->right == NULL){
        transplant(T,z,z->left);
    }
    else{
        y = min(z->right);
        if(y->parent != z){
            transplant(T,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T,z,y);
        y->left = z->left;
        y->left->parent = y;
    }
}
int main(){
    char ch;
    int k;
    BT T;
    T = (BT)malloc(sizeof(struct BT));
    T->root = NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'a':{
                scanf(" %d",&k);
                node w;
                w = create_node(k);
                insert(T,w);
                break;
            }
            case 'i':{
                inorder(T->root);
                printf("\n");
                break;
            }
            case 'p':{
                preorder(T->root);
                printf("\n");
                break;
            }
            case 't':{
                postorder(T->root);
                printf("\n");
                break;
            }
            case 'm':{
                node w;
                w = min(T->root);
                printf("%d\n",w->key);
                break;
            }
            case 'x':{
                node w;
                w = max(T->root);
                printf("%d\n",w->key);
                break;
            }
            case 'l':{
                scanf(" %d",&k);
                node w = search(T->root,k);
                if(w == NULL){
                    printf("-1\n");
                }
                else{
                    int l = level(T->root,w);
                    printf("%d\n",l);
                }
                break;
            }
            case 's':{
                 scanf(" %d",&k);
                 node y;
                 y = (node)malloc(sizeof(struct node));
                 y = search(T->root,k);
                 if(y == NULL){
                     printf("-1\n");
                 }
                 else{
                     printf("1\n");
                 }
                 break;
            }
            case 'u':{
                scanf(" %d",&k);
                node x,y;
                y = (node)malloc(sizeof(struct node));
                x = (node)malloc(sizeof(struct node));
                y = search(T->root,k);
                if(y == NULL){
                    printf("-1\n");
                }
                else{
                    x = successor(T,y);
                    if(x == NULL){
                        printf("-1\n");
                    }
                    else{
                        printf("%d\n",x->key);
                    }
                }
                break;
            }
            case 'r':{
                scanf(" %d",&k);
                node x,y;
                y = (node)malloc(sizeof(struct node));
                x = (node)malloc(sizeof(struct node));
                y = search(T->root,k);
                if(y == NULL){
                    printf("-1\n");
                }
                else{
                    x = predecessor(T,y);
                    if(x == NULL){
                        printf("-1\n");
                    }
                    else{
                        printf("%d\n",x->key);
                    }
                }
                break;
            }
            case 'd':{
                scanf(" %d",&k);
                node x;
                x = (node)malloc(sizeof(struct node));
                x = search(T->root,k);
                if(x == NULL){
                    printf("-1\n");
                }
                else{
                    delete(T,x);
                    printf("%d\n",x->key);
                }
                break;
            }
            case 'e':{
                return 0;
            }
        }
    }
    
}