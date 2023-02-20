#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int key;
	int height;
	struct node* left;
	struct node* right;
}node;

typedef struct avlTree{
	struct node* root;
}avlTree;


node* createNode(int key){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	newNode->height = 1;
	return newNode;
}


int max(int a, int b){
	return ((a>b)?a:b);
}


int height(node* n){
	if(n == NULL){
		return 0;
	}
	return n->height;
}


node* avlSearch(node* T,int k){
	if(T == NULL){
		return T;
	}
	if(T->key == k){
		return T;
	}else if(k < T->key){
		return avlSearch(T->left,k);
	}else if(k > T->key){
		return avlSearch(T->right,k);
	}
}


int avlBalanceFactor(node* T,int k){
	node* requiredNode = avlSearch(T,k);
	return (height(requiredNode->left) - height(requiredNode->right));
}


node* leftRotation(node* n){
	node* temp = n->right;
	node* trace = temp->left;
	temp->left = n;
	n->right = trace;
	n->height = max(height(n->left),height(n->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}


node* rightRotation(node* n){
	node* temp = n->left;
	node* trace = temp->right;
	temp->right = n;
	n->left = trace;
	n->height = max(height(n->left),height(n->right)) + 1;
	temp->height = max(height(temp->left),height(temp->right)) + 1;
	return temp;
}


node* avlInsert(node* T,int k){
	if(T == NULL){
		return createNode(k);
	}
	if(k < T->key){
		T->left = avlInsert(T->left,k);
	}else if(k > T->key){
		T->right = avlInsert(T->right,k);
	}else{
		return T;
	}
	
	T->height = max(height(T->left),height(T->right)) + 1;
	
	int bf;
	if(T == NULL){
		bf = 0;
	}else{
		bf = avlBalanceFactor(T,T->key);
	}
	
	
	//LL
	if(bf > 1 && k < T->left->key){
		return rightRotation(T);
	}else if(bf > 1 && k > T->left->key){
		T->left = leftRotation(T->left);
		return rightRotation(T);
	}else if(bf < -1 && k > T->right->key){
		return leftRotation(T);
	}else if(bf < -1 && k < T->right->key){
		T->right = rightRotation(T->right);
		return leftRotation(T);
	}

	
	return T;
}


node* minValue(node* n){
	if(n->left == NULL){
		return n;
	}
	node* temp = n;
	while(temp->left != NULL){
		temp = temp->left;
	}
	return temp;
}


node* avlDelete(node* T,int k){
	if(T == NULL){
		printf("FALSE\n");
		return T;
	}else if(k < T->key){
		T->left = avlDelete(T->left,k);
	}else if(k > T->key){
		T->right = avlDelete(T->right,k);
	}else{
		if(T->left == NULL){
			return T->right;
		}else if(T->right == NULL){
			return T->left;
		}else{
			node* minVal = minValue(T->right);
			T->key = minVal->key;
			T->right = avlDelete(T->right,minVal->key);
		}
	}

	T->height = max(height(T->left),height(T->right)) + 1;
	
	int bf;
	if(T == NULL){
		bf = 0;
	}else{
		bf = avlBalanceFactor(T,T->key);
	}


	if(bf > 1){
		if(avlBalanceFactor(T->left,T->left->key) >= 0){
			return rightRotation(T);
		}else{
			T->left = leftRotation(T->left);
			return rightRotation(T);
		}
	}else if(bf < -1){
		if(avlBalanceFactor(T->right,T->right->key) <= 0){
			return leftRotation(T);
		}else{
			T->right = rightRotation(T->right);
			return leftRotation(T);
		}
	}	
	return T;

	
}


//Print
void print(node* n){
	if(n != NULL){
		printf("( %d ",n->key);
		print(n->left);
		print(n->right);
		printf(") ");
	}else{
		printf("( ) ");
	}
}


//`i', `d', `s', `b', `p' and `e'
int main(){
	avlTree* avl = (avlTree*)malloc(sizeof(avlTree));
	avl->root = NULL;
	char ch;
	int x;
	int y;
	node* requiredNode;
	while(1){
		scanf("%c",&ch);
		switch(ch){
			case 'i':
				scanf("%d",&x);
				avl->root = avlInsert(avl->root,x);
				break;
			case 'd':
				scanf("%d",&x);
				if(avlSearch(avl->root,x) == NULL){
					printf("FALSE\n");
				}else{
					avl->root =  avlDelete(avl->root,x);
					printf("%d\n",x);	
				};
				break;
			case 's':
				scanf("%d",&x);
				requiredNode = avlSearch(avl->root,x);
				if(requiredNode == NULL){
					printf("FALSE\n");
				}else{
					printf("TRUE\n");
				}
				break;
			case 'b':
				scanf("%d",&x);
				if(avlSearch(avl->root,x) == NULL){
					printf("FALSE\n");
				}else{
					y = avlBalanceFactor(avl->root,x);
					printf("%d\n",y);	
				};
				break;
			case 'p':
				print(avl->root);
				printf("\n");
				break;
			case 'e':
				exit(0);
		}
	}
	return 0;
}
/*      test case 1
i 30
i 20
i 10
i 40
i -20
s 10
p
b 20
b 50
d 40
p
e

output 1
TRUE
( 20 ( 10 ( -20 ( ) ( ) ) ( ) ) ( 30 ( ) ( 40 ( ) ( ) ) ) )
0
FALSE
40
( 20 ( 10 ( -20 ( ) ( ) ) ( ) ) ( 30 ( ) ( ) ) )
*/
/*      Test case 4

i 0
i 100
i 399
i 529
i 823
i 1048
i 9832
i 10726
i 999999
p
s 99999
b 85496
d 12347
s 529
d 399
s 399
b 529
d 0
p
d 1036
p
e

*/

/*
        Test case 4 output
( 529 ( 100 ( 0 ( ) ( ) ) ( 399 ( ) ( ) ) ) ( 1048 ( 823 ( ) ( ) ) ( 10726 ( 9832 ( ) ( ) ) ( 999999 ( ) ( ) ) ) ) )
FALSE
FALSE
FALSE
TRUE
399
FALSE
-1
0
( 1048 ( 529 ( 100 ( ) ( ) ) ( 823 ( ) ( ) ) ) ( 10726 ( 9832 ( ) ( ) ) ( 999999 ( ) ( ) ) ) )
FALSE
( 1048 ( 529 ( 100 ( ) ( ) ) ( 823 ( ) ( ) ) ) ( 10726 ( 9832 ( ) ( ) ) ( 999999 ( ) ( ) ) ) )
*/