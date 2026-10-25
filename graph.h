#ifndef GRAPH_H
#define GRAPH_H

// 맨날 하는거
typedef struct graphnode        graphnode;
typedef struct graph            graph;
typedef struct dijkstra_package dijkstra_package;

typedef int     graphdata;
typedef list*   graphlink;

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
typedef struct dijkstra_package {
    int* visited;
    int* distance;
    int* parent;
    int* curr_index;
    int length;
}dijkstra_package;

//외부 함수
void graph_init_graph(graph* graph);
void graph_delete_graph(graph* graph);
graph* graph_create_graph();
void graph_insert_vertex(graph* graph, graphdata item);
void graph_delete_vertex(graph* graph, int index);
void graph_insert_edge(graph* graph, int index_a, int index_b);
void graph_delete_edge(graph* graph, int index_a, int index_b);
int graph_is_adjacent(graph* graph, int index_a, int index_b);
void graph_print_node(graphnode* node);
void graph_BFS(graph* graph, int start_index);
void graph_DFS(graph* graph, int start_index);
dijkstra_package* dijkstra(graph* graph, int index, void* context, int (*condition)(void*, void*));
int dijkstra_find_between(graph* graph, int index1, int index2);
list* dijkstra_find_within_distance(graph* graph, int index, int max_distance);
int* dijkstra_find_all(graph* graph);
#endif