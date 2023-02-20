#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Test case - 1 is coming wrong
int IsFull(int arr[],int *size,int *top){
    if(*top == *size - 1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(int arr[],int key,int *size,int *top){
    if(IsFull(arr,size,top)){
        printf("1\n");
        *size = (*size)*2;
        *top = *top + 1;
        arr[*top] = key;
    }
    else{
        *top = *top + 1;
        arr[*top] = key;
    }
}
int IsEmpty(int arr[],int size,int *top){
    if(*top == -1){
        return 1;
    }
    else{
        return 0;
    }
}
int pop(int arr[],int size,int *top){
    int element;
    if(IsEmpty(arr,size,top)){
        element = -1;
    }
    else{
        element = arr[*top];
        *top = *top - 1;
    }
    return element;
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    int key;
    int del;
    int top = -1;
    char ch;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf(" %d",&key);
                push(arr,key,&n,&top);
                break;
            }
            case 'd':{
                del = pop(arr,n,&top);
                printf("%d\n",del);
                break;
            }
            case 't':{
                return 0;
            }
        }
    }
    return 0;
}
