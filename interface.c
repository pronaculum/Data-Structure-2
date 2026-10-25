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
#include "dataset.h"

#pragma region 내부_함수
void printreq1(void* item) {
    printf("item : %d, index : %d\n", ((graphnode*)item)->item, ((graphnode*)item)->index);
}
void graph_print(void* node) { graph_print_node((graphnode*)node); }
graph* test_graph_create() {
    graph* graph;
    graph = graph_create_graph();
    int dataset_vertex[] = {4, 2, 7, 1, 5, 3};
    int dataset_edge_start[] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};
    int dataset_edge_end[] = {2, 3, 4, 3, 5, 4, 6, 5, 6, 6};
    for (int i = 0; i < (int)sizeof(dataset_vertex)/(int)sizeof(dataset_vertex[0]); i++) {
        graph_insert_vertex(graph, dataset_vertex[i]);
    }
    for (int i = 0; i < (int)sizeof(dataset_edge_start)/(int)sizeof(dataset_edge_start[0]); i++) {
        graph_insert_edge(graph, dataset_edge_start[i] - 1, dataset_edge_end[i] - 1);
    }
    return graph;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
int requirement1_1 (universe* universe, int index_you) {
    int result = EXIT_SUCCESS;
    if(index_you < 0 || universe->graph->length <= index_you) result = ERANGE;
    else {
        list* friends_friends = dijkstra_find_within_distance(universe->graph, index_you, 2, EXCL);
        if (friends_friends != NULL) {
            printf("friend's friends : (total = %d)\n", list_get_length(friends_friends));
            list_print_list(friends_friends, &printreq1);
            list_clear_list(&friends_friends);
            printf("friend's friends End\n");
        }
        else result = ENOMEM;
    }
    return result;
}

int requirement1_2 (universe* universe, int index_a, int index_b) {
    int result = EXIT_SUCCESS;
    if      (index_a < 0 || universe->graph->length <= index_a) result = ERANGE;
    else if (index_b < 0 || universe->graph->length <= index_b) result = ERANGE;
    else {
        int min = dijkstra_find_between(universe->graph, index_a, index_b);
        if(min == -1)  printf("고립되어 있습니다.\n");
        else            printf("최소 연결 촌수 : %d\n", min);
    }
    return result;
}

int requirement2 (universe* universe);

int requirement3 (universe* universe);

int requirement4 (universe* universe);

int test_merge() {
    int* array = (int*)malloc(sizeof(int)*30);
    int i = 0;

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
    
    for (i=0;i<8;i++) { array[i] = ((int[]) {8, 3, 5, 1, 7, 2, 6, 4})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<16;i++) { array[i] = ((int[]) {16, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8})[i]; }
    sort_print(array, i, MERGE);

    for (i=0;i<17;i++) { array[i] = ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]; }
    sort_print(array, i, MERGE);

    free(array);
    return EXIT_SUCCESS;
}

int test_graph_main() {
    graph* graph = test_graph_create();
    graph_BFS(graph, 5);
    graph_DFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_BFS() {
    graph* graph = test_graph_create();
    graph_BFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_DFS() {
    graph* graph = test_graph_create();
    graph_DFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_dijkstra() {
    graph* graph = test_graph_create();
    dijkstra_package* pac = dijkstra(graph, 5, NULL, NULL);
    if(pac == NULL) return ENOMEM;
    printf("Dijkstra Start\n");
    for(int i=0;i<pac->length;i++) {
        printf("%d ", pac->distance[i]);
    }
    printf("Dijkstra End\n");
    graph_delete_graph(graph);
    free(pac->visited);
    free(pac->distance);
    free(pac->parent);
    free(pac);
    return EXIT_SUCCESS;
}

int test_hash() {
    graph* graph = test_graph_create();
    char* dataset_hashtag[] = {"onee", "twoo", "thre", "four", "five", "sixx"};
    unsigned int* dataset_UID[] = {&(unsigned int){1}, &(unsigned int){11}, &(unsigned int){111}, &(unsigned int){1111}, &(unsigned int){11111}, &(unsigned int){111111}};
    hash* hashS = hash_create_hash(3, STRING);
    hash* hashI = hash_create_hash(3, UNSIGNEDINT);
    for (int i = 0; i < 6; i++) {
        hash_push(hashS, graph->nodes[i], dataset_hashtag[i]);
        hash_push(hashI, graph->nodes[i], dataset_UID[i]);
    }
    hash_print_node(hash_pop(hashS, "twoo"), &graph_print);
    hash_print_node(hash_peek(hashS, "twoo"), &graph_print);
    hash_print_node(hash_pop(hashS, "sevn"), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_peek(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){1111111}), &graph_print);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_heap_feed() {
    printf("Feed Start\n");
    gaesi* g = (gaesi*)malloc(sizeof(gaesi)*200000);
    heap* h;
    heap_create_heap(&h, 200000, MAX_HEAP);
    for (int i=0;i<200000;i++) {
        (g+i)->good = (rand() % 1000) * 1000 + (rand() % 1000); //0~100만, 좋아요 수
        (g+i)->time = rand() % 7142;                            //0~7142, 경과한 시간
        int weight = (g+i)->good - (g+i)->time * 14;
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
    return EXIT_SUCCESS;
}

int test_heap_main() {
    printf("Heap Start\n");
    heap* h;
    heap_create_heap(&h, 17, MIN_HEAP);
    printf("heap : ");
    for (int i=0;i<17;i++) {
        heap_push(h, (int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16}+i, (int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16}+i);
        printf("%d ", ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]);
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
    return EXIT_SUCCESS;
}

#pragma endregion