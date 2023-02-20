#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node *node;
struct LL{
    struct node *head;
};
typedef struct LL *LL;

node create_node(int key){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->data = key;
    temp->next = NULL;
    return temp;
}

void insert(LL L,node x){
    node selected;
    selected = L->head;
    if(selected != NULL){
        while(selected->next != NULL){
            selected = selected->next;
        }
        selected->next = x;
    }
    else{
        L->head = x; 
    }
}
node KLast(LL L,int k,int n){
    int search = n-k;
    int j = 0;
    node selected = L->head;
    while(j<search){
        selected = selected->next;
        j++;
    }
    return selected;

}
int digit(char ch){
    if(ch>='0' && ch<='9'){
        return 1;
    }
    else{
        return 0;
    }
}
void change_numerical_string_to_array(char str[],int *size,int arr[]){
    int n = strlen(str);
    int j = 0;
    int neg;
    for(int i = 0;i<n;i++){
        if(str[i] == ' '){
            continue;
        }
        if(str[i] == '-' && digit(str[i+1])){ 
            neg = 1; // neg is for the negative numbers 
        }
        else if(digit(str[i])){
            int num = 0;
            while(digit(str[i])){
                num = num*10 + (int)(str[i] - '0');
                i++;
            }
            i--;
            if(neg == 1){
                num = (-1)*num;
                neg = 0;
            }
            arr[j] = num;
            j++; // j is actual truesize of array
        }
    }
    *size = j;
    return;
}


int main(){
    char str[100000];
    scanf("%[^\n]s",str);
    int arr[100000];
    int size;
    change_numerical_string_to_array(str,&size,arr);
    int k;
    scanf("%d",&k);
    if(k>size){
        printf("-1");
        return 0;
    }
    // int n = size;
    // int search = n - k;
    // printf("%d",arr[search]);
    LL L;
    L = (LL)malloc(sizeof(struct LL));
    L->head = NULL;
    for(int i = 0;i<size;i++){
        node x;
        x = create_node(arr[i]);
        insert(L,x);
    }
    node klast;
    klast = (node)malloc(sizeof(struct node));
    klast = KLast(L,k,size);
    printf("%d",klast->data);
    return 0;
}