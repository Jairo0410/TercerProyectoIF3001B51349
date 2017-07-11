#include "graphnode.h"

GraphNode::GraphNode(char ID)
{
    this->id = ID;
    this->isVisited = 0;
    this->headInnerList = NULL;
    this->nextGraphNode = NULL;
    this->prevGraphNode = NULL;
    this->distance = MAX_VALUE;
}
