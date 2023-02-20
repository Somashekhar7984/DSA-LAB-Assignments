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
    temp->right = NULL;
    temp->left = NULL;
    temp->parent = NULL;
    return temp;
}

int no_of_nodes(node root){
    if(root == NULL){
        return 0;
    }
    int left_tree = no_of_nodes(root->left);
    int right_tree = no_of_nodes(root->right);
    return (1 + left_tree + right_tree);
}

int isBST(node root,int min,int max){
    if(root == NULL){
        return 1;
    }
    if(root->key<min || root->key >max){
        return 0;
    }
    
    if(isBST(root->left,min,root->key) && isBST(root->right,root->key,max)){
        return 1;
    }
    return 0;
}

int largest_BST(node root){
    if(isBST(root,INT_MIN,INT_MAX)){
        return no_of_nodes(root);
    }
    int left = largest_BST(root->left);
    int right = largest_BST(root->right);
    if(left > right){
        return left;
    }
    else{
        return right;
    }

}

void convert_to_binary_tree(BT T, char s[]){
	node temp = NULL;
	int high = 1;
	int neg = 1;
	int i = 0;
	while(s[i] != '\0'){
		neg = 1;
		if(s[i] == '('){
    		  i = i+2;
    			if(s[i] == ')'){
    				if(s[i+1] == '\0'){
    					i++;
    				}
                    else{
    					i = i+2;
    					high = 0;
    				}
    				continue;
    			}
                else{
    				if(s[i] == '-'){
    					neg = -1;
    					i++;
    				}
    				char y = s[i];
    				int num = y - '0';
    				while(1){
    					if(s[i+1] != ' '){
    						i++;
                            num = num*10 + (int)(s[i] - '0');
    					}
                        else{
    						break;
    					}	
    				}
    				node x = create_node((neg*num));
    				if(temp == NULL){
    					T->root = x;
    					temp = T->root;
    				}
    				else if(temp->left == NULL && high == 1){
    					temp->left = x;
    					x->parent = temp;
    					temp = x;
    				}
                    else if(temp->right == NULL){
    					temp->right = x;
    					x->parent = temp;
    					temp = x;
    					high = 1;
    				}
    				i = i+2;
    				continue;	
    			}
		}
        else if(s[i] == ')'){
			if(temp->parent != NULL){
				temp = temp->parent;
			}
			if(s[i+1] == '\0'){
				i++;
			}else{
				i = i+2;
			}
			continue;
		}
	}
}

int main(){
    char str[100000];
    scanf("%[^\n]s",str);
    BT T;
    T = (BT)malloc(sizeof(struct BT));
    T->root = NULL;
    convert_to_binary_tree(T,str);
    int size = largest_BST(T->root);
    printf("%d",size);
    return 0;
}

//( 10 ( 15 ( 12 ( ) ( ) ) ( 20 ( ) ( ) ) ) ( 8 ( 5 ( ) ( ) ) ( 2 ( ) ( ) ) ) )
/*
                    10
                15       8
            12     20  5    2
*/