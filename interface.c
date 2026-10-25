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
    printf("item : %d, index : %d\n", ((graphnode*)item)->item, ((graphnode*)item)->index);
}
#pragma endregion

#pragma region 외부_함수
// 외부 함수
int requirement1_1 (universe* universe, int index_you) {
    int result = EXIT_SUCCESS;
    if(index_you < 0 || universe->graph->length <= index_you) result = ERANGE;
    else {
        list* second_degree_relatives = dijkstra_find_within_distance(universe->graph, index_you, 2, EXCL);
        if (second_degree_relatives != NULL) {
            printf("show friend's friends Start\n");
            list_print_list(second_degree_relatives, &printreq1);
            list_clear_list(&second_degree_relatives);
            printf("show friend's friends End\n");
        }
        else result = ENOMEM;
    }
    return result;
}

int requirement1_2 (universe* universe, int index_a, int index_b) {
    int result = EXIT_SUCCESS;
    if      (index_a < 0 || universe->graph->length <= index_a) result = ERANGE;
    else if (index_b < 0 || universe->graph->length <= index_b) result = ERANGE;
    else {
        int chon = dijkstra_find_between(universe->graph, index_a, index_b);
        if(chon == -1)  printf("no link\n");
        else            printf("where are you : %d\n", chon);
    }
    return result;
}

int requirement2 (universe* universe);

int requirement3 (universe* universe);

int requirement4 (universe* universe);

#pragma endregion