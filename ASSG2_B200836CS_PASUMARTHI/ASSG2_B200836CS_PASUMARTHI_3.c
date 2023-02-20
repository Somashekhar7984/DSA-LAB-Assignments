#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct node{
    int age;
    char* first_name;
    char* last_name;
    struct node* left;
    struct node* right;
    struct node* parent;
};
typedef struct node* node;
struct BT{
    node root;
};
typedef struct BT* BT;
node create_node(int lenf,int lenl,int age){
    node temp;
    temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    char* first_name = (char*)malloc(lenf*sizeof(char));
    char* last_name = (char*)malloc(lenl*sizeof(char));
    temp->first_name = first_name;
    temp->last_name = last_name;
    temp->age = age;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}
int sum_ASCII(char last_name[]){
    int sum = 0;
    int len = strlen(last_name);
    for(int i = 0;i<len;i++){
        sum = sum + last_name[i];
    }
    return sum;
}
BT insert(BT T,node z){
    node x,y;
    y = NULL;
    x = T->root;
    while(x != NULL){
        y = x;
        if(z->age < x->age){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL){
        T->root = z;
    }
    else if(z->age<y->age){
        y->left = z;
    }
    else{
        y->right = z;
    }
    return T;
}
node nodeExists(node root,char first_name[],char last_name[]){
    if(root == NULL){
        return NULL;
    }
    else{
        if((strcmp(root->first_name,first_name) == 0) && (strcmp(root->last_name,last_name) == 0)){
            return root;
        }
        else{
            node resl = nodeExists(root->left,first_name,last_name);
            node resr = nodeExists(root->right,first_name,last_name);
            if(resl != NULL){
                return resl;
            }
            else if(resr != NULL){
                return resr;
            }
        }
    }
}
void print(BT T,node req){
    if(req == NULL){
        printf("-1\n");
        return;
    }
    node temp = T->root;
    while(temp != NULL && (req->age != temp->age)){
        printf("%s %s %d\n",temp->first_name,temp->last_name,temp->age);
        if((req->age) < (temp->age)){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    printf("%s %s %d\n",temp->first_name,temp->last_name,temp->age);
}
int main(){
    char ch;
    BT hash_table[128];
    for(int i = 0;i<128;i++){
        BT T;
        T = (BT)malloc(sizeof(struct BT));
        T->root = NULL;
        hash_table[i] = T;
    }
    while(1){
        char firstname[100000],lastname[100000];
        int age;
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%s %s %d",firstname,lastname,&age);
                int lenf = strlen(firstname);
                int lenl = strlen(lastname);
                node temp;
                temp = (node)malloc(sizeof(struct node));
                temp = create_node(lenf,lenl,age);
                strcpy(temp->first_name,firstname);
                strcpy(temp->last_name,lastname);
                int index;
                int sum = sum_ASCII(lastname);
                index = ((sum)%128);
                hash_table[index] = insert(hash_table[index],temp);
                break;
            }
            case 'p':{
                scanf("%s %s",firstname,lastname);
                int sum = sum_ASCII(lastname);
                int index = ((sum)%128);
                node temp;
                temp = (node)malloc(sizeof(struct node));
                temp = nodeExists(hash_table[index]->root,firstname,lastname);
                print(hash_table[index],temp);
                break;
              //printf("%s\n %s\n",firstname,lastname);
            }
            case 't':{
                return 0;
            }
        }
    }
    /*
    Adding default is terminating the program 
    removed default and replace with it 
    case 't':{
        return 0;
    }
    */
}
/*
i Ranbir Kapoor 30
i Anil Kapoor 60
i Kareena Kapoor 40
i elon qwe3 50
i Boney Kapoor 65
i melon qwe3 56
p Boney Kapoor
p melon qwe3
p Sonam Kapoor
p Sachin Tendulkar
t
*/