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
    post*   posts;

    hash*   UID_to_user;
    hash*   UID_to_posts;
    hash*   hashtag_to_posts;
    heap*   feed;
    int*    rank;

    char    name_array[VERTEX_NUM*8];
    int     UID_array[VERTEX_NUM];
    char    hashtag_array[HASHTAG_NUM*4]; //해시태그 \0 없음
};


// 외부 함수
int requirement1_1 (universe* universe, int index_you);
int requirement1_2 (universe* universe, int index_a, int index_b);
int requirement2_1 (universe* universe, int UID_input);
int requirement2_2 (universe* universe, char* hashtag_input);
int requirement3 (universe* universe);
int requirement4 (universe* universe);
int get_input(int num, int subnum, void* arg1, void* arg2);
int interface_init_universe(universe* u);
int interface_create_universe(universe** u);
int test_merge();
int test_graph_main();
int test_graph_BFS();
int test_graph_DFS();
int test_graph_dijkstra();
int test_hash();
int test_heap_feed();
int test_heap_main();

#endif