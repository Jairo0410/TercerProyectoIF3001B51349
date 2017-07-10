#ifndef NEIGHBORNODE_H
#define NEIGHBORNODE_H

#include <cstddef>

class NeighborNode
{
public:
    NeighborNode(char id, int cost);
    char id;
    int cost;
    NeighborNode* nextNeighbor;
};

#endif // NEIGHBORNODE_H
