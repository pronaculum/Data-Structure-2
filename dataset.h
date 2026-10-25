#ifndef DATA_H
#define DATA_H
#include "list.h"
#include "graph.h"

#define VERTEX_NUM 100000
#define EDGE_NUM 500000

// 맨날 하는거
/*
typedef struct listnode listnode;
typedef struct list     list;

typedef void*           listdata;
typedef listnode*       listlink;

struct listnode
{
    listdata item;
    listlink next;
};
struct list
{
    listnode* root;
    listnode* tail;
    int length;
};
*/
// 외부 함수
void dataset_make_vertex(graph* g);
void dataset_make_edge(graph* g);
void dataset_out_graph(graph* g);
#endif