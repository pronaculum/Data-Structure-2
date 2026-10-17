#ifndef GRAPH_H
#define GRAPH_H

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

void graph_init_graph(graph* graph);
graph* graph_create_graph();
void graph_insert_vertex(graph* graph, graphdata item);
void graph_delete_vertex(graph* graph, int index);
void graph_insert_edge(graph* graph, int index_a, int index_b);
void graph_delete_edge(graph* graph, int index_a, int index_b);
int graph_is_adjacent(graph* graph, int index_a, int index_b);
void graph_BFS(graph* graph, int start_index);
void graph_DFS(graph* graph, int start_index);

#endif