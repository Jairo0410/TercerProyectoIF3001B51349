#include "mygraph.h"

MyGraph::MyGraph() {
    this->headGraphNode = NULL;
    this->size = 0;
}

MyGraph::~MyGraph() {
}

void MyGraph::insert_graph_node(char id){
    // insertar nodo en la lista principal

    GraphNode* newNode = new GraphNode(id);

    // la insercion se hara al principio, ya que no importa el orden

    newNode->nextGraphNode = this->headGraphNode;
    this->headGraphNode = newNode;

    size++;
}

void MyGraph::print_graph(){
    GraphNode* temp = this->headGraphNode;
    while(temp != NULL){
        printf("%c--> ", temp->id);
        temp = temp->nextGraphNode;
    }

    printf("NULL\n\n");
}

GraphNode *MyGraph::get_node(char id){
    GraphNode* temp = this->headGraphNode;

    // el ciclo se detiene o cuando encuentra el nodo o cuando termina la lista
    while(temp != NULL && temp->id != id){
        temp = temp->nextGraphNode;
    }

    return temp;
}

bool MyGraph::exists(char ID){
    return get_node(ID) != NULL;
}

void MyGraph::print_graph_with_neighbors(){
    GraphNode* node = this->headGraphNode;

    while(node != NULL){

        printf("NODE: %c\n", node->id);
        NeighborNode* neighbor = node->headInnerList;
        printf("\t"); // un tab para mayor orden

        while(neighbor != NULL){
            printf("%c-> ", neighbor->id);
            neighbor = neighbor->nextNeighbor;
        }

        printf("NULL\n\n");
        node = node->nextGraphNode;

    }

    printf("\n\n");

}

void MyGraph::insert_neighbor(char idOrigin, char idDestiny, int cost){
    // obtengo el nodo al cual voy a insertar el vecino
    GraphNode* node = get_node(idOrigin);

    NeighborNode* newNeighbor = new NeighborNode(idDestiny, cost);

    // insercion al principio
    newNeighbor->nextNeighbor = node->headInnerList;
    node->headInnerList = newNeighbor;
}

void MyGraph::insert_neighbor_non_addresed(char lastID, char firstID, int cost){
    insert_neighbor(lastID, firstID, cost);
    insert_neighbor(firstID, lastID, cost);
}

void MyGraph::set_not_visited(){
    // marcar todos los nodos como no visitados
    GraphNode* temp = this->headGraphNode;

    while(temp != NULL){
        temp->isVisited = false;
        temp = temp->nextGraphNode;
    }
}

bool MyGraph::has_neighbor(char origin, char destiny){
    GraphNode* node = get_node(origin);

    if(node != NULL){
        NeighborNode* temp = node->headInnerList;

        while(temp != NULL){

            if(temp->id == destiny){
                return true;
            }

            temp = temp->nextNeighbor;

        }

    }

    return false;
}

void MyGraph::Dijsktra(char ID){

}
