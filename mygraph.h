#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include "graphnode.h"
#include "neighbornode.h"

class MyGraph {
public:
    MyGraph();
    MyGraph(const MyGraph& orig);
    virtual ~MyGraph();

    // graph methods

    void insert_graph_node(char ID);
    void print_graph();
    void print_graph_with_neighbors();
    void insert_neighbor_non_addresed(char origin, char destiny, int cost);
    GraphNode* get_node(char ID);
    void set_not_visited();
    bool has_neighbor(char origin, char destiny);
    bool exists(char ID);

    // graph build methods
    MyGraph get_Dijkstra(char start, char goal);
    MyGraph get_Prim();
    MyGraph get_Montecarlo();

    // variables
    int size;

private:

    // variables
    GraphNode* headGraphNode;

    // metodos privados
    void insert_neighbor(char origin, char destiny, int cost);
    void Dijsktra(char ID);
};

#endif // MYGRAPH_H
