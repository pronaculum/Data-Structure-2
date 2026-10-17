#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "list.h"

#pragma region 맨날_하는거
// 맨날 하는거
typedef struct graphnode    graphnode;
typedef struct graph        graph;

typedef int                 graphdata;
typedef list*               graphlink;

struct graphnode
{
    int         index;
    graphdata   item;
    graphlink   adjustNodes;
};
struct graph
{
    graphnode**  nodes;
    int         length;
};
#pragma endregion

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
    if      (node_a->item == node_b->item)  return 0;
    else if (node_a->item > node_b->item)   return 1;
    else                                    return -1;
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
#pragma endregion

#pragma region 외부_함수
void graph_init_graph(graph* graph) {
    free(graph->nodes);
    graph->length = 0;
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
    if (graph->length > 0) graph->nodes = (graphnode**)realloc(graph->nodes, sizeof(graphnode*) * (graph->length + 1));
    else graph->nodes = (graphnode**)malloc(sizeof(graphnode*));
    new_node->index = graph->length;
    graph->nodes[graph->length] = new_node;
    graph->length++;
}

void graph_delete_vertex(graph* graph, int index) {
    if(index<0 || index>=graph->length) return;
    graph_delete_graphnode(graph->nodes[index]);
    for (int i = index; i < graph->length - 2; i++) {
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
    if(list_search(graphnode_a->adjustNodes, graphnode_b, graph_compare_graphnode)==NULL) return 0;
    else return 1;
}

void graph_print_node(graphnode* node) {
    printf("index : [ %d ],\nitem : [ %d ],\nadjust nodes : [ ", node->index, node->item);
    for (int i=0;i<node->adjustNodes->length;i++) printf("%d ", ((graphnode*)list_get_at(node->adjustNodes, i))->index);
    printf("]");
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
    stack_push(stack, graph->nodes[start_index]);
    printf("DFS Start\n");

    while (stack_is_empty(stack)==0) {
        graphnode* current_node = (graphnode*)stack_pop(stack);
        int current_index = current_node->index;
        if(visited[current_index]==1) continue;
        visited[current_index] = 1;
        printf("[current index : %d, item : %d ]\n", current_index, graph->nodes[current_index]->item);
        for (int i = 0; i < current_node->adjustNodes->length; i++) {
            graphnode* neighbor_node = (graphnode*)list_get_at(current_node->adjustNodes, i);
            if (visited[neighbor_node->index]==0)  stack_push(stack, neighbor_node);
        }
    }
    stack_delete_stack(stack);
    free(visited);
    printf("DFS End\n");
}

typedef struct dijkstra_package {
    int* distance;
    int* parent;
}dijkstra_package;

dijkstra_package* dijkstra(graph* graph, int index, void* context, int (*condition)(void* context)) {
    if (graph == NULL) return NULL;
    if (graph->length == 0) return NULL;
    if (index < 0 || index >= graph->length) return NULL;
    int* visited    = (int*)malloc(sizeof(int)*graph->length);
    int* distance   = (int*)malloc(sizeof(int)*graph->length);
    int* parent     = (int*)malloc(sizeof(int)*graph->length);
    int flag = 1;
    
    //초기화
    for (int i=0;i<graph->length;i++) {
        visited[i]  = 0;
        distance[i] = -1; //무한대
        parent[i]   = -1; //정해지지 않음
    }
    distance[index] = 0;

    
    while (flag--) {
        //완화
        visited[index]  = 1;
        
        for (int i=0;i<list_get_length(graph->nodes[index]->adjustNodes);i++) {
            int j = ((graphnode*)list_get_at(graph->nodes[index]->adjustNodes, i))->index;
            if (distance[j] == -1) {
                distance[j] = distance[index] + 1;
                parent[j] = index;
            } 
            else if (distance[j] > distance[index] + 1) {
                distance[j] = distance[index] + 1;
                parent[j] = index;
            }
        }
        int min = distance[index]+2;
        //탐색
        for (int i=0;i<graph->length;i++) {
            if(!visited[i] && distance[i] != -1 && distance[i] < min) {
                index = i;
                min = distance[i];
                flag = 1;
            }
        }
    }
    free(visited);
    dijkstra_package* result = (dijkstra_package*)malloc(sizeof(dijkstra_package));
    if (result == NULL) return NULL;
    result->distance = distance;
    result->parent = parent;
    return result;
}