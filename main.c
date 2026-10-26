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



int main(void) {
    universe* u;
    if (interface_create_universe(&u)) { printf("유니버스 생성에 실패하였습니다.\n프로그램을 종료합니다..."); return ENOMEM; }
    while (1) {
        int input = 0;
        int index_you, index_a, index_b, testnum;
        char hashtag[9];
        printf("입력하십시오 : ");
        scanf("%d", &input);
        if(input == 0) break; //0 입력시 종료
        switch (input)
        {
        case 1:
            printf("요구사항 1이 입력되었습니다.\n");
            printf("다리 건너 아는 친구 기능의 유저를 입력하세요 : ");
            scanf("%d", &index_you);
            requirement1_1(u, index_you);
            printf("최단 연결 촌수 계산 기능의 두 유저를 입력하세요 : ");
            scanf("%d %d", &index_a, &index_b);
            requirement1_2(u, index_a, index_b);
            break;
        case 2:
            printf("요구사항 2가 입력되었습니다.\n");
            printf("UID를 입력하세요 : ");
            scanf("%d", &index_you);
            requirement2_1(u, index_you);
            printf("해시태그를 입력하세요 : ");
            scanf("%8s", hashtag);
            requirement2_2(u, hashtag);
            break;
        case 4:
            requirement4(u);
            break;
        case 5:
            printf("테스트 번호를 입력하십시오(help = 0) : ");
            scanf("%d", &testnum);
            switch (testnum)
            {
            case 0: printf(
            "1 : test_hash\n2 : test_heap_main\n3 : test_heap_feed\n4 : test_graph_BFS\n5 : test_graph_DFS\n6 : test_graph_dijkstra\n7 : test_graph_main\n8 : test_merge\n");
            break;
            case 1: test_hash(); break;
            case 2: test_heap_main(); break;
            case 3: test_heap_feed(); break;
            case 4: test_graph_BFS(); break;
            case 5: test_graph_DFS(); break;
            case 6: test_graph_dijkstra(); break;
            case 7: test_graph_main(); break;
            case 8: test_merge(); break;
            case 9: break;
            default: printf("잘못된 입력입니다.\n"); break;
            }
            break;
        default:
            break;
        }
    }
    interface_init_universe(u);
    return 0;
}