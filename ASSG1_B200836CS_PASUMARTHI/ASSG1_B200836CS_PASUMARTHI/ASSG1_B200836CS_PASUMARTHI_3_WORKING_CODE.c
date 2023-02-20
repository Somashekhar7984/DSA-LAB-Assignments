#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int len(char* s){
    int counter=0;
    for(int i=0;s[i]!='\0';++i){
        ++counter;
    }
    return counter;
}
typedef struct node{
    int data;
    struct node*left,*right,*parent;
}node;
typedef struct snode{
    node*data;
    struct snode *next;
}snode;
typedef struct stack_s{
    snode*top;
    int size;
}stack_s;
stack_s* initialize_s(){
    stack_s*new;
    new=malloc(sizeof(stack_s));
    new->top=NULL;
    new->size=0;
    return new;
}
bool empty_s(stack_s*s){
    if(s->top==NULL)
        return true;
    else return false;
}
void push_s(stack_s* s,node*z){
    snode*x;
    x=malloc(sizeof(snode));
    x->data=z;
    x->next=NULL;
    if(s->top==NULL){
        s->top=x;
    }
    else{
        x->next=s->top;
        s->top=x;
    }
    s->size++;
}
void pop_s(stack_s* s){
    if(empty_s(s))
        return;
    snode*x;
    x=s->top->next;
    s->top->next=NULL;
    s->top=x;
    s->size--;
    return;
}
typedef struct cnode{
    char data;
    struct cnode*next;
}cnode;
typedef struct stack_c{
    cnode*top;
}stack_c;
stack_c* initialize_c(){
    stack_c*new;
    new=malloc(sizeof(stack_c));
    new->top=NULL;
    return new;
}
bool empty_c(stack_c*s){
    if(s->top==NULL)
        return true;
    else return false;
}
void push_c(stack_c*s,char c){
    cnode*x;
    x=malloc(sizeof(cnode));
    x->data=c;
    x->next=NULL;
    if(s->top==NULL)
        s->top=x;
    else{
        x->next=s->top;
        s->top=x;
    }
}
void pop_c(stack_c*s){
    if(empty_c(s))
        return;
    else{
        cnode*x;
        x=s->top->next;
        s->top->next=NULL;
        s->top=x;
    }
}
int stack_to_num(stack_c*s){
    int num=0;
    int exp=1;
    stack_c*p;
    p=initialize_c();
    while (!empty_c(s))
    {
        push_c(p,s->top->data);
        pop_c(s);
    }
    while(!empty_c(p)){
        if(p->top->data=='-'){
            num*=-1;
        }
        else{
            num+=((int)p->top->data-48)*exp;
        }
        pop_c(p);
        exp*=10;
    }
    return num;
}
node* make_tree(char s []){
    stack_s*s_stk;
    stack_c*c_stk;
    stack_c*num;
    s_stk=initialize_s();
    c_stk=initialize_c();
    num=initialize_c();
    for(int i=0;i<len(s);++i){
        if(s[i]=='('){
            push_c(c_stk,s[i]);
        }       
        else if(s[i]>='0' && s[i]<='9'){
            push_c(c_stk,s[i]);
        }
        else if(s[i]=='-'){
            push_c(c_stk,s[i]);
        }
        else if(s[i]==')'){
            while(!empty_c(c_stk)){
                if(c_stk->top->data!='('){
                    push_c(num,c_stk->top->data);
                }
                else{
                    pop_c(c_stk);
                    break;
                }
                pop_c(c_stk);
            }
            node*p;
            if(empty_c(num)){
                node*p;
                p=NULL;
                push_s(s_stk,p);
            }
            else{
                int x=stack_to_num(num);
                p=malloc(sizeof(node));
                p->data=x;
                p->left=NULL;
                p->right=NULL;
                p->parent=NULL;
                if(s_stk->size>=2){
                    node*l,*r;
                    r=s_stk->top->data;
                    pop_s(s_stk);
                    l=s_stk->top->data;
                    pop_s(s_stk);
                    p->left=l;
                    p->right=r;
                    if(l!=NULL)
                        l->parent=p;
                    if(r!=NULL)
                        r->parent=p;
                    push_s(s_stk,p);
                }
                else push_s(s_stk,p);
            }
        }

    }
    node*root;
    root=s_stk->top->data;
    pop_s(s_stk);
    return root;
}
bool isBST(node*root){
    if(root==NULL)
        return false;
    if(root->left!=NULL){
        if(root->left->data>root->data)
            return false;
    }
    else if(root->right!=NULL){
        if(root->right->data<root->data)
            return false;
    }
    return true;
}
int no_of_deletions(node*root){
    if(root==NULL)
        return 0;
    else if(isBST(root)){
        return no_of_deletions(root->left)+no_of_deletions(root->right);
    }
    else{
        int counter=0;
        if(root->left!=NULL){
            if(root->left->data<root->data){
                counter+=no_of_deletions(root->left);
            }
            else{
                root->left=NULL;
                ++counter;
            }
        }
        if(root->right!=NULL){
            if(root->right->data>root->data){
                counter+=no_of_deletions(root->right);
            }
            else{
                root->right=NULL;
                ++counter;
            }
        }
        return counter;
    }
}
int main(){
    char P[2000];
    scanf("%[^\n]%*c",P);
    node*root;
    root=make_tree(P);
    printf("%d\n",no_of_deletions(root));
    return 0;
}