#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

//heap sort
#define HEAP_PARENT(i) (i/2)
#define HEAP_LEFT(i) (2*i)
#define HEAP_RIGHT(i) (2*i+1)

void min_heapify(unsigned int A[][2], unsigned int i, unsigned int n) {
    unsigned int l = HEAP_LEFT(i);
    unsigned int r = HEAP_RIGHT(i);
    unsigned int smallest = 0;
    
    if(l <= n && A[l-1][0] < A[i-1][0]) {
        smallest = l;
    } else {
        smallest = i;
    }
    if(r <= n && A[r-1][0] < A[smallest-1][0]) {
        smallest = r;
    }
    if(smallest != i) {
        unsigned int temp1 = A[i-1][0];
        unsigned int temp2 = A[i-1][1];
        
        A[i-1][0] = A[smallest-1][0];
        A[i-1][1] = A[smallest-1][1];
        A[smallest-1][0] = temp1;
        A[smallest-1][1] = temp2;

        min_heapify(A, smallest, n);
    }
}

void build_min_heap(unsigned int A[][2], unsigned int n) {    
    for(int i = (n/2); i > 0; i--) {
        min_heapify(A, i, n);
    }
}

unsigned int heap_extract_min(unsigned int A[][2], unsigned int n, unsigned int *node_index) {
    if(n < 1) {
        printf("error: underflow\n");
        return -1;
    }
    
    unsigned int min = A[0][0];
    unsigned int u = A[0][1];

    if(n > 1) {        
        A[0][0] = A[n-1][0];
        A[0][1] = A[n-1][1];
        build_min_heap(A, n - 1);
        //min_heapify(A, 1, n - 1);
    }
    *node_index = u;
    return min;
}

void heap_decrease_key(unsigned int heap[][2], unsigned int u, unsigned int weight, unsigned int n) {
    for(int i = 0; i < n; i++) {
        if(heap[i][1] == u) {
            if(weight < heap[i][0]) {
                heap[i][0] = weight;
                unsigned int parent = HEAP_PARENT(i);
                while(i > 0 && heap[parent][0] > heap[i][0]) {
                    //swap
                    unsigned int temp1 = heap[parent][0];
                    unsigned int temp2 = heap[parent][1];
                    heap[parent][0] = heap[i][0];
                    heap[parent][1] = heap[i][1];
                    heap[i][0] = temp1;
                    heap[i][1] = temp2;
                    i = parent;
                    parent = HEAP_PARENT(i);
                }
            }
            break;
        }
    }
}

void relax(unsigned int heap[][2], unsigned int distance[][2], 
           unsigned int u, unsigned int v, unsigned int w, unsigned int n) {
    
    unsigned int weight = distance[u][0] + w;

    if(distance[v][0] > weight) {
        distance[v][0] = weight;        
        distance[v][1] = u;
        heap_decrease_key(heap, v, weight, n);
    }
}
void run_dijkstra(unsigned int adj_matrix[][3000], unsigned int distance[][2], int s, int n) {
    
    unsigned int heap[n][2];
    unsigned int S[n];
    
    for(int i = 0; i < n; i++) {
        distance[i][0] = 0xFFFFFFFF;
        distance[i][1] = 0xFFFFFFFF;
        heap[i][0] = 0xFFFFFFFF;
        heap[i][1] = i;
        S[i] = 0;
    }
    distance[s][0] = 0;
    distance[s][1] = 0;
    heap[s][0] = 0;
    
    unsigned int heap_size = n;
    
    build_min_heap(heap, heap_size);
    
    while(heap_size > 0) {
        unsigned int u = -1;
        unsigned int min_val = heap_extract_min(heap, heap_size, &u);

        if (u == -1) {
           printf("unexpected case\n");
            break;
        }        
        S[u] = 1; 
        heap_size--;
        if(min_val == (unsigned int)-1) {
            break;
        } else {
            for (unsigned int v = 0; v < n; v++) {
                unsigned int w = adj_matrix[u][v];
                if (w != (unsigned int)-1 && S[v] != 1) {
                    relax(heap, distance, u, v, w, heap_size);
                }
            }
        }
    }
    
}


int main(){
    int t; 
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        int n; 
        int m; 
        scanf("%d %d",&n,&m);
        
        unsigned int adj_matrix[n][3000];
        unsigned int shortest_distance[n][2];
        
        memset(adj_matrix, -1, sizeof(adj_matrix));
        memset(shortest_distance, -1, sizeof(shortest_distance));
        
        for(int a1 = 0; a1 < m; a1++){
            int x; 
            int y; 
            int r; 
            scanf("%d %d %d",&x,&y,&r);
            if(adj_matrix[x-1][y-1] > r) {
                adj_matrix[x-1][y-1] = r;
                //comment this line to make the graph a directed one
                //adj_matrix[y-1][x-1] = r;
            }
        }
        int s; 
        scanf("%d",&s);
        run_dijkstra(adj_matrix, shortest_distance, s-1, n);
        
        for(int i = 0; i < n; i++) {
            printf("node: %d weight: %d\n", i+1, shortest_distance[i][0]);
        }
        printf("\n");
    }
    return 0;
}

