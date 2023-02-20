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
node LCA(node root,int n1,int n2){
    if(root == NULL){
        return NULL;
    }
    if(root->key == n1 || root->key == n2){
        return root;
    }
    node left_lca = LCA(root->left,n1,n2);
    node right_lca = LCA(root->right,n1,n2);
    if(left_lca && right_lca){
        return root;
    }
    if(left_lca != NULL){
        return left_lca;
    }
    else{
        return right_lca;
    }
}
int level(node root,node x){
    if(root == NULL){
        return -1;
    }
    int dis = -1;
    if(root->key == x->key){
        return dis + 1;
    }
    dis = level(root->left,x);
    if(dis >= 0){
        return dis + 1;
    }
    dis = level(root->right,x);
    if(dis >= 0){
        return dis + 1;
    }
    else{
        return dis;
    }
}
int dist(rbTree T,node start,node end){
    node lca = LCA(T->root,start->key,end->key);
    int d1 = -1;
    d1 = level(T->root,start);
    int d2 = -1;
    d2 = level(T->root,end);
    int r = -1;
    r = level(T->root,lca);
    int D = d1 + d2 - (2*r);
    return D;
}
void search(rbTree T,node root,node main_node,int* flag,int dis){
    if(root == NULL){
        return;
    }
    else{
        if(dist(T,root,main_node) == dis){
            if(root->colour == 'B'){
                *flag = 1;
            }
        }
        search(T,root->left,main_node,flag,dis);
        search(T,root->right,main_node,flag,dis);
    }
}
void inorder_traversal(rbTree T,node root,int* flag,int* count,int dis){
    if(root != NULL){
        inorder_traversal(T,root->left,flag,count,dis);
        node main_node = root;
        node root1 = T->root;
        search(T,root1,main_node,flag,dis);
        if(*flag == 1){
            *count = *count + 1;
        }
        *flag = 0;
        inorder_traversal(T,root->right,flag,count,dis);   
    }
    else{
        return;
    }
}
int main(){
    int dis;
    scanf("%d",&dis);
    int n;
    scanf("%d",&n);
    int k;
    rbTree T = (rbTree)malloc(sizeof(struct rbTree));
    node root = (node)malloc(sizeof(struct node));
    root->colour = 'B';
    root->left = NULL;
    root->right = NULL;
    T->root = root;
    for(int i = 0;i<n;i++){
        scanf("%d",&k);
        node l = create_node(k,root);
        T->root = rbInsert(T->root,l,root);
        if(T->root->colour == 'R'){
            T->root->colour = 'B';
        }
    }
    //print(T->root,root);
    //printf("\n");
    int flag = 0;
    int count = 0;
    inorder_traversal(T,T->root,&flag,&count,dis);
    printf("%d\n",count);
    return 0;
}