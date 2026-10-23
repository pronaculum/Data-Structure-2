#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "hash.h"
#include "sort.h"
#include "heap.h"
#include "interface.h"

void graph_print(void* node) { graph_print_node((graphnode*)node); }

int main(void) {
    /*
    graph* graph = graph_create_graph();
    hash* hashS = hash_create_hash(3, STRING);
    hash* hashI = hash_create_hash(3, UNSIGNEDINT);
    dijkstra_package* pac;
    int dataset_vertex[] = {4, 2, 7, 1, 5, 3};
    int dataset_edge_start[] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};
    int dataset_edge_end[] = {2, 3, 4, 3, 5, 4, 6, 5, 6, 6};
    char* dataset_hashtag[] = {"onee", "twoo", "thre", "four", "five", "sixx"};
    unsigned int* dataset_UID[] = {&(unsigned int){1}, &(unsigned int){11}, &(unsigned int){111}, &(unsigned int){1111}, &(unsigned int){11111}, &(unsigned int){111111}};
    for (int i = 0; i < (int)sizeof(dataset_vertex)/(int)sizeof(dataset_vertex[0]); i++) {
        graph_insert_vertex(graph, dataset_vertex[i]);
        hash_push(hashS, graph->nodes[i], dataset_hashtag[i]);
        hash_push(hashI, graph->nodes[i], dataset_UID[i]);
    }
    for (int i = 0; i < (int)sizeof(dataset_edge_start)/(int)sizeof(dataset_edge_start[0]); i++) {
        graph_insert_edge(graph, dataset_edge_start[i] - 1, dataset_edge_end[i] - 1);
    }
    graph_BFS(graph, 5);
    graph_DFS(graph, 5);
    hash_print_node(hash_pop(hashS, "twoo"), &graph_print);
    hash_print_node(hash_peek(hashS, "twoo"), &graph_print);
    hash_print_node(hash_pop(hashS, "sevn"), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_peek(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){1111111}), &graph_print);
    printf("graph->length : %d\n", graph->length);
    pac = dijkstra(graph, 0, NULL, NULL);
    if(pac != NULL) {
        printf("dijkstra Start\n");
        printf("pac->length : %d\n", pac->length);
        //for (int i=0;i<pac->length;i++) printf("[current index : %d, distance : %d, parent : %d]\n", i, pac->distance[i], pac->parent[i]); 
        printf("dijkstra End\n");
    }
    
    printf("Merge Start\n");
    
    for (i=0;i<2;i++) { array[i] = ((int[]){2, 1})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<3;i++) { array[i] = ((int[])	{3, 2, 1})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<7;i++) { array[i] = ((int[])	{1, 2, 3, 4, 5, 6, 7})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<9;i++) { array[i] = ((int[]) {9, 8, 7, 6, 5, 4, 3, 2, 1})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<5;i++) { array[i] = ((int[]) {2, 1, 2, 1, 2})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<4;i++) { array[i] = ((int[]) {5, 5, 5, 5})[i]; }
    sort_print(array, i, MERGE);
    */
    int* array = (int*)malloc(sizeof(int)*30);
    int i = 0;
    for (i=0;i<8;i++) { array[i] = ((int[]) {8, 3, 5, 1, 7, 2, 6, 4})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<16;i++) { array[i] = ((int[]) {16, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<17;i++) { array[i] = ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]; }
    sort_print(array, i, MERGE);
    printf("Feed Start\n");
    gaesi* g = (gaesi*)malloc(sizeof(gaesi)*200000);\
    heap* h;
    heap_create_heap(&h, 200000, MAX_HEAP);
    for (int i=0;i<200000;i++) {
        (g+i)->good = (rand()% 1000)*(rand()% 1000);
        (g+i)->time = rand() % 1023 + 20260000; // 현재 시각
        int weight = (g+i)->good - (20261023 - (g+i)->time) * 100;
        heap_push(h, &weight, &i);
    }
    for (int i=0;i<10;i++) {
        int weight;
        int index;
        heap_pop(h, &weight, &index);
        printf("good = %d, time = %d, weight = %d\n", (g+index)->good, (g+index)->time, weight);
    }
    free(g);
    heap_delete_heap(h);
    printf("Feed End\n");
    printf("Heap Start\n");
    heap_create_heap(&h, 17, MIN_HEAP);
    printf("heap : ");
    for (i=0;i<17;i++) { array[i] = ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]; }
    for (int i=0;i<17;i++) {
        heap_push(h, array+i, array+i);
        printf("%d ", array[i]);
    }
    printf("in\n");
    printf("heap : ");
    for (int i=0;i<17;i++) {
        int tmp;
        heap_pop(h, &tmp, &tmp);
        printf("%d ", tmp);
    }
    printf("out\n");
    printf("Heap End\n");
    heap_delete_heap(h);

    return 0;
}