#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<limits.h>
struct node{
    int key;
    int degree;
    struct node* parent;
    struct node* sibling;
    struct node* child;
};
typedef struct node* node;
struct heap{
    node root;
};
typedef struct heap* heap;
node create_node(int k){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->key = k;
    temp->degree = 0;
    temp->child = NULL;
    temp->parent = NULL;
    temp->sibling = NULL;
    return temp;
}
heap make_heap(){
    heap H = malloc(sizeof(struct heap));
    H->root = NULL;
    return H;
}

node* createqueue(int* front,int* rear)
{
    node* Q =(node*)malloc(sizeof(node)*1000000);
    *front = 0;
    *rear =0;
    return Q;
}
void enqueue(node* Q,int* rear,node z)
{
    Q[*rear]=z;
    (*rear)++;
}
node dequeue(node* Q,int* front)
{
    (*front)++;
    return Q[*front-1];
}
void print(node H){
    int front;
    int rear;
    node* Q = createqueue(&front,&rear);
    node temp = H;
    node x;
    while(temp != NULL){
        while(temp != NULL){
            printf("%d ",temp->key);
            x = temp->child;
            if(x != NULL){
                enqueue(Q,&rear,x);
            }
            temp = temp->sibling;
        }
        temp = dequeue(Q,&front);
    }
}
node binomial_heap_merge(heap H1,heap H2){
    if(H1->root == NULL){
        return H2->root;
    }
    if(H2->root == NULL){
        return H1->root;
    }
    node head;
    node tail;
    node track_H1 = H1->root;
    node track_H2 = H2->root;
    if(H1->root->degree <= H2->root->degree){
        head = H1->root;
        track_H1 = track_H1->sibling;
    }
    else{
        head = H2->root;
        track_H2 = track_H2->sibling;
    }
    tail = head;
    while(track_H1 != NULL && track_H2 != NULL){
        if(track_H1->degree <= track_H2->degree){
            tail->sibling = track_H1;
            track_H1 = track_H1->sibling;
        }
        else{
            tail->sibling = track_H2;
            track_H2 = track_H2->sibling;
        }
        tail = tail->sibling;
    }
    if(track_H1 == NULL){
        tail->sibling = track_H2;
    }
    else{
        tail->sibling = track_H1;
    }
    return head;
}
node binomial_heap_union(heap H1,heap H2){
    node temp = binomial_heap_merge(H1,H2);
    H1->root = NULL;
    H2->root = NULL;
    if(temp == NULL){
        return NULL;
    }
    node prev = NULL;
	node n = temp;
	node next = temp->sibling;
	
	while(next != NULL){
		if((n->degree != next->degree) || ((next->sibling != NULL) && (next->sibling->degree == n->degree))){
			prev = n;
			n = next;
		}else{
			if(n->key < next->key){
                // binomial link
				n->sibling = next->sibling;
				next->parent = n;
				next->sibling = n->child;
				n->child = next;
				n->degree = n->degree + 1;
			}else{
				if(prev == NULL){
					temp = next;
				}else{
					prev->sibling = next;
				}
                // Binomial link
				n->parent = next;
				n->sibling = next->child;
				next->child = n;
				next->degree = next->degree + 1;
				n = next;
			}
		}
		next = n->sibling;
	}
	return temp;
}
void binomial_heap_insert(heap H1,heap H2){
    H1->root = binomial_heap_union(H1,H2);
    free(H2);
}
node binomial_heap_minimum(heap H){
    if(H->root == NULL){
        return NULL;
    }
    node min = H->root;
    node min_prev = NULL;
    node next = min->sibling;
    node next_prev = min;

    while(next != NULL){
		if(next->key < min->key){
			min = next;
			min_prev = next_prev;
		}
		next_prev = next;
		next = next->sibling;
	}
    return min;
}
void binomial_heap_remove(heap H,node x,node y){
    if(x == H->root){
		H->root = x->sibling;
	}else{
		y->sibling = x->sibling;
	}
	
	node newRoot = NULL;
	node childNode = x->child;
	// reversing the string
	while(childNode != NULL){
		node next = childNode->sibling;
		childNode->sibling = newRoot;
		childNode->parent = NULL;
		newRoot = childNode;
		childNode = next;
	}
	heap H1 = make_heap();
	H1->root = newRoot;
	H->root = binomial_heap_union(H, H1);
	free(H1);
}
node binomial_heap_extract_min(heap H){
    if(H->root == NULL){
        return NULL;
    }
    node min = H->root;
    node min_prev = NULL;
    node next = min->sibling;
    node next_prev = min;

    while(next != NULL){
		if(next->key < min->key){
			min = next;
			min_prev = next_prev;
		}
		next_prev = next;
		next = next->sibling;
	}
    binomial_heap_remove(H,min,min_prev);
    return min;
}
node find(node n,int x){
    node a = n;
    node b = NULL;
    if(n->key == x){
        b = n;
        return b;
    }
    if(a->child != NULL && b == NULL){
        b = find(a->child,x);
    }
    if(a->sibling != NULL && b == NULL){
        b = find(a->sibling,x);
    }
    return b;
}
int binomial_heap_decrease_key(heap H,int n,int m){
    node temp = find(H->root,n);
    if(temp == NULL){
        return 0;
    }
    temp->key = m;
    node a = temp;
    node b = temp->parent;
    while(b != NULL && a->key < b->key){
		int t = a->key;
		a->key = b->key;
		b->key = t;
		a = b;
		b = b->parent;
	}
	return 1;
}
int binomial_heap_delete(heap H,int x){
    int n = binomial_heap_decrease_key(H,x,INT_MIN);
    if(n == 0){
        return 0;
    }
    binomial_heap_extract_min(H);
    return 1;
}
int main(){
    char ch;
    heap H = make_heap();
    H->root = NULL;
    int k;
    int y,z;
    while(1){
        scanf("%c",&ch);
        switch(ch){
                case 'i':{
                    scanf("%d",&k);
                    node x = create_node(k);
                    heap temp = make_heap();
                    temp->root = x;
                    binomial_heap_insert(H,temp);
                    break;
                }
                case 'd':{
                    scanf("%d",&k);
                    int res = binomial_heap_delete(H,k);
                    if(res == 0){
                        printf("-1\n");
                    }
                    else{
                        printf("%d\n",k);
                    }
                    break;
                }
                case 'p':{
                    print(H->root);
                    printf("\n");
                    break;
                }
                case 'm':{
                    node min = binomial_heap_minimum(H);
                    printf("%d\n",min->key);
                    break;
                }
                case 'x':{
                    node x = binomial_heap_extract_min(H);
                    printf("%d\n",x->key);
                    break;
                }
                case 'r':{
                    scanf("%d %d",&y,&z);
                    int res = y - z;
                    int l = binomial_heap_decrease_key(H,y,res);
                    if(l == 0){
                        printf("-1\n");
                    }
                    else{
                        printf("%d\n",res);
                    }
                    break;
                }
                case 'e':{
                    return 0;
                }
        }
    }
    
}
/*
i 10
i 20
i 30
i 40
i 50
p
m
x
p
r 50 4
p
r 70 5
e
*/