#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
struct node{
    int key;
    int height;
    struct node* left;
    struct node* right;
};
typedef struct node* node;

struct AVL_tree{
    node root;
};
typedef struct AVL_tree* AVL_tree;

node create_node(int key){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->key = key;
    temp->height = 1;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int height(node n){
    if(n == NULL){
        return 0;
    }
    return n->height;
}
node AVL_search(node root,int k){
    if(root == NULL){
        return root;
    }
    if(root->key == k){
        return root;
    }
    else if(k < root->key){
        return AVL_search(root->left,k);
    }
    else if(k > root->key){
        return AVL_search(root->right,k);
    }
}

int AVL_bf(node root,int k){
    node temp = AVL_search(root,k);
    int bf = height(temp->left) - height(temp->right);// Here a change
    return bf;
}

node left_rotate(node n){
    node temp = n->right;
    node track = temp->left;        // Here a change (n->left changed to temp->left)
    temp->left = n;
    n->right = track;
    int hl = height(n->left);
    int hr = height(n->right);
    if(hl > hr){
        n->height = hl + 1;
    }
    else{
        n->height = hr + 1;
    }
    int htl = height(temp->left);
    int htr = height(temp->right);
    if(htl > htr){
        temp->height = htl + 1;
    }
    else{
        temp->height = htr + 1;
    }
    return temp;
}

node right_rotate(node n){
    node temp = n->left;
    node track = temp->right;       // Here a Change (n->right is changed to temp->right)
    temp->right = n;
    n->left = track; 
    int hl = height(n->left);
    int hr = height(n->right);
    if(hl > hr){
        n->height = hl + 1;
    }
    else{
        n->height = hr + 1;
    }
    int htl = height(temp->left);
    int htr = height(temp->right);
    if(htl > htr){
        temp->height = htl + 1;
    }
    else{
        temp->height = htr + 1;
    }   
    return temp;
}
node AVL_insert(node root,int k){
    if(root == NULL){
        node x = create_node(k);
        return x;
    }
    if(k < root->key){
        root->left = AVL_insert(root->left,k);
    }
    else if(k > root->key){
        root->right = AVL_insert(root->right,k);
    }
    else{
        return root;
    }
    // Adjusting the height after insertion
    int hl = height(root->left);
    int hr = height(root->right);
    if(hl > hr){
        root->height = hl + 1;
    }
    else{
        root->height = hr + 1;
    }
    // balance factor
    int bf;
    if(root == NULL){
        bf = 0;
    }
    else{
        bf = AVL_bf(root,root->key);
    }
    // Doing rotations after insertion if required
    if(bf > 1 && k < root->left->key){
        return right_rotate(root);
    }
    else if(bf > 1 && k > root->left->key){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    else if(bf < -1 && k > root->right->key){ // Here one change (root->left->key changed to root->right->key)
        return left_rotate(root);
    }
    else if(bf < -1 && k < root->right->key){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}
node min(node n){
    if(n->left == NULL){
        return n;
    }
    node temp = n;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

node AVL_delete(node root,int k){
    if(root == NULL){
        printf("FALSE\n");
        return root;
    }
    else if(k < root->key){
        root->left = AVL_delete(root->left,k);
    }
    else if(k > root->key){
        root->right = AVL_delete(root->right,k);
    }
    else{
        if(root->left == NULL){
            return root->right;
        }
        else if(root->right == NULL){
            return root->left;
        }
        else{
            node min_node = min(root->right);
            root->key = min_node->key;
            root->right = AVL_delete(root->right,min_node->key);
        }
    }

    int hl = height(root->left);
    int hr = height(root->right);
    if(hl > hr){
        root->height = hl + 1;
    }
    else{
        root->height = hr + 1;
    }

    int bf;
    if(root == NULL){
        bf = 0;
    }
    else{
        bf = AVL_bf(root,root->key);
    }

    if(bf > 1){
        if(AVL_bf(root->left,root->left->key) >= 0){
            return right_rotate(root);
        }
        else{
            root->left = left_rotate(root->left);
            return right_rotate(root);
        }
    }
    else if(bf < -1){
        if(AVL_bf(root->right,root->right->key) <= 0){
            return left_rotate(root);
        }
        else{
            root->right = right_rotate(root->right);
            return left_rotate(root);
        }
    }

    return root;
}
void print(node root){
    if(root != NULL){
        printf("( %d ",root->key);
        print(root->left);
        print(root->right);
        printf(") ");
    }
    else{
        printf("( ) ");
    }
}
int main(){
    char ch;
    int k;
    AVL_tree AVL;
    AVL = (AVL_tree)malloc(sizeof(struct AVL_tree));
    AVL->root = NULL;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%d",&k);
                AVL->root = AVL_insert(AVL->root,k);
                break;
            }
            case 'd':{
                scanf("%d",&k);
                if(AVL_search(AVL->root,k) == NULL){
                    printf("FALSE\n");
                }
                else{
                    AVL->root = AVL_delete(AVL->root,k);
                    printf("%d\n",k);
                }
                break;
            }
            case 's':{
                scanf("%d",&k);
                node x = AVL_search(AVL->root,k);
                if(x == NULL){
                    printf("FALSE\n");
                }
                else{
                    printf("TRUE\n");
                }
                break;
            }
            case 'b':{
                scanf("%d",&k);
                if(AVL_search(AVL->root,k) == NULL){
                    printf("FALSE\n");
                }
                else{
                    int bf = AVL_bf(AVL->root,k);
                    printf("%d\n",bf);
                }
                break;
            }
            case 'p':{
                print(AVL->root);
                printf("\n");
                break;
            }
            case 'e':{
                return 0;
            }
        }
    }
}
/*
i 4
i 6
i 3
i 2
i 1
s 2
p
b 4
d 3
p
e

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