#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<math.h>

struct edge{
	int u;
	int v;
	int w;
};
typedef struct edge edge;
struct node{
	int vertex;
	struct node* next;
};
typedef struct node node;
struct graph{
	int vertices;
	int edges;
	node** array;
};
typedef struct graph graph;
struct subset{
	int parent;
	int rank;
};
typedef struct subset subset;
graph* createGraph(int v){
	graph* newGraph = (graph*)malloc(sizeof(graph));
	newGraph->vertices = v;
	newGraph->array = malloc(v*sizeof(node));
	for(int i=0; i<v; i++){
		newGraph->array[i] = NULL;
	}
	return newGraph;
}
node* createNode(){
	node* newNode = (node*)malloc(sizeof(node));
	newNode->next = NULL;
	return newNode;
}
int addEdges(graph* graph){
	int e = 0;
	int v = graph->vertices;
	for(int i=0; i<v; i++){
		char ch;
		int x;
		node* n;
		scanf("%d%c",&x,&ch);
		while(ch != '\n'){
			node* newNode = createNode();
			e++;
			newNode->vertex = x;
			if(graph->array[i] == NULL){
				graph->array[i] = newNode;
				n = graph->array[i]; 
			}else{
				n->next = newNode;
				n = n->next;
			}
			scanf("%d%c",&x,&ch);
		}
		node* newNode = createNode();
		newNode->vertex = x;
		if(graph->array[i] == NULL){
			graph->array[i] = newNode;
			n = graph->array[i]; 
		}else{
			n->next = newNode;
			n = n->next;
		}
		
	}
	return e;
}
void sort(edge edges[], int e){
	int min = 0;
	int index = 0;
	for(int i=0;i<e-1;i++){
		index = i;
		min = edges[i].w;
		for(int j=i+1; j<e; j++){
			if(min > edges[j].w){
				index = j;
				min = edges[j].w;
			}
		}
		
		if(index != i){
			int src = edges[i].u;
			int dest = edges[i].v;
			int wgt = edges[i].w;
			edges[i].u = edges[index].u;
			edges[i].v = edges[index].v;
			edges[i].w = edges[index].w;
			edges[index].u = src;
			edges[index].v = dest;
			edges[index].w = wgt;
		}
	}
}
int findSet(subset subsets[], int v){
	if(subsets[v].parent != v){
		subsets[v].parent = findSet(subsets,subsets[v].parent);
	}
	return subsets[v].parent;
}
void Union(subset subsets[], int x, int y){
	int a = findSet(subsets,x);
	int b = findSet(subsets,y);
	if(subsets[a].rank < subsets[b].rank){
		subsets[a].parent = b;
	}else if(subsets[a].rank > subsets[b].rank){
		subsets[b].parent = a;
	}else{
		subsets[b].parent = a;
		subsets[a].rank++;
	}
}
int kruskal(graph* graph){
	int v = graph->vertices;
	int e = 0;
	int flag = 1;
	edge edges[graph->edges];
	for(int i=0; i<v; i++){
		node* n = graph->array[i]->next;
		int waste;
		scanf("%d",&waste);
		while(n){
			int wt;
			scanf("%d",&wt);
			for(int j=0; j<e; j++){
				if(edges[j].u == n->vertex && edges[j].v == i){
					flag = 0;
					break;
				}
			}
			if(flag == 1){
				edges[e].u = i;
				edges[e].v = n->vertex;
				edges[e].w = wt;
				e = e + 1;
				n = n->next;
			}else{
				flag = 1;
				n = n->next;
			}
		}
	}
	sort(edges,graph->edges);
	
	subset subsets[v];
	for(int i=0;i<v;i++){
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}
	e = 0;
	int i = 0;
	int sumOfwsMST = 0;
	while(e < v-1 && i < graph->edges){
		int x = findSet(subsets, edges[i].u);
		int y = findSet(subsets, edges[i].v);
		if(x != y){
			sumOfwsMST = sumOfwsMST + edges[i].w;
			Union(subsets,x,y);
			e++;
			i++;
		}else{
			i++;
		}
	}
	printf("%d",sumOfwsMST);
	
}
int minKey(int key[], int set[], int v){
	int min = INT_MAX;
	int index;
	for(int i=0; i<v; i++){
		if(set[i] == 0 && key[i] < min){
			min = key[i];
			index = i;
		}
		
	}
	return index;
}
int prim(graph* graph){
	int v = graph->vertices;
	int e = 0;
	int num = graph->edges;
	edge edges[num];
	for(int i=0; i<v; i++){
		node* n = graph->array[i]->next;
		int waste;
		scanf("%d",&waste);
		while(n != NULL){
			edges[e].u = i;
			edges[e].v = n->vertex;
			int wt;
			scanf("%d",&wt);
			edges[e].w = wt;
			e++;
			n = n->next;
		}
		
	}
	e = num;
	int set[v];
	int key[v];
	for(int i=0;i<v;i++){
		set[i] = 0;
		key[i] = 2147483647;
	}
	key[0] = 0;
	for(int i=0;i<v-1;i++){
		int u = minKey(key,set,v);
		set[u] = 1;
		for(int j=0;j<e;j++){
			if( (edges[j].u == u) && ( set[edges[j].v] == 0 ) && ( key[edges[j].v] > edges[j].w ) ){
				key[edges[j].v] = edges[j].w;
			}
		}
	}
	int sumOfwsMST = 0;
	for(int i=0; i<v; i++){
		sumOfwsMST = sumOfwsMST + key[i];
	}
	printf("%d",sumOfwsMST);
}
int main(){
	int v;
	int e;
	char ch;
	scanf("%c",&ch);
	scanf("%d",&v);
	graph* graph = createGraph(v);
	e = addEdges(graph);
    if(ch == 'a'){
        graph->edges = e/2;
        kruskal(graph);
        return 0;
    }
    else if(ch == 'b'){
        graph->edges = e;
		prim(graph);
		return 0;
    }
	
}
/*
a
7
0 1 5
1 0 2 6
2 1 3
3 2 4 6
4 3 5 6
5 0 4
6 1 3 4
0 28 10
1 28 16 14
2 16 12
3 12 22 18
4 22 25 24
5 10 25
6 14 18 24
*/

/*
b
7
0 1 5
1 0 2 6
2 1 3
3 2 4 6
4 3 5 6
5 0 4
6 1 3 4
0 28 10
1 28 16 14
2 16 12
3 12 22 18
4 22 25 24
5 10 25
6 14 18 24
*/

