//Q5 Graph

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 999999

int n;
int graph[MAX][MAX];

void initGraph() {
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i==j) graph[i][j]=0;
            else graph[i][j]=INF;
}

void readSIF() {
    int edges,i,j;
    printf("Enter number of vertices: ");
    scanf("%d",&n);
    initGraph();

    printf("Enter number of edges: ");
    scanf("%d",&edges);
    printf("Enter edges in SIF format: src dest weight\n");
    for(i=0;i<edges;i++) {
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        graph[u][v]=w;
    }

    printf("\nAdjacency Matrix:\n");
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(graph[i][j]==INF) printf("INF ");
            else printf("%3d ",graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int src) {
    int dist[MAX], visited[MAX];
    int i,v,count;

    for(i=0;i<n;i++) {
        dist[i]=INF;
        visited[i]=0;
    }
    dist[src]=0;

    for(count=0;count<n-1;count++) {
        int min=INF,u=-1;
        for(i=0;i<n;i++) {
            if(!visited[i] && dist[i]<min) {
                min=dist[i];
                u=i;
            }
        }
        if(u==-1) break;

        visited[u]=1;

        for(v=0;v<n;v++) {
            if(!visited[v] && graph[u][v]!=INF && dist[u]+graph[u][v]<dist[v]) {
                dist[v]=dist[u]+graph[u][v];
            }
        }
    }

    printf("\nShortest distances from node %d (Dijkstra):\n",src);
    for(i=0;i<n;i++) {
        if(dist[i]==INF) printf("Node %d: INF\n",i);
        else printf("Node %d: %d\n",i,dist[i]);
    }
}

void floydWarshall() {
    int dist[MAX][MAX];
    int i,j,k;

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            dist[i][j]=graph[i][j];

    for(k=0;k<n;k++) {
        for(i=0;i<n;i++) {
            for(j=0;j<n;j++) {
                if(dist[i][k]!=INF && dist[k][j]!=INF && dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
            }
        }
    }

    printf("\nAll Pair Shortest Paths (Floyd-Warshall):\n");
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(dist[i][j]==INF) printf("INF ");
            else printf("%3d ",dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int src;
    readSIF();

    printf("\nEnter source vertex for Dijkstra: ");
    scanf("%d",&src);

    dijkstra(src);
    floydWarshall();

    return 0;
}

