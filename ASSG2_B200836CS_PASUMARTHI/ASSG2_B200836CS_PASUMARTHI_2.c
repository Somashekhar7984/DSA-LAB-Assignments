#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node{
    char* word;
    struct node* next;
};
typedef struct node* node;
struct LL{
    node head;
};
typedef struct LL* LL;
node create_node(int len){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    char* word = (char*)malloc(len*sizeof(char));
    temp->word = word;
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
void print(LL L){
    node selected;
    selected = L->head;
    if(selected == NULL){
        printf("null");
    }
    else{
        printf("%s",selected->word);
        selected = selected->next;
        while(selected != NULL){
            printf("-%s",selected->word);
            selected = selected->next;
        }
    }
}
int search(LL L,node x){
    node selected = L->head;
    if(selected == NULL){
        return 0;
    }
    else{
        while(selected != NULL){
            if(strcmp(selected->word,x->word) == 0){
                return 1; // returns 1 if word is present in linked list
            }
            selected = selected->next;
        }
    }
    return 0;
    // returns 0 if word is not present
}
void implementing_hash_table(LL hash_table[],int size,char str[]){
    char words[550];
    int j = 0;
    for(int i = 0;i<=strlen(str);i++){
        if(str[i] == ' '|| str[i] == '\0' ){
            words[j] = '\0';
            j = 0;
            int len = strlen(words);
            //printf("%s %d ",words,len);
            int index = ((len*len)%size);
            //printf("%d\n",index);
            node temp;
            temp = (node)malloc(sizeof(struct node));
            temp = create_node(len);
            strcpy(temp->word,words);
            if(search(hash_table[index],temp) == 0){
                insert(hash_table[index],temp);
            }
        }
        else{
            words[j] = str[i];
            j++;
        }
    }
    for(int i = 0;i<size;i++){
        printf("%d:",i);
        print(hash_table[i]);
        printf("\n");
    }
}
int main(){
    int size;
    char str[550];
    scanf("%d %[^\n]s",&size,str);
    // creating a hash table of linked lists
    LL hash_table[size];
    for(int i = 0;i<size;i++){
        LL L;
        L = (LL)malloc(sizeof(struct LL));
        L->head = NULL;
        hash_table[i] = L;
    }
    implementing_hash_table(hash_table,size,str);
    return 0;
}
/*
3
write a program to create a hash table
*/
/*
5
This program is a program to create a hash table
*/