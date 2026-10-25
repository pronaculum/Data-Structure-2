#ifndef DATA_H
#define DATA_H
#include "list.h"
#include "graph.h"

#define VERTEX_NUM 100000
#define EDGE_NUM 500000
#define RAND_NUM 32768
#define HASHTAG_NUM 50000
#define ALPHABET_NUM 456976

// 맨날 하는거
typedef struct gaesi        gaesi;
struct gaesi {
    int     good;
    int     time;
    int     UID;
    char*   hashtag[3]; //해시태그 출력할땐 항상 \0 붙이기
};
// 외부 함수
void dataset_make_vertex(graph* g);
void dataset_make_edge(graph* g);
void dataset_make_hashtag(char* hashtag);
void dataset_out_graph(graph* g);
int dataset_random_int(int max);
#endif