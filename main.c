#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"

int main(void) {
    graph* graph = graph_create_graph();
    int dataset_vertex[] = {4, 2, 7, 1, 5, 3};
    int dataset_edge_start[] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};
    int dataset_edge_end[] = {2, 3, 4, 3, 5, 4, 6, 5, 6, 6};
    for (int i = 0; i < (int)sizeof(dataset_vertex)/(int)sizeof(dataset_vertex[0]); i++) {
        graph_insert_vertex(graph, dataset_vertex[i]);
    }
    for (int i = 0; i < (int)sizeof(dataset_edge_start)/(int)sizeof(dataset_edge_start[0]); i++) {
        graph_insert_edge(graph, dataset_edge_start[i] - 1, dataset_edge_end[i] - 1);
    }
    graph_BFS(graph, 5);
    graph_DFS(graph, 5);
    return 0;
}