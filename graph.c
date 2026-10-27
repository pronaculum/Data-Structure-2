#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"
#include "graph.h"
#include "heap.h"
#include "dataset.h"

#pragma region 내부_함수
// 내부 함수
graphnode* graph_create_graphnode(graphdata item) {
    graphnode* new_graphnode = (graphnode*)malloc(sizeof(graphnode));
    if(new_graphnode==NULL) return NULL;
    new_graphnode->index = -1;
    new_graphnode->item = item;
    new_graphnode->adjustNodes = list_create_list();
    return new_graphnode; 
}

int graph_compare_graphnode(void* a, void* b) {
    graphnode* node_a = (graphnode*)a;
    graphnode* node_b = (graphnode*)b;
    if (node_a->item == node_b->item) return 1;
    return 0;
}

void graph_delete_graphnode(graphnode* node) {
    if(node==NULL) return;
    while (node->adjustNodes->length > 0) {
        graphnode* me = node;
        graphnode* you = (graphnode*)(node->adjustNodes->root->item);
        list_delete_if(you->adjustNodes, me, graph_compare_graphnode);
        list_delete_if(me->adjustNodes, you, graph_compare_graphnode);
        //원래 다른거였는데 이쁘니까
    }
    list_clear_list(&(node->adjustNodes));
    free(node);
}

int graph_condition_is_unvisited(int* visited, graphnode* item) {
    if(visited[item->index]==0) return 1;
    return 0;
}

int dijkstra_find_between_condition(void* index, void* result) { return ((dijkstra_package*)result)->visited[*(int*)index]; }

int dijkstra_find_within_distance_condition(void* max_distance, void* result) { return ((dijkstra_package*)result)->distance[*(((dijkstra_package*)result)->curr_index)] > *(int*)max_distance; }
#pragma endregion

#pragma region 외부_함수
void graph_init_graph(graph* graph) {
    if(graph == NULL) return;
    for(int i=0;i<graph->length;i++) {
        list_clear_list(&(graph->nodes[i]->adjustNodes));
        free(graph->nodes[i]);
    }

    free(graph->nodes);
    graph->length = 0;
}

void graph_delete_graph(graph* graph) {
    if(graph == NULL) return;
    graph_init_graph(graph);
    free(graph);
}

graph* graph_create_graph() {
    graph* new_graph = (graph*)malloc(sizeof(graph));
    if(new_graph==NULL) return NULL;
    new_graph->nodes = NULL;
    new_graph->length = 0;
    return new_graph;
}

void graph_insert_vertex(graph* graph, graphdata item) {
    graphnode* new_node = graph_create_graphnode(item);
    if(new_node==NULL) return;
    if (graph->length > 0) graph->nodes = (graphnode**)realloc(graph->nodes, sizeof(graphnode*) * (graph->length * 2));
    else graph->nodes = (graphnode**)malloc(sizeof(graphnode*));
    new_node->index = graph->length;
    graph->nodes[graph->length] = new_node;
    graph->length++;
}

void graph_delete_vertex(graph* graph, int index) {
    if(index<0 || index>=graph->length) return;
    graph_delete_graphnode(graph->nodes[index]);
    for (int i = index; i < graph->length - 1; i++) {
        graph->nodes[i] = graph->nodes[i + 1];
        graph->nodes[i]->index = i;
    }
    graph->nodes = (graphnode**)realloc(graph->nodes, sizeof(graphnode*)*(graph->length-1));
    graph->length--;
}

void graph_insert_edge(graph* graph, int index_a, int index_b) {
    graphnode* graphnode_a = graph->nodes[index_a];
    graphnode* graphnode_b = graph->nodes[index_b];
    list_insert_at_tail(graphnode_a->adjustNodes, graphnode_b);
    list_insert_at_tail(graphnode_b->adjustNodes, graphnode_a);
}

void graph_delete_edge(graph* graph, int index_a, int index_b) {
    graphnode* graphnode_a = graph->nodes[index_a];
    graphnode* graphnode_b = graph->nodes[index_b];
    if(graphnode_a==NULL || graphnode_b==NULL) return;
    list_delete_if(graphnode_a->adjustNodes, graphnode_b, graph_compare_graphnode);
    list_delete_if(graphnode_b->adjustNodes, graphnode_a, graph_compare_graphnode);
}

int graph_is_adjacent(graph* graph, int index_a, int index_b) {
    graphnode* graphnode_a = graph->nodes[index_a];
    graphnode* graphnode_b = graph->nodes[index_b];
    if(graphnode_a==NULL || graphnode_b==NULL) return 0;
    if(list_get_if(graphnode_a->adjustNodes, graphnode_b, graph_compare_graphnode)==NULL) return 0;
    else return 1;
}

void graph_print_node(graphnode* node) {
    printf("index : [ %d ],\nitem : [ %d ],\nadjust nodes : [ ", node->index, node->item);
    for (int i=0;i<node->adjustNodes->length;i++) printf("%d ", ((graphnode*)list_get_at(node->adjustNodes, i))->index);
    printf("]\n");
}

void graph_BFS(graph* graph, int start_index) {
    if(start_index<0 || start_index>=graph->length) return;
    queue* queue = queue_create_queue(graph->length);
    int* visited = (int*)malloc(sizeof(int)*graph->length);
    if (visited == NULL) return;
    for (int i = 0; i < graph->length; i++) visited[i] = 0;
    queue_enqueue(queue, graph->nodes[start_index]);
    visited[start_index] = 1;
    printf("BFS Start\n");

    while (queue_is_empty(queue)==0) {
        graphnode* current_node = (graphnode*)queue_dequeue(queue);
        int current_index = current_node->index;
        printf("[current index : %d, item : %d ]\n", current_index, graph->nodes[current_index]->item);
        for (int i = 0; i < current_node->adjustNodes->length; i++) {
            graphnode* neighbor_node = (graphnode*)list_get_at(current_node->adjustNodes, i);
            if (visited[neighbor_node->index]==0) {
                queue_enqueue(queue, neighbor_node);
                visited[neighbor_node->index] = 1;
            }
        }
    }
    queue_delete_queue(queue);
    free(visited);
    printf("BFS End\n");
}

void graph_DFS(graph* graph, int start_index) {
    if(start_index<0 || start_index>=graph->length) return;
    stack* stack = stack_create_stack(graph->length);
    int* visited = (int*)malloc(sizeof(int)*graph->length);
    if (visited == NULL) return;
    for (int i = 0; i < graph->length; i++) visited[i] = 0;
    visited[start_index] = 1;
    stack_push(stack, graph->nodes[start_index]);
    printf("DFS Start\n");

    while (stack_is_empty(stack)==0) {
        graphnode* current_node = (graphnode*)stack_pop(stack);
        int current_index = current_node->index;
        printf("[current index : %d, item : %d ]\n", current_index, graph->nodes[current_index]->item);
        for (int i = 0; i < current_node->adjustNodes->length; i++) {
            graphnode* neighbor_node = (graphnode*)list_get_at(current_node->adjustNodes, i);
            if (visited[neighbor_node->index]==0) {
                stack_push(stack, neighbor_node);
                visited[neighbor_node->index] = 1;
            }
        }
    }
    stack_delete_stack(stack);
    free(visited);
    printf("DFS End\n");
}

dijkstra_package* dijkstra(graph* graph, int index, void* context, int (*condition)(void*, void*)) {
    if (graph == NULL) return NULL;
    if (graph->length == 0) return NULL;
    if (index < 0 || index >= graph->length) return NULL;
    dijkstra_package* result = (dijkstra_package*)malloc(sizeof(dijkstra_package));
    if (result == NULL) return NULL;
    int* visited    = (int*)malloc(sizeof(int)*graph->length);
    if (visited == NULL) {
        free(result);
        return NULL;
    }
    int* distance   = (int*)malloc(sizeof(int)*graph->length);
    if (distance == NULL) {
        free(result);
        free(visited);
        return NULL;
    }
    int* parent     = (int*)malloc(sizeof(int)*graph->length);
    if (parent == NULL) {
        free(result);
        free(visited);
        free(distance);
        return NULL;
    }
    heap* heap;
    if(heap_create_heap(&heap, EDGE_NUM, MIN_HEAP) == ENOMEM) {
        free(result);
        free(visited);
        free(distance);
        free(parent);
        return NULL;
    }
    result->visited = visited;
    result->distance = distance;
    result->parent = parent;
    result->length = graph->length;
    result->curr_index = &index;
    int flag = 0;
    
    //초기화
    for (int i=0;i<graph->length;i++) {
        visited[i]  = 0;
        distance[i] = -1; //무한대
        parent[i]   = -1; //정해지지 않음
    }
    distance[index] = 0;

    
    while (1) {
        //완화
        visited[index]  = 1;
        listnode* cur_ptr = graph->nodes[index]->adjustNodes->root;
        
        for (int i=0;i<list_get_length(graph->nodes[index]->adjustNodes);i++) {
            int j = ((graphnode*)cur_ptr->item)->index;
            if (distance[j] == -1) {
                distance[j] = distance[index] + 1;
                if(heap_push(heap, distance+j, &j) == ERANGE) {
                    heap_resize_heap(heap, heap->max_size*2);
                    heap_push(heap, distance+j, &j);
                }
                parent[j] = index;
            } 
            else if (distance[j] > distance[index] + 1) {
                distance[j] = distance[index] + 1;
                if(heap_push(heap, distance+j, &j) == ERANGE) {
                    heap_resize_heap(heap, heap->max_size*2);
                    heap_push(heap, distance+j, &j);
                }
                parent[j] = index;
            }
            cur_ptr = cur_ptr->next;
        }
        int weight, item;
        //탐색
        while (1) {
            if(heap_pop(heap, &weight, &item) == ERANGE) { flag = 1;break; }
            if(weight == distance[item]) break;
        }
        if(flag) break;
        index = item;
        if(condition != NULL && condition(context, result)) break;
    }
    heap_delete_heap(heap);
    return result;
}

int dijkstra_find_between(graph* graph, int index1, int index2) { //1번 기능
    if (index2 < 0 || index2 >= graph->length) return -1;
    dijkstra_package* pac = dijkstra(graph, index1, &index2, &dijkstra_find_between_condition);
    if(pac == NULL) return -1;
    int result = pac->distance[index2];
    free(pac->visited);free(pac->distance);free(pac->parent);free(pac);
    return result;
}

int dijkstra_find_between_path(graph* graph, int index1, int index2, int** path) { //1번 기능
    if (index2 < 0 || index2 >= graph->length) return -1;
    dijkstra_package* pac = dijkstra(graph, index1, &index2, &dijkstra_find_between_condition);
    if (pac == NULL) return -ERANGE;
    int result = pac->distance[index2];
    result = (result == -1)?-ERANGE:result;
    if (result > 0) {
        *path = (int*)malloc(sizeof(int)*(result+1));
        if(*path == NULL) result = -ENOMEM;
        else {
            (*path)[0] = index2;
            for(int i=1;i<result+1;i++) (*path)[i] = pac->parent[(*path)[i-1]];
        }
    }
    free(pac->visited);free(pac->distance);free(pac->parent);free(pac);
    return result;
}

list* dijkstra_find_within_distance(graph* graph, int index, int max_distance, dijkstra_find_within_distance_type type) { //2번 기능
    if (max_distance < 1) return NULL;
    list* result = list_create_list();
    if(result == NULL) return NULL;
    dijkstra_package* pac = dijkstra(graph, index, &max_distance, &dijkstra_find_within_distance_condition);
    if(pac == NULL) { 
        free(result);
        return NULL;
    }
    for (int i=0;i<graph->length;i++) {
        if (type && pac->distance[i] < max_distance) continue;
        if(pac->visited[i]) list_insert_at_tail(result, graph->nodes[i]);
    }
    list_delete_if(result, graph->nodes[index], graph_compare_graphnode);
    free(pac->visited);free(pac->distance);free(pac->parent);free(pac);
    return result;
}

int* dijkstra_find_all(graph* graph) { //3번 기능
    int* result = (int*)malloc(sizeof(int)*graph->length);
    if(result == NULL) return NULL;
    for(int i=0;i<graph->length;i++) {
        result[i] = graph->nodes[i]->adjustNodes->length;
    }
    return result;
}
// 이건 존재해도 됨

#pragma endregion

#pragma region 존재해서는 안되는 것들

/*
int** dijkstra_find_all(graph* graph) { //3번 기능
    int** result = (int**)malloc(sizeof(int*)*(graph->length+1)>>1);
    if(result == NULL) return NULL;
    dijkstra_package* pac;
    for(int i=0;i<(graph->length+1)>>1;i++) {
        pac = dijkstra(graph, i, NULL, NULL);
        if(pac == NULL) {
            free(result);
            return NULL;
        }
        result[i] = pac->distance;
        free(pac->visited);free(pac->parent);free(pac);
    }
    return result;
}
    그냥 무식하게 한거. 무조건 터진다.
*/
#pragma endregion