#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<math.h>
struct node{
    int k;
    int rank;
    struct node* parent;
    struct node* next;
};
typedef struct node* node;
struct node makeset(struct node a,int n){
    node temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->k = n;
    temp->parent = temp;
    temp->rank = 0;
    temp->next = NULL;
    a.next = temp;
    return a;
}
node find(node n,int c,int* c1,int* c2,int* c3,int* c4){
    if(c == 1){
       *c1 = *c1 + 1;
    }
    if(c == 2){
       *c2 = *c2 + 1;
    }
    if(n->parent == n){
        return n;
    }
    else{
        return find(n->parent,c,c1,c2,c3,c4);
    }
}
node find_ByPC(node n,int c,int* c1,int* c2,int* c3,int* c4){
    if(c == 3){
       *c3 = *c3 + 1;
    }
    if(c == 4){
       *c4 = *c4 + 1;
    }
    if(n->parent != n){
        n->parent = find_ByPC(n->parent,c,c1,c2,c3,c4);
    }
    return n->parent;
}
node Union_one(node a,node b,int c,int* c1,int* c2,int* c3,int* c4){    // No rank and No path compression
    a = find(a,c,c1,c2,c3,c4);
    b = find(b,c,c1,c2,c3,c4);
    if(a == b){
        return a;
    }
    else{
        b->parent = a;
        return a;
    }
}
node Union_two(node a,node b,int c,int* c1,int* c2,int* c3,int* c4){    // only with rank
    a = find(a,c,c1,c2,c3,c4);
    b = find(b,c,c1,c2,c3,c4);
    if(a == b){
        return a;
    }
    else{
        if(a->rank >= b->rank){
            b->parent = a;
            if(a->rank == b->rank){
                a->rank = a->rank + 1;
            }
            return a;
        }
        else{
            a->parent = b;
            return b;
        }
    }
}
node Union_three(node a,node b,int c,int* c1,int* c2,int* c3,int* c4){      // only with Path Compression
    a = find_ByPC(a,c,c1,c2,c3,c4);
    b = find_ByPC(b,c,c1,c2,c3,c4);
    if(a == b){
        return a;
    }
    else{
        b->parent = a;
        return a;
    }
}
node Union_four(node a,node b,int c,int* c1,int* c2,int* c3,int* c4){       // both Rank and Path Compression
    a = find_ByPC(a,c,c1,c2,c3,c4);
    b = find_ByPC(b,c,c1,c2,c3,c4);
    if(a == b){
        return a;
    }
    else{
        if(a->rank >= b->rank){
            b->parent = a;
            if(a->rank == b->rank){
                a->rank = a->rank + 1;
            }
            return a;
        }
        else{
            a->parent = b;
            return b;
        }
    }
}
int main(){
    struct node s1[50];
    struct node s2[50];
    struct node s3[50];
    struct node s4[50];
    for(int i = 0;i<50;i++){
        s1[i].next = NULL;
        s2[i].next = NULL;
        s3[i].next = NULL;
        s4[i].next = NULL;
    }
    char ch;
    int x,y;
    int c;
    node p;
    node q;
    node r;
    node s;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'm':{
                scanf("%d",&x);
                if(s1[x].next != NULL){
                    printf("-1\n");
                    continue;
                }
                s1[x] = makeset(s1[x],x);
                s2[x] = makeset(s2[x],x);
                s3[x] = makeset(s3[x],x);
                s4[x] = makeset(s4[x],x);
                printf("%d\n",s1[x].next->k);
                break;
            }
            case 'u':{
                scanf("%d %d",&x,&y);
                if(s1[x].next == NULL || s2[y].next == NULL){
                    printf("-1\n");
                    continue;
                }
				p = Union_one(s1[x].next,s1[y].next, 1,&c1,&c2,&c3,&c4);
				q = Union_two(s2[x].next,s2[y].next, 2,&c1,&c2,&c3,&c4);
				r = Union_three(s3[x].next,s3[y].next, 3,&c1,&c2,&c3,&c4);
				s = Union_four(s4[x].next,s4[y].next, 4,&c1,&c2,&c3,&c4);
				printf("%d %d %d %d\n",p->k,q->k,r->k,s->k);
				break;
            }
            case 'f':{
				scanf("%d",&x);
				if(s1[x].next == NULL){
					printf("-1\n");
					continue;
				} 
				p = find(s1[x].next, 1,&c1,&c2,&c3,&c4);
				q = find(s2[x].next, 2,&c1,&c2,&c3,&c4);
				r = find_ByPC(s3[x].next, 3,&c1,&c2,&c3,&c4);
				s = find_ByPC(s4[x].next, 4,&c1,&c2,&c3,&c4);
				printf("%d %d %d %d\n",p->k,q->k,r->k,s->k);
				break;
            }    
			case 's':{
				printf("%d %d %d %d",c1, c2, c3, c4);
                return 0;
            }    
        }
    }
}
/*
m 1
m 2
m 3
m 4
m 5
m 6
m 7
m 8
m 9
u 1 2
u 3 4
u 5 6
u 7 8
u 9 8
u 6 8
u 4 8
u 2 8
f 9
m 10
u 10 9
s

*/