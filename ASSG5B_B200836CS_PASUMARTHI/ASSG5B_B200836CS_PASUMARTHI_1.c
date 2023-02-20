#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<math.h>

int main(){
    int n;
    scanf("%d",&n);
    int G[n][n];
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&G[i][j]);
        }
    }

    for(int i = 0;i<n;i++){
        printf("%d ",i);
        for(int j = 0;j<n;j++){
            if(G[i][j] == 1){
                printf("%d ",j);
            }
        }
        printf("\n");
    }
    return 0;
}