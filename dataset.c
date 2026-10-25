#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "dataset.h"

#pragma region 내부_함수
// 내부 함수

#pragma endregion

#pragma region 외부_함수
// 외부 함수
void dataset_make_vertex(graph* g) {
    for (int i=0;i<VERTEX_NUM;i++) graph_insert_vertex(g, i);
}
void dataset_make_edge(graph* g) {
    int index_a, index_b;
    
    //아무튼 랜덤으로 두 정점 잡음
    for (int inserted_edge = 0;inserted_edge<EDGE_NUM;) {
        index_a = ((rand() % 32768) * 32768 + (rand() % 32768))%VERTEX_NUM;
        index_b = ((rand() % 32768) * 32768 + (rand() % 32768))%VERTEX_NUM;
        if (index_a != index_b && !graph_is_adjacent(g, index_a, index_b)) {
            graph_insert_edge(g, index_a, index_b);
            inserted_edge++;
        }
    } 
}
void dataset_out_graph(graph* g) {
    //아무튼 내보냄
}
#pragma endregion