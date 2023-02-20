#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;
    struct node* next;
};
typedef struct node* node;

struct BT{
    node root;
};
typedef struct BT* BT;

struct queue{
    node head;
};
typedef struct queue* queue;

node create_node(int k){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    temp->key = k;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->next = NULL;
    return temp;
}
void enqueue_front(queue Q,node x){
    x->next = Q->head;
    Q->head = x;
}
void enqueue_back(queue Q,node x){
    node selected;
    selected = Q->head;
    if(selected != NULL){
        while(selected->next != NULL){
            selected = selected->next;
        }
        selected->next = x;
    }
    else{
        Q->head = x;
    }
}
node dequeue(queue Q){
    node temp = Q->head;
    Q->head = Q->head->next;
    return temp;
}

void insert(BT T,node x,queue Q){
    if(T->root == NULL){
        T->root = x;
        enqueue_back(Q,T->root);
        return;
    }
    else{
        while(1){
            node temp = dequeue(Q);
            if(temp->left != NULL && temp->right != NULL){
                enqueue_back(Q,temp->left);
                enqueue_back(Q,temp->right);
                break;
            }
            else if(temp->left == NULL){
                temp->left = x;
                enqueue_front(Q,temp);
                break;
            }
            else if(temp->right == NULL){
                temp->right = x;
                enqueue_back(Q,temp->left);
                enqueue_back(Q,temp->right);
                break;
            }
        }
    }
}

void print(node x){
    if(x == NULL){
        printf("( ) ");
        return;
    }
    else{
        printf("( ");
        printf("%d ",x->key);
        print(x->left);
        print(x->right);
        printf(") ");
    }
}

int main(){
    int k;
    char ch;
    BT T;
    T = (BT)malloc(sizeof(struct BT));
    T->root = NULL;
    queue Q;
    Q = (queue)malloc(sizeof(struct queue));
    Q->head = NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%d",&k);
                node x;
                x = create_node(k);
                insert(T,x,Q);
                break;
            }
            case 'p':{
                print(T->root);
                printf("\n");
                break;
            }
            case 'e':{
                return 0;
            }
        }
    }
}