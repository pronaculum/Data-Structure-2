#ifndef INTERFACE_H
#define INTERFACE_H
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "hash.h"
#include "sort.h"
#include "heap.h"
#include "dataset.h"

// 맨날 하는거
typedef struct universe     universe;


struct universe {
    graph*  graph;
    hash*   UID;
    int*    UIDarray[VERTEX_NUM*2];
    heap*   feed;
    int*    rank;
    post*   post;
    char*   name;
    char*   tag; //해시태그 출력할땐 항상 \0 붙이기
};


// 외부 함수
int requirement1_1 (universe* universe, int index_you);
int requirement1_2 (universe* universe, int index_a, int index_b);
int requirement2 (universe* universe);
int requirement3 (universe* universe);
int requirement4 (universe* universe);
int test_merge();
int test_graph_main();
int test_graph_BFS();
int test_graph_DFS();
int test_graph_dijkstra();
int test_hash();
int test_heap_feed();
int test_heap_main();

#endif