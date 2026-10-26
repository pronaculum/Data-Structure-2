#ifndef DATA_H
#define DATA_H
#include "list.h"
#include "graph.h"

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
    char*   hashtag1[3];
    char*   hashtag2[3];
    char*   hashtag3[3];
    char*   hashtag4[3];
};
// 외부 함수
void dataset_make_vertex(graph* g);
void dataset_make_edge(graph* g);
void dataset_make_hashtag(char* hashtag);
int dataset_make_name(char* name);
int dataset_make_post(post** p);
void dataset_out_graph(graph* g);
int dataset_random_int(int max);
#endif