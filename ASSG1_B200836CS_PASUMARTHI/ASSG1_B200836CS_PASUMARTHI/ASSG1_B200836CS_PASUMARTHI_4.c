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
    T = (BT)malloc(sizeof(struct node));
    T->root = NULL;
    convert_to_binary_tree(T,str);
    int n1,n2;
    scanf("%d %d",&n1,&n2);
    node ancestor = LCA(T->root,n1,n2);
    printf("%d",ancestor->key);
    return 0;
}