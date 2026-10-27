#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "hash.h"
#include "sort.h"
#include "heap.h"
#include "interface.h"
#include "dataset.h"

#pragma region 내부_함수
void printreq1(void* item) {
    printf("UID : %d, index : %d\n", ((graphnode*)item)->item, ((graphnode*)item)->index);
}
void graph_print(void* node) { graph_print_node((graphnode*)node); }
graph* test_graph_create() {
    graph* graph;
    graph = graph_create_graph();
    int dataset_vertex[] = {4, 2, 7, 1, 5, 3};
    int dataset_edge_start[] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};
    int dataset_edge_end[] = {2, 3, 4, 3, 5, 4, 6, 5, 6, 6};
    for (int i = 0; i < (int)sizeof(dataset_vertex)/(int)sizeof(dataset_vertex[0]); i++) {
        graph_insert_vertex(graph, dataset_vertex[i]);
    }
    for (int i = 0; i < (int)sizeof(dataset_edge_start)/(int)sizeof(dataset_edge_start[0]); i++) {
        graph_insert_edge(graph, dataset_edge_start[i] - 1, dataset_edge_end[i] - 1);
    }
    return graph;
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
int requirement1_1 (universe* universe, int UID_you) {
    int result = EXIT_SUCCESS;
    hashnode* search = hash_peek(universe->UID_to_user, &UID_you);
    if(search == NULL) { printf("존재하지 않는 UID입니다.\n"); return ERANGE; }
    else {
        list* friends_friends = dijkstra_find_within_distance(universe->graph, ((graphnode*)(search->item))->index, 2, EXCL);
        if (friends_friends != NULL) {
            printf("--- 다리 건너 친구 목록 ---(총 = %d)\n", list_get_length(friends_friends));
            list_print_list(friends_friends, &printreq1);
            list_clear_list(&friends_friends);
            printf("--- ----- ---\n");
        }
        else result = ENOMEM;
    }
    return result;
}

int requirement1_2 (universe* universe, int UID_a, int UID_b) {
    if (UID_a == UID_b) { printf("같은 유저입니다.\n"); return EINVAL; }
    int result = EXIT_SUCCESS;
    int* path;
    hashnode* search_a = hash_peek(universe->UID_to_user, &UID_a);
    hashnode* search_b = hash_peek(universe->UID_to_user, &UID_b);
    if (search_a == NULL || search_b == NULL) { printf("존재하지 않는 UID입니다.\n"); result = ERANGE; }
    else {
        int min = dijkstra_find_between_path(universe->graph, ((graphnode*)(search_a->item))->index, ((graphnode*)(search_b->item))->index, &path);
        if (min == -ERANGE) printf("연결되어 있지 않습니다.\n");
        else if (min != -ENOMEM) {
            printf("최소 연결 촌수 : %d\n[ ", min);
            for(int i=0;i<min;i++) printf("%d - ", universe->UID_array[path[min-i]]);
            printf("%d ]\n", universe->UID_array[path[0]]);
            free(path);
        }
        else printf("메모리 할당에 실패했습니다.\n");
    }
    return result;
}

int requirement2_1 (universe* universe, int UID_input) {
    hashnode* hashnode = hash_peek(universe->UID_to_user, &UID_input);
    if (hashnode == NULL) {
        printf("존재하지 않는 UID입니다\n");
        return ERANGE;
    }
    graphnode* user = ((graphnode*)(hashnode->item));
    list* posts = hash_peek_bucket_item(universe->UID_to_posts, &UID_input);
    printf("이름 : %.8s\n유저 ID : %d\n", universe->name_array+(user->index)*8, UID_input);
    if (user->adjustNodes->length == 0) printf("친구가 없습니다... 친구가 되어볼까요?\n");
    else {
        printf("유저 친구 수 : %d\n-- 친구 목록 --\n", user->adjustNodes->length);
        for(int i=0;i<user->adjustNodes->length;i++) printf("%d\n", universe->UID_array[((graphnode*)list_get_at(user->adjustNodes, i))->index]);
    }
    if (posts == NULL) {
        printf("작성물 목록을 불러오지 못했습니다.\n");
        return ENOMEM;
    }
    else {
        if (posts->length == 0) printf("작성물이 없습니다.\n");
        else{
            printf("-- 작성 게시물 목록 --\n");
            for(int i=0;i<posts->length;i++) {
                post* p = (post*)list_get_at(posts, i);
                printf("%d시간 전, 좋아요 : %d\n", p->time, p->good);
                for(int j=0;j<3;j++) if (p->hashtag[j] != NULL) printf("#%.4s ", p->hashtag[j]);
                printf("\n");
        }printf("-- ----- --\n");}
        list_clear_list(&posts);
    }
    return EXIT_SUCCESS;
}

int requirement2_2 (universe* universe, char* hashtag_input) {
    if (hashtag_input == NULL) { printf("잘못된 문자열입니다.\n"); return EINVAL; }
    int i;
    for(i=0;i<5;i++) if(hashtag_input[i] == '\0') { break; }
    if (i != 4) { printf("해시태그는 4글자만 허용됩니다.\n"); return EINVAL; }
    for(i=0;i<4;i++) if(hashtag_input[i] < 'a' || 'z' < hashtag_input[i]) { printf("해시태그는 영어만 허용됩니다.\n"); return EINVAL; }
    list* posts = hash_peek_bucket_item(universe->hashtag_to_posts, hashtag_input);
    if (posts == NULL) {
        printf("게시물을 불러오지 못했습니다.\n");
        return ENOMEM;
    }
    if (posts->length == 0) {
        printf("존재하지 않는 해시태그입니다\n");
        list_clear_list(&posts);
        return ERANGE;
    }
    printf("-- 해당 게시물 목록 --\n");
    for(int i=0;i<posts->length;i++) {
        post* p = (post*)list_get_at(posts, i);
        printf("%d시간 전, 좋아요 : %d\n", p->time, p->good);
        for(int j=0;j<3;j++) if (p->hashtag[j] != NULL) printf("#%.4s ", p->hashtag[j]);
        printf("\n");
    }
    printf("-- ----- --\n");
    list_clear_list(&posts);
    return EXIT_SUCCESS;
}

int requirement3 (universe* universe) {
    int weight[10], index[10], i;
    int length = universe->feed->cur_size;
    if (length > 10) length = 10; //최대 10개만
    printf("-- 피드 상위 %d개 목록 --\n", length);
    for(i=0;i<length;i++) {
        if (heap_pop(universe->feed, weight+i, index+i) != EXIT_SUCCESS) break;
        post* p = universe->posts+index[i];
        printf("%d시간 전, 좋아요 : %d\n", p->time, p->good);
        for(int j=0;j<3;j++) if (p->hashtag[j] != NULL) printf("#%.4s ", p->hashtag[j]);
        printf("\n");
    }
    printf("-- ----- --\n");
    for (int j=0;j<i;j++) heap_push(universe->feed, weight+j, index+j);
    return EXIT_SUCCESS;
}

int requirement4 (universe* universe) {
    if (universe->rank[0] == -1) {
        if (dataset_refresh_rank(universe->rank, universe->graph->nodes) == ENOMEM) {printf("정렬에 실패하였습니다.\n"); return ENOMEM; }
    }
    printf("--- 랭킹 목록 ---\n");
    for(int i=0;i<50;i++) printf("%d위 : %d명, ID-%d 이름-%.8s\n", i+1, universe->rank[i*2], universe->graph->nodes[universe->rank[i*2+1]]->item, universe->name_array+universe->rank[i*2+1]*8);
    printf("--- ----- ---\n");
    return EXIT_SUCCESS;
}

int get_input(int num, int subnum, void* arg1, void* arg2) {
    if (num == 0) {
        printf("기능 번호를 입력하세요 : ");
        while (!scanf("%d", (int*)arg1)) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    if (num == 1 && subnum == 1) {
        printf("다리 건너 아는 친구 기능의 유저를 입력하세요 : ");
        while (!scanf("%d", (int*)arg1)) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    if (num == 1 && subnum == 2) {
        printf("최단 연결 촌수 계산 기능의 두 유저를 입력하세요 : ");
        while (scanf("%d %d", (int*)arg1, (int*)arg2)!=2) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    if (num == 2 && subnum == 1) {
        printf("UID를 입력하세요 : ");
        while (!scanf("%d", (int*)arg1)) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    if (num == 2 && subnum == 2) {
        printf("해시태그를 입력하세요 : ");
        while (!scanf("%8s", (char*)arg1)) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    if (num == 5) {
        printf("테스트 번호를 입력하십시오(help = 0) : ");
        while (!scanf("%d", (int*)arg1)) {
            while (getchar() != '\n') {}
            printf("다시 입력해 주세요 : ");
        }
        return EXIT_SUCCESS; }
    return EINVAL;
}

int interface_init_universe(universe* u) {
    if (u == NULL) return EINVAL;
    if (u->graph            != NULL) graph_delete_graph(u->graph);
    if (u->UID_to_user      != NULL) hash_delete_hash(u->UID_to_user);
    if (u->UID_to_posts     != NULL) hash_delete_hash(u->UID_to_posts);
    if (u->hashtag_to_posts != NULL) hash_delete_hash(u->hashtag_to_posts);
    if (u->feed             != NULL) heap_delete_heap(u->feed);
    if (u->rank             != NULL) free(u->rank);
    if (u->posts            != NULL) free(u->posts);
    free(u); return EXIT_SUCCESS;
}

int interface_create_universe(universe** u) {
    *u = (universe*)malloc(sizeof(universe));
    if (*u == NULL) return ENOMEM;
    (*u)->graph = NULL;
    (*u)->posts = NULL;

    (*u)->UID_to_user       = NULL;
    (*u)->UID_to_posts      = NULL;
    (*u)->hashtag_to_posts  = NULL;
    (*u)->feed              = NULL;
    (*u)->rank              = NULL;
    
    dataset_make_name_array((*u)->name_array);
    dataset_make_hashtag_array((*u)->hashtag_array);

    if (((*u)->graph = graph_create_graph())                                        == NULL ) { interface_init_universe(*u); return ENOMEM; }
    dataset_make_vertex((*u)->graph);
    dataset_make_edge((*u)->graph);

    if (dataset_make_UID_both(&((*u)->UID_to_user), (*u)->UID_array, (*u)->graph)   == ENOMEM) { interface_init_universe(*u); return ENOMEM; }
    if (heap_create_heap(&((*u)->feed), POST_NUM, MAX_HEAP)                         == ENOMEM) { interface_init_universe(*u); return ENOMEM; }
    if (dataset_make_post(&((*u)->posts), (*u)->UID_array, (*u)->hashtag_array)     == ENOMEM) { interface_init_universe(*u); return ENOMEM; }
    if (dataset_make_feed((*u)->feed, (*u)->posts)                                  == ENOMEM) { interface_init_universe(*u); return ENOMEM; }
    if (dataset_make_hashtag_to_post(&((*u)->hashtag_to_posts), (*u)->posts)        == ENOMEM) { interface_init_universe(*u); return ENOMEM; }
    if (dataset_make_UID_to_posts(&((*u)->UID_to_posts), (*u)->posts)               == ENOMEM) { interface_init_universe(*u); return ENOMEM; }

    if (((*u)->rank  = (int*)malloc(sizeof(int)*VERTEX_NUM*2))                      == NULL  ) { interface_init_universe(*u); return ENOMEM; }
    (*u)->rank[0] = -1;

    return EXIT_SUCCESS;
}

int test_merge() {
    int* array = (int*)malloc(sizeof(int)*30);
    int i = 0;

    for (i=0;i<2;i++) { array[i] = ((int[]){2, 1})[i]; }
    sort_print(array, i, MERGE, LOW);

    for (i=0;i<3;i++) { array[i] = ((int[])	{3, 2, 1})[i]; }
    sort_print(array, i, MERGE, HIGH);

    for (i=0;i<7;i++) { array[i] = ((int[])	{1, 2, 3, 4, 5, 6, 7})[i]; }
    sort_print(array, i, MERGE, LOW);

    for (i=0;i<9;i++) { array[i] = ((int[]) {9, 8, 7, 6, 5, 4, 3, 2, 1})[i]; }
    sort_print(array, i, MERGE, HIGH);

    for (i=0;i<5;i++) { array[i] = ((int[]) {2, 1, 2, 1, 2})[i]; }
    sort_print(array, i, MERGE, LOW);

    for (i=0;i<4;i++) { array[i] = ((int[]) {5, 5, 5, 5})[i]; }
    sort_print(array, i, MERGE, HIGH);
    
    for (i=0;i<8;i++) { array[i] = ((int[]) {8, 3, 5, 1, 7, 2, 6, 4})[i]; }
    sort_print(array, i, MERGE, LOW);

    for (i=0;i<16;i++) { array[i] = ((int[]) {16, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8})[i]; }
    sort_print(array, i, MERGE, HIGH);

    for (i=0;i<17;i++) { array[i] = ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]; }
    sort_print(array, i, MERGE, LOW);

    free(array);
    return EXIT_SUCCESS;
}

int test_graph_main() {
    graph* graph = test_graph_create();
    graph_BFS(graph, 5);
    graph_DFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_BFS() {
    graph* graph = test_graph_create();
    graph_BFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_DFS() {
    graph* graph = test_graph_create();
    graph_DFS(graph, 5);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_graph_dijkstra() {
    graph* graph = test_graph_create();
    dijkstra_package* pac = dijkstra(graph, 5, NULL, NULL);
    if(pac == NULL) return ENOMEM;
    printf("Dijkstra Start\n");
    for(int i=0;i<pac->length;i++) {
        printf("%d ", pac->distance[i]);
    }
    printf("Dijkstra End\n");
    graph_delete_graph(graph);
    free(pac->visited);
    free(pac->distance);
    free(pac->parent);
    free(pac);
    return EXIT_SUCCESS;
}

int test_hash() {
    graph* graph = test_graph_create();
    char* dataset_hashtag[] = {"onee", "twoo", "thre", "four", "five", "sixx"};
    unsigned int* dataset_UID[] = {&(unsigned int){1}, &(unsigned int){11}, &(unsigned int){111}, &(unsigned int){1111}, &(unsigned int){11111}, &(unsigned int){111111}};
    hash* hashS = hash_create_hash(3, STRING);
    hash* hashI = hash_create_hash(3, UNSIGNEDINT);
    for (int i = 0; i < 6; i++) {
        hash_push(hashS, graph->nodes[i], dataset_hashtag[i]);
        hash_push(hashI, graph->nodes[i], dataset_UID[i]);
    }
    hash_print_node(hash_pop(hashS, "twoo"), &graph_print);
    hash_print_node(hash_peek(hashS, "twoo"), &graph_print);
    hash_print_node(hash_pop(hashS, "sevn"), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_peek(hashI, &(unsigned int){11}), &graph_print);
    hash_print_node(hash_pop(hashI, &(unsigned int){1111111}), &graph_print);
    graph_delete_graph(graph);
    return EXIT_SUCCESS;
}

int test_heap_feed() {
    printf("Feed Start\n");
    post* g = (post*)malloc(sizeof(post)*200000);
    heap* h;
    heap_create_heap(&h, 200000, MAX_HEAP);
    for (int i=0;i<200000;i++) {
        (g+i)->good = (rand() % 1000) * 1000 + (rand() % 1000); //0~100만, 좋아요 수
        (g+i)->time = rand() % 7142;                            //0~7142, 경과한 시간
        int weight = (g+i)->good - (g+i)->time * 14;
        heap_push(h, &weight, &i);
    }
    for (int i=0;i<10;i++) {
        int weight;
        int index;
        heap_pop(h, &weight, &index);
        printf("good = %d, time = %d, weight = %d\n", (g+index)->good, (g+index)->time, weight);
    }
    free(g);
    heap_delete_heap(h);
    printf("Feed End\n");
    return EXIT_SUCCESS;
}

int test_heap_main() {
    printf("Heap Start\n");
    heap* h;
    heap_create_heap(&h, 17, MIN_HEAP);
    printf("heap : ");
    for (int i=0;i<17;i++) {
        heap_push(h, (int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16}+i, (int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16}+i);
        printf("%d ", ((int[]) {17, 9, 4, 13, 1, 12, 7, 15, 3, 10, 6, 14, 2, 11, 5, 8, 16})[i]);
    }
    printf("in\n");
    printf("heap : ");
    for (int i=0;i<17;i++) {
        int tmp;
        heap_pop(h, &tmp, &tmp);
        printf("%d ", tmp);
    }
    printf("out\n");
    printf("Heap End\n");
    return EXIT_SUCCESS;
}

#pragma endregion