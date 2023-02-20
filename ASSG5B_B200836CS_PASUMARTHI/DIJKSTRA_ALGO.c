#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<math.h>
struct node{
    int key;
    int weight;
    struct node* next;
};
typedef struct node* node;
struct LL{
    node head;
};
typedef struct LL *LL;
struct Graph{
    int vertices;  // no of vertices
    LL L;   // for adjaceny list
};
typedef struct Graph* Graph;
node create_node(int k){
    node temp = (node)malloc(sizeof(struct node));
    if(temp == NULL){
        exit(0);
    }
    temp->key = k;
    temp->weight = INT_MIN;
    temp->next = NULL;
    return temp;
}
Graph create_graph(int n){
    Graph G = (Graph)malloc(sizeof(struct Graph));
    G->vertices = n;
    G->L = (LL)malloc(n*sizeof(struct LL));
    for(int i = 0;i<n;i++){
        G->L[i].head = NULL;
    }
    return G;
}
void insert_edge(Graph G,int k,int key){    // same as inserting in Linked list
    node temp = create_node(key);             // for the linked list of Kth vertex at the tail
    if(G->L[k].head == NULL){
        temp->next = G->L[k].head;
        G->L[k].head = temp;
    }
    else{
        node selected = G->L[k].head;
        while(selected->next != NULL){
            selected = selected->next;
        }
        selected->next = temp;
    }
}
void insert_weight(Graph G,int k,int weight){
    if(G->L[k].head == NULL){
        return;
    }
    else{
        node selected = G->L[k].head;
        while(selected->next != NULL && selected->weight != INT_MIN){
            selected = selected->next;
        }
        selected->weight = weight;
    }
}
int mindistance(int distance[],int set[],int n){
    int min = INT_MAX;
    int index;
    for(int i = 0;i<n;i++){
        if(set[i] == 0 && distance[i] <= min){
            min = distance[i];
            index = i;
        }
    }
    return index;
}
void dijkstra_1(int** arr,int k,int n){
    int distance[n];
    int set[n];
    for(int i = 0;i<n;i++){
        distance[i] = INT_MAX;
        set[i] = 0;
    }
    distance[k] = 0;
    for(int i = 0;i<n-1;i++){
        int d = mindistance(distance,set,n);
        set[d] = 1;
        for(int j = 0;j<n;j++){
            if(!set[j] && arr[d][j] && distance[d] != INT_MAX && distance[d] + arr[d][j] < distance[j]){
                distance[j] = distance[d] + arr[d][j];
            }
        } 
    }
    for(int i = 0;i<n;i++){
        if(distance[i] == INT_MAX){
            printf("INF ");
        }
        else{
            printf("%d ",distance[i]);
        }
    }
}
void dijkstra_2(int** arr,int x,int y,int n){
    int distance[n];
    int set[n];
    for(int i = 0;i<n;i++){
        distance[i] = INT_MAX;
        set[i] = 0;
    }
    distance[x] = 0;
    for(int i = 0;i<n-1;i++){
        int d = mindistance(distance,set,n);
        set[d] = 1;
        for(int j = 0;j<n;j++){
            if(!set[j] && arr[d][j] && distance[d] != INT_MAX && distance[d] + arr[d][j] < distance[j]){
                distance[j] = distance[d] + arr[d][j];
            }
        } 
    }
    // printing
    if(distance[y] == INT_MAX){
        printf("UNREACHABLE");
        return;
    }
    else{
        printf("%d",distance[y]);
        return;
    }

}
int main(){
    int n;
    int k;
    char c;
    scanf("%d",&n);
    Graph G;
    G = create_graph(n);
    //for the nodes in the adjaceny list
    for(int i = 0;i<n;i++){
        scanf("%d%c",&k,&c);
        if(c == '\n'){
            continue;
        }
        else{
            char str[100];
            scanf("%[^\n]s",str);
            int l = strlen(str);
            for(int j = 0;j<l;j++){
                if(str[j] == ' '){
                    continue;;
                }
                else if(str[j] >= '0' && str[j] <= '9'){
                    int num = 0;
                    while(str[j] >= '0' && str[j] <= '9'){
                        num = num*10 + (int)(str[j] - '0');
                        j++;
                    }
                    j--;
                    insert_edge(G,k,num);
                }
            }
        }

    }
    
    for(int i = 0;i<n;i++){
        scanf("%d%c",&k,&c);
        if(c == '\n'){
            continue;
        }
        else{
            char str[100];
            scanf("%[^\n]s",str);
            int l = strlen(str);
            for(int j = 0;j<l;j++){
                if(str[j] == ' '){
                    continue;;
                }
                else if(str[j] >= '0' && str[j] <= '9'){
                    int num = 0;
                    while(str[j] >= '0' && str[j] <= '9'){
                        num = num*10 + (int)(str[j] - '0');
                        j++;
                    }
                    j--;
                    insert_weight(G,k,num);
                }
            }
        }

    }
    // Creating a 2D array for the graph
    int** arr = (int**)malloc(n*sizeof(int*));
    for(int i = 0;i<n;i++){
        arr[i] = (int*)malloc(n*sizeof(int));
    }

    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            arr[i][j] = 0;
        }
    }
    // assigning the weight as the value to the array
    for(int i = 0;i<n;i++){
        node selected = G->L[i].head;
        if(selected == NULL){
            continue;
        }
        while(selected != NULL){
            arr[i][selected->key] = selected->weight;
            selected = selected->next;
        }
    }

    char str[100];
    while(1){
        scanf("%s",str);
        if(strcmp(str,"apsp") == 0){
            scanf("%d",&k);
            dijkstra_1(arr,k,n);
            printf("\n");
        }
        else if(strcmp(str,"sssp") == 0){
            int x,y;
            scanf("%d %d",&x,&y);
            dijkstra_2(arr,x,y,n);
            printf("\n");
        }
        else if(strcmp(str,"stop") == 0){
            for(int i = 0;i<n;i++){
                free(arr[i]);
            }
            free(arr);
            return 0;
        }
    }
}
/*
9
0 1 4
1 5
2 3
3 6
4
5 2 7 8
6 2
7 4
8 5 7
0 2 20
1 3
2 7
3 5
4
5 1 6 4
6 0
7 2
8 2 1
apsp 0
sssp 0 6
sssp 0 7
sssp 5 6
sssp 8 7
sssp 4 0
stop

*/