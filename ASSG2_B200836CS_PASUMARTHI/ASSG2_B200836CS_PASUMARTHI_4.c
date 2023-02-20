#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int idx(char name[]){
    int first = 0;
    int second = 0;
    int third = 0;
    for(int i = 0;i<strlen(name);i++){
        if(i<=2){
            first = first + name[i];
        }
    }
    for(int i = 0;i<strlen(name);i = i + 2){
        if(i <= 4){
            second = second + name[i];
        }
    }
    for(int i = 0;i<strlen(name);i = i + 4){
        if(i <= 8){
            third = third + name[i];
        }
    }
    first = (((first)%26)%10);
    second = (((second)%26)%10);
    third = (((third)%26)%10);
    int index = (first*100) + (second*10) + third;
    //printf("%d\n",index);
    return index;
}
void roll(char* roll_no[],char name[],int index){
    char rollno[10];
    int k = index;
    rollno[0] = name[0];
    rollno[3] = (k%10) + '0';
    k = k/10;
    rollno[2] = (k%10) + '0';
    k = k/10;
    rollno[1] = k + '0';
    rollno[4] = '\0';
    strcpy(roll_no[index],rollno);
}
int main(){
    char* hash_table[1000];
    for(int i = 0;i<1000;i++){
        hash_table[i] = NULL;
    }
    char* roll_no[1000];
    for(int i = 0;i<1000;i++){
        roll_no[i] = NULL;
    }
    char rollno[10];
    char name[10000];
    char ch;
    while(1){
        scanf("%c",&ch);
        switch(ch){
            case 'i':{
                scanf("%s",name);
                int index = idx(name);
                int len = strlen(name);
                hash_table[index] = (char*)malloc(len*sizeof(char));
                roll_no[index] = (char*)malloc(10*sizeof(char));
                strcpy(hash_table[index],name);
                roll(roll_no,name,index);
                // printf("%s\n",hash_table[index]);
                // printf("%d\n",index);
                // printf("%s\n",roll_no[index]);
                break;
            }
            case 's':{
                scanf("%s",rollno);
                int idx = 0;
                for(int i = 1;i<strlen(rollno);i++){
                    idx = idx*10 + (int)(rollno[i] - '0');
                }
                if(hash_table[idx] != NULL){
                    printf("%s\n",hash_table[idx]);
                }
                else{
                    printf("NOT FOUND\n");
                }
                break;
            }
            case 'd':{
                scanf("%s",rollno);
                int idx = 0;
                for(int i = 1;i<strlen(rollno);i++){
                    idx = idx*10 + (int)(rollno[i] - '0');
                }
                hash_table[idx] = NULL;
                break;
            }
            case 't':{
                return 0;
            }
        }
    }
}
/*
i Abhishek
i Anupam
i Akshat
i Ebin
s A744
s E287
s A333
d A744
s A744
t

*/