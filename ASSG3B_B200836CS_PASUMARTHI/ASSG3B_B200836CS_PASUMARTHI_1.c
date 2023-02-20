#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

struct node{
    int key;
    char colour;
    struct node* left;
    struct node* right;
};
typedef struct node* node;

struct rbTree{
    struct node* root;
};
typedef struct rbTree* rbTree;

node create_node(int key,node root){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    temp->key = key;
    temp->colour = 'R';
    temp->left = root;
    temp->right = root;
    return temp;
}
node left_rotate(node n){
    node temp = n->right;
    node track = temp->left;
    temp->left = n;
    n->right = track;
    return temp;
}
node right_rotate(node n){
    node temp = n->left;
    node track = temp->right;
    temp->right = n;
    n->left = track;
    return temp;
}
node rbInsert(node T,node x,node root){
    if(T == root){
        return x;
    }
    else{
        if(x->key < T->key){
			T->left = rbInsert(T->left,x,root);
			if(T->left->colour == 'R'){
				if(T->left->left->colour == 'R' || T->left->right->colour == 'R'){
					if(T->right->colour != 'R'){
						if(T->left->left->colour == 'R'){
							T = right_rotate(T);
							T->right->colour = 'R';
							T->colour = 'B';
							return T;
						}else{
							T->left = left_rotate(T->left);
							T = right_rotate(T);
							T->right->colour = 'R';
							T->colour = 'B';
							return T;
						}
					}else if(T->right->colour == 'R'){
						T->left->colour = 'B';
						T->right->colour = 'B';
						T->colour = 'R';
						return T;
					}
				}
			}
			return T;
        }
        else{
            T->right = rbInsert(T->right,x,root);
			if(T->right->colour == 'R'){
				if(T->right->left->colour == 'R' || T->right->right->colour == 'R'){
					if(T->left->colour != 'R'){
						if(T->right->right->colour == 'R'){
							T = left_rotate(T);
							T->left->colour = 'R';
							T->colour = 'B';
							return T;
						}else{
							T->right = right_rotate(T->left);
							T = left_rotate(T);
							T->left->colour = 'R';
							T->colour = 'B';
							return T;
						}
					}else if(T->left->colour == 'R'){
						T->left->colour = 'B';
						T->right->colour = 'B';
						T->colour = 'R';
						return T;
					}
				}
			}
        }
        return T;
    }    
    return T;
}
void print(node root,node x){
    if(root != NULL && root != x){
        printf("( %d %c ",root->key,root->colour);
        print(root->left,x);
        print(root->right,x);
        printf(") ");
    }
    else{
        printf("( ) ");
    }
}
int main(){
    int k;
    rbTree T = (rbTree)malloc(sizeof(struct rbTree));
    node root = (node)malloc(sizeof(struct node));
    root->colour = 'B';
    root->left = NULL;
    root->right = NULL;
    T->root = root;
    while(1){
        int l = scanf("%d",&k);
        if(l == 1){
            node x = create_node(k,root);
            T->root = rbInsert(T->root,x,root);
            if(T->root->colour == 'R'){
                T->root->colour = 'B';
            }
            print(T->root,root);
            printf("\n");
        }
        else if(l == 0){
            break;
        }
    }
    return 0;
}
/*
25
18
50
80
12
100
34
t

*/