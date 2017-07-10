#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <stddef.h>
#include <cstdio>
#include <cstdlib>

class MyGraph {
public:
    MyGraph();
    MyGraph(const MyGraph& orig);
    virtual ~MyGraph();

    // structs

    typedef struct NeighborNode{
        char id;
        int cost;
        struct NeighborNode* nextNeighbor;
    } NEIGHBORNODE;

    typedef struct GraphNode{
        char id;
        NeighborNode* headInnerList;
        bool isVisited;
        struct GraphNode* nextGraphNode;
    } GRAPHNODE;

    // graph methods

    void insert_graph_node(char ID);
    void print_graph();
    void print_graph_with_neighbors();
    void insert_neighbor_non_addresed(char origin, char destiny, int cost);
    GRAPHNODE* get_node(char ID);
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
    GRAPHNODE* headGraphNode;

    // metodos privados
    void insert_neighbor(char origin, char destiny, int cost);
    void Dijsktra(char ID);
};

#endif // MYGRAPH_H
