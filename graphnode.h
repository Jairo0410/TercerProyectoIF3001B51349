#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "neighbornode.h"

#include <cstddef>

class GraphNode
{
public:
    GraphNode(char ID);
    char id;
    NeighborNode* headInnerList;
    bool isVisited;
    GraphNode* nextGraphNode;
    GraphNode* prevGraphNode;
    unsigned int distance;
    static const unsigned int MAX_VALUE = 4000000;
};

#endif // GRAPHNODE_H
