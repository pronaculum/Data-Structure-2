#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "sort.h"
#include "heap.h"
#include "hash.h"
#include "dataset.h"

#pragma region 내부_함수
// 내부 함수
unsigned int LCG(unsigned int x, int m, int c, int a) {
    return (a * x + c) % m;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
void dataset_make_vertex(graph* g) {  //finish
    for (int i=0;i<VERTEX_NUM;i++) graph_insert_vertex(g, i*1000+dataset_random_int(1000));
}
void dataset_export_vertex(graph* g, FILE* file) {  //finish
    for (int i=0;i<VERTEX_NUM;i++) fprintf(file, "%d ", i*1000+dataset_random_int(1000));
}
void dataset_import_vertex(graph* g, FILE* file) {  //finish
    int input;
    for (int i=0;i<VERTEX_NUM;i++) {
        fscanf(file, "%d ", &input);
        graph_insert_vertex(g, input);
    }

}
void dataset_make_edge(graph* g) {  //finish
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
void dataset_make_hashtag_array(char* hashtag_array) {  //finish
    unsigned int x = dataset_random_int(ALPHABET_NUM);
    unsigned int result;
    for(int i=0;i<HASHTAG_NUM;i++) {
        int c = 17; //2와 13의 배수가 아닌 적절한 수
        int a = 521; //보다 1 작은 값이 4와 13의 배수
        int m = ALPHABET_NUM;
        x = LCG(x, m, c, a);
        result = x;
        hashtag_array[i*4+0] = result%26+'a';result/=26;
        hashtag_array[i*4+1] = result%26+'a';result/=26;
        hashtag_array[i*4+2] = result%26+'a';result/=26;
        hashtag_array[i*4+3] = result%26+'a';result/=26;
    }
}
int dataset_make_hashtag_to_post(hash** hashtag, post* p) {  //finish
    *hashtag = hash_create_hash(HASHTAG_NUM, STRING);
    if(*hashtag == NULL) return ENOMEM;
    for(int i=0;i<POST_NUM;i++) {
        hash_push_hard(*hashtag, p+i, (p+i)->hashtag[0]);
        if ((p+i)->hashtag[1] != NULL) {
            hash_push_hard(*hashtag, p+i, (p+i)->hashtag[1]);
            if ((p+i)->hashtag[2] != NULL) hash_push_hard(*hashtag, p+i, (p+i)->hashtag[2]);
        }
    }
    return EXIT_SUCCESS;
}
int dataset_make_name_array(char* name_array) {  //finish
    unsigned int x = dataset_random_int(ALPHABETEXTRA_DIVIDED_NUM);
    unsigned int result;
    for(int i=0;i<VERTEX_NUM;i++) {
        int c = 17; //37의 배수가 아닌 적절한 수
        int a = 75; //보다 1 작은 값이 37의 배수
        int m = ALPHABETEXTRA_DIVIDED_NUM;
        for(int j=0;j<2;j++) {
            x = LCG(x, m, c, a);
            result = x;
            for(int k=0;k<4;k++) {
                if      (result % 37 == 0)  name_array[i*8+j*4+k]    = '_';
                else if (result % 37 <= 10) name_array[i*8+j*4+k]    = '0' + result % 37 - 1;
                else                        name_array[i*8+j*4+k]    = 'a' + result % 37 - 11;
                result/=37;
            }
        }
    }
    return EXIT_SUCCESS;
}
int dataset_make_UID_both(hash** UID_to_user, int* UID_array, graph* graph) {  //finish
    *UID_to_user = hash_create_hash(VERTEX_NUM, UNSIGNEDINT);
    if (*UID_to_user == NULL) return ENOMEM;
    unsigned int x = dataset_random_int(VERTEX_NUM);
    int c = 17; //10의 배수가 아닌 적절한 수
    int a = 81; //보다 1 작은 값이 20의 배수
    int m = VERTEX_NUM;
    for(int i=0;i<VERTEX_NUM;i++) {
        x = LCG(x, m, c, a);
        UID_array[i] = x;
        graph->nodes[i]->item = x;
        hash_push(*UID_to_user, graph->nodes[i], UID_array+i);
    }
    return EXIT_SUCCESS;
}
int dataset_make_UID_to_posts(hash** UID_to_posts, post* p) {  //UID 없는건 포스트에 있어서
    *UID_to_posts = hash_create_hash(POST_NUM, UNSIGNEDINT);
    if (*UID_to_posts == NULL) return ENOMEM;
    for(int i=0;i<POST_NUM;i++) { hash_push_hard(*UID_to_posts, p+i, &(p+i)->UID); }
    return EXIT_SUCCESS;
}
int dataset_make_post(post** p, int* UID_array, char* hashtag_array) {
    *p = (post*)malloc(sizeof(post)*POST_NUM);
    if(*p == NULL) return ENOMEM;
    for (int i=0;i<POST_NUM;i++) {
        (*p+i)->good = (rand() % 1000) * 1000 + (rand() % 1000); //0~100만, 좋아요 수
        (*p+i)->time = rand() % 7142;                            //0~7142, 경과한 시간
        (*p+i)->UID  = UID_array[dataset_random_int(VERTEX_NUM)];
        int hashtag1 = dataset_random_int(HASHTAG_NUM);
        int hashtag2 = -1;
        int hashtag3 = -1;
        if (dataset_random_int(2)) {
            hashtag2 = dataset_random_int(HASHTAG_NUM);
            while (hashtag1 == hashtag2) hashtag2 = dataset_random_int(HASHTAG_NUM);
            if (dataset_random_int(2)) {
                hashtag3 = dataset_random_int(HASHTAG_NUM);
                while (hashtag1 == hashtag2 || hashtag2 == hashtag3) hashtag3 = dataset_random_int(HASHTAG_NUM);
            }
        }
        (*p+i)->hashtag[0] = hashtag_array + hashtag1 * 4;
        (*p+i)->hashtag[1] = (hashtag2+1)?hashtag_array + hashtag2 * 4:NULL;
        (*p+i)->hashtag[2] = (hashtag3+1)?hashtag_array + hashtag3 * 4:NULL;
    }
    return EXIT_SUCCESS;
}
int dataset_make_feed(heap* h, post* p) {
    for(int i=0;i<POST_NUM;i++){
        int weight = (p+i)->good - (p+i)->time * 14;
        heap_push(h, &weight, &i);
    }
    return EXIT_SUCCESS;
}
int dataset_refresh_rank(int* rank, graphnode* nodes[]) {
    for(int i=0;i<VERTEX_NUM;i++) {
        rank[i*2] = nodes[i]->adjustNodes->length;
        rank[i*2+1] = nodes[i]->index;}
        sort_Merge(rank, VERTEX_NUM, DUAL_ARRAY_INT, HIGH);
}
void dataset_out_graph(graph* g) {
    //파일 내보내기 구현 예정
}
int dataset_random_int(int max) {
    return((rand()%RAND_NUM)*RAND_NUM + (rand()%RAND_NUM))%max;
}


#pragma endregion