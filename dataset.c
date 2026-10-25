#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "dataset.h"

#pragma region 내부_함수
// 내부 함수
unsigned int LCG(unsigned int x) {
    int m = ALPHABET_NUM;
    int c = 17; //2와 13의 배수가 아닌 적절한 수
    int a = 521; //보다 1 작은 값이 2와 13의 배수
    return (a * x + c) % m;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
void dataset_make_vertex(graph* g) {
    for (int i=0;i<VERTEX_NUM;i++) graph_insert_vertex(g, i*1000+dataset_random_int(1000));
}
void dataset_make_edge(graph* g) {
    int index_a, index_b;
    
    
    for (int inserted_edge = 0;inserted_edge<EDGE_NUM;) {
        index_a = dataset_random_int(VERTEX_NUM);
        index_b = dataset_random_int(VERTEX_NUM);
        if (index_a != index_b && !graph_is_adjacent(g, index_a, index_b)) { // 접하지 않는 임의의 다른 두 인덱스 index_a, index_b
            graph_insert_edge(g, index_a, index_b);
            inserted_edge++;
        }
    } 
}
void dataset_make_hashtag(char* hashtag) {
    unsigned int x = dataset_random_int(ALPHABET_NUM);
    unsigned int result;
    for(int i=0;i<HASHTAG_NUM;i++) {
        x = LCG(x);
        result = x;
        hashtag[i*4+0] = result%26+'a';result/=26;
        hashtag[i*4+1] = result%26+'a';result/=26;
        hashtag[i*4+2] = result%26+'a';result/=26;
        hashtag[i*4+3] = result%26+'a';result/=26;
    }
}
void dataset_out_graph(graph* g) {
    //파일 내보내기 구현 예정
}
int dataset_random_int(int max) {
    return((rand()%RAND_NUM)*RAND_NUM + (rand()%RAND_NUM))%max;
}


#pragma endregion