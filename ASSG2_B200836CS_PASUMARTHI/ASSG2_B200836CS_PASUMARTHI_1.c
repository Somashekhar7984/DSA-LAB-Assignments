#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int* Create_hash_table(int arr[],int size){
    for(int i = 0;i<size;i++){
        arr[i] = -1;
    }
    return arr;
}
bool is_prime(int n){
    for(int i = 2;i<n-1;i++){
        if(n%i == 0){
            return false;
        }
    }
    return true;
}
int hash_Index(char type,int k,int size,int i,int c1,int c2){
    int index;
    if(type == 'a'){
        index =  (((k%size) + (c1*i) + (c2*i*i))%size);
        return index;
    }
    else if(type == 'b'){
        int prime ;
        for(int j = size - 1;j>0;j--){
            if(is_prime(j)){
                prime = j;
                break;
            }
        }
        index = (((k%size) + i*(prime - (k%prime)))%size);
        return index;
    }
}

int* insert(char type,int *table,int k,int size,int c1,int c2){
    int index;
    for(int i = 0;i<size;i++){
        index = hash_Index(type,k,size,i,c1,c2);
        if(table[index] == -1 || table[index] == -2){
            table[index] = k;
            return table;
        }
    }
}

void search(char type,int *table,int k,int size,int c1,int c2){
    int index;
    for(int i = 0;i<size;i++){
        index = hash_Index(type,k,size,i,c1,c2);
        if(table[index] == -1){
            printf("-1\n");
            return;
        }
        else if(table[index] == k){
            printf("1\n");
            return;
        }
    }
    printf("-1\n");
    return;
}

int* delete(char type,int* table,int k,int size,int c1,int c2){
    int index;
    for(int i = 0;i<size;i++){
        index = hash_Index(type,k,size,i,c1,c2);
        if(table[index] == k){
            table[index] = -2;
            return table;
        }
    }
}

void print(int *table,int size){
    for(int i = 0;i<size;i++){
        if(table[i] == -1 || table[i] == -2){
            printf("%d ()\n",i);
        }
        else{
            printf("%d (%d)\n",i,table[i]);
        }
    }
}

int main(){
    char hash_type;
    scanf("%c",&hash_type);
    int size;
    scanf("%d",&size);
    int arr[size];
    int* hash_table;
    hash_table = Create_hash_table(arr,size);
    int c1,c2;
    if(hash_type == 'a'){
        scanf("%d %d",&c1,&c2);
    }
    char ch;
    int k;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%d",&k);
                hash_table = insert(hash_type,hash_table,k,size,c1,c2);
                break;
            }
            case 's':{
                scanf("%d",&k);
                search(hash_type,hash_table,k,size,c1,c2);
                break;
            }
            case 'd':{
                scanf("%d",&k);
                hash_table = delete(hash_type,hash_table,k,size,c1,c2);
                break;
            }
            case 'p':{
                print(hash_table,size);
                break;
            }
            case 't':{
                return 0;
            }
        }
    }
}
/*
a
7
0 1
i 76
i 40
i 48
i 5
s 5
i 55
p
s 62
d 55
t

b
7
i 76
i 93
i 40
i 47
i 10
i 55
p
d 40
s 47
s 76
s 40
t
*/