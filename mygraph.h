#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "graphnode.h"
#include "neighbornode.h"
#include "queue.h"

class MyGraph {
public:
    MyGraph();
    MyGraph(const MyGraph& orig);
    virtual ~MyGraph();

    // general graph methods

    void insert_graph_node(char ID);
    void print_graph();
    void print_graph_with_neighbors();
    void insert_neighbor_non_addresed(char origin, char destiny, int cost);
    GraphNode* get_node(char ID);
    void set_not_visited();

    // Prim
    bool exists(char ID);

    // Dijkstra
    void reset_values();
    void relax(GraphNode* current, GraphNode* adjacent, int cost);
    bool has_neighbor(char origin, char destiny);

    // Montecarlo
    void depth_scan(MyGraph* graph, GraphNode* node);

    // graph build methods
    MyGraph* get_Dijkstra(char start, char goal);
    MyGraph* get_Prim();
    MyGraph* get_Montecarlo();

    // variables
    int size;

private:

    // variables
    GraphNode* headGraphNode;
    GraphNode* tailGraphNode;

    // metodos privados
    void insert_neighbor(char origin, char destiny, int cost);
    void Dijsktra(char ID);
};

#endif // MYGRAPH_H
