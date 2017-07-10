#include "neighbornode.h"

NeighborNode::NeighborNode(char id, int cost)
{
    this->id = id;
    this->cost = cost;
    this->nextNeighbor = NULL;
}
