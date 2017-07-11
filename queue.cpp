#include "queue.h"

Queue::Queue()
{
    this->head = NULL;
    this->tail = NULL;
}

void Queue::enqueue(char ID, int distance){
    GraphNode* newNode = new GraphNode(ID);
    newNode->distance = distance;

    // la cola esta vacia
    if(this->is_empty()){
       this->head = newNode;
        this->tail = newNode;
    }else{
        GraphNode *temp = this->head;

        while(temp != NULL && temp->distance > newNode->distance){
            temp = temp->nextGraphNode;
        }

        // hacer la insercion segun sea el caso

        // insercion al final
        if(temp == NULL){
            this->tail->nextGraphNode = newNode;
            newNode->prevGraphNode = this->tail;
            this->tail = newNode;
        }
        // insercion al principio
        else if(temp->prevGraphNode == NULL){
            this->head->prevGraphNode = newNode;
            newNode->nextGraphNode = this->head;
            this->head = newNode;
        }
        // insercion en el medio
        else{
            temp->prevGraphNode->nextGraphNode = newNode;
            newNode->prevGraphNode = temp->prevGraphNode;
            temp->prevGraphNode = newNode;
            newNode->nextGraphNode = temp;
        }
    }
}

bool Queue::is_empty(){
    return this->head == NULL || this->tail == NULL;
}

GraphNode* Queue::dequeue(){

    if(!this->is_empty()){
        GraphNode* node = this->tail;

        // eliminar el ultimo valor de la cola
        this->tail = this->tail->prevGraphNode;

        if(this->tail != NULL){
            this->tail->nextGraphNode = NULL;
        }

        return node;
    }

    return NULL;
}
