#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<math.h>
struct Edge{
    int x;  // start point of edge
    int y;  // destination point of edge
    int w;  // Weight f edge
};
typedef struct Edge* Edge;
struct Graph{
    int vertices;   // No of vertices
    int Edge ;     // No of edges
    Edge Edges;
};
typedef struct Graph* Graph;
Graph Create_graph(int v,int e){
    Graph G = (Graph)malloc(sizeof(struct Graph));
    G->vertices = v;
    G->Edge = e;
    G->Edges = malloc(e*sizeof(struct Edge));
    return G;
}
void Bellman_ford(Graph G,int src){
    int v = G->vertices;
    int e = G->Edge;
    int distances[v];
    for(int i = 0;i<e;i++){
        distances[i] = INT_MAX;
    }
    distances[src] = 0;
    for(int i = 0;i<v;i++){
        for(int j = 0;j<e;j++){
            int s = G->Edges[j].x;  // s is for Source
            int d = G->Edges[j].y;  // d is for destination
            int w = G->Edges[j].w;  // w is for weight of Edge
            if(distances[s] != INT_MAX && distances[s] + w < distances[d]){
                distances[d] = distances[s] + w;
            }
        }
    }
    for(int i = 0;i<e;i++){
        int s = G->Edges[i].x;  
        int d = G->Edges[i].y;  
        int w = G->Edges[i].w;
        if(distances[s] != INT_MAX && distances[s] + w < distances[d]){
            printf("1\n");
            return;
        }
    }
    printf("-1\n");

}
int main(){
    int v,e;
    scanf("%d %d",&v,&e);
    Graph G = Create_graph(v,e);
    int x,y,z;
    for(int i = 0;i<e;i++){
        scanf("%d %d %d",&x,&y,&z);
        G->Edges[i].x = x;
        G->Edges[i].y = y;
        G->Edges[i].w = z;
    }
    Bellman_ford(G,0);
    return 0;
}