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
};

#endif // GRAPHNODE_H
