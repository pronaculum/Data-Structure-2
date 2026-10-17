#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "hash.h"

int main(void) {
    graph* graph = graph_create_graph();
    hash* hash = hash_create_hash(3, STRING);
    int dataset_vertex[] = {4, 2, 7, 1, 5, 3};
    int dataset_edge_start[] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};
    int dataset_edge_end[] = {2, 3, 4, 3, 5, 4, 6, 5, 6, 6};
    char* dataset_hashtag[] = {"onee", "twoo", "thre", "four", "five", "sixx"};
    for (int i = 0; i < (int)sizeof(dataset_vertex)/(int)sizeof(dataset_vertex[0]); i++) {
        graph_insert_vertex(graph, dataset_vertex[i]);
        hash_push(hash, graph->nodes[i], dataset_hashtag[i]);
    }
    for (int i = 0; i < (int)sizeof(dataset_edge_start)/(int)sizeof(dataset_edge_start[0]); i++) {
        graph_insert_edge(graph, dataset_edge_start[i] - 1, dataset_edge_end[i] - 1);
    }
    graph_BFS(graph, 5);
    graph_DFS(graph, 5);
    graph_print_node((graphnode*)hash_pop(hash, "twoo")->item);
    return 0;
}