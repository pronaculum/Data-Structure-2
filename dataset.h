#ifndef DATA_H
#define DATA_H
#include "list.h"
#include "graph.h"
#include "hash.h"

#define VERTEX_NUM 100000
#define EDGE_NUM 500000
#define RAND_NUM 32768
#define HASHTAG_NUM 50000
#define ALPHABET_NUM 456976
#define ALPHABETEXTRA_DIVIDED_NUM 1874161
#define POST_NUM 200000

// 맨날 하는거
typedef struct post post;
struct post {
    int     good;
    int     time;
    int     UID;
    char*   hashtag[3];
};
// 외부 함수
void dataset_make_vertex(graph* g);
void dataset_make_edge(graph* g);
void dataset_make_hashtag_array(char* hashtag_array);
int dataset_make_hashtag_to_post(hash** hashtag, post* p);
int dataset_make_name_array(char* name);
int dataset_make_UID_both(hash** UID, int* UID_array, graph* graph);
int dataset_make_UID_to_posts(hash** UID_to_posts, post* p);
int dataset_make_post(post** p, int* UID_array, char* hashtag);
int dataset_make_feed(heap* h, post* p);
int dataset_refresh_rank(int* rank, graphnode* nodes[]);
void dataset_out_graph(graph* g);
int dataset_random_int(int max);
#endif