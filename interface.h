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

typedef struct gaesi        gaesi;
typedef struct universe     universe;

struct gaesi {
    int     good;
    int     time;
};
struct universe {
    graph*  graph;
    hash*   idk;
    heap*   peed;
    int*    rank;
    gaesi*  gaesis;
};


// 외부 함수
int requirement1_1 (universe* universe, int index_you);
int requirement1_2 (universe* universe, int index_a, int index_b);
int requirement2 (universe* universe);
int requirement3 (universe* universe);
int requirement4 (universe* universe);

#endif