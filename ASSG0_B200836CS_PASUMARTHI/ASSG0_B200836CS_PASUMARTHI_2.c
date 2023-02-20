#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct queue{
    int head;
    int tail;
    int size;
    int *arr;
};
typedef struct queue *queue;

int IsFull(queue q){
    if(q->tail == q->size - 1){
        return 1;
    }
    else{
        return -1;
    }
}
int IsEmpty(queue q){
    if(q->head == q->tail){
        return 1;
    }
    else{
        return -1;
    }
}
void enqueue(queue q,int k){
    if(IsFull(q) == 1){
        printf("1\n");
    }
    else{
        q->tail++;
        q->arr[q->tail] = k;
        // if(q->tail == q->size - 1){
        //     q->tail = -1;
        // }
    }
}
int dequeue(queue q){
    int del;
    if(IsEmpty(q) == 1){
        return 1;
    }
    q->head++;
    del = q->arr[q->head];
    return del; 
}
int main(){
    int n;
    char ch;
    int k;
    scanf("%d",&n);
    queue q;
    q->head = -1;
    q->tail = -1;
    q->arr = (int*)malloc(sizeof(int) * n);
    q->size = n;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf(" %d",&k);
                enqueue(q,k);
                break;
            }
            case 'd':{
                int del;
                del = dequeue(q);
                printf("%d\n",del);
                break;
            }
            case 'e':{
                printf("%d\n",IsEmpty(q));
                break;
            }
            case 'f':{
                printf("%d\n",IsFull(q));
                break;
            }
            case 't':{
                return 0;
            }
        }

    }
}