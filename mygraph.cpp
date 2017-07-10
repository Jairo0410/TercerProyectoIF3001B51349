#include "mygraph.h"

MyGraph::MyGraph() {
    this->headGraphNode = NULL;
    this->size = 0;
}

MyGraph::~MyGraph() {
}

void MyGraph::insert_graph_node(char id){
    // insertar nodo en la lista principal

    GRAPHNODE* newNode = (GRAPHNODE*) malloc(sizeof(GRAPHNODE));
    newNode->id = id;
    newNode->isVisited = 0;
    newNode->headInnerList = NULL;
    newNode->nextGraphNode = NULL;

    // la insercion se hara al principio, ya que no importa el orden

    newNode->nextGraphNode = this->headGraphNode;
    this->headGraphNode = newNode;

    size++;
}

void MyGraph::print_graph(){
    GRAPHNODE* temp = this->headGraphNode;
    while(temp != NULL){
        printf("%c--> ", temp->id);
        temp = temp->nextGraphNode;
    }

    printf("NULL\n\n");
}

MyGraph::GRAPHNODE *MyGraph::get_node(char id){
    GRAPHNODE* temp = this->headGraphNode;

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
        NEIGHBORNODE* neighbor = node->headInnerList;
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
    GRAPHNODE* node = get_node(idOrigin);

    NEIGHBORNODE* newNeighbor = (NEIGHBORNODE*) malloc(sizeof(NEIGHBORNODE));
    newNeighbor->id = idDestiny;
    newNeighbor->cost = cost;
    newNeighbor->nextNeighbor = NULL;

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
    GRAPHNODE* temp = this->headGraphNode;

    while(temp != NULL){
        temp->isVisited = false;
        temp = temp->nextGraphNode;
    }
}

bool MyGraph::has_neighbor(char origin, char destiny){
    GRAPHNODE* node = get_node(origin);

    if(node != NULL){
        NEIGHBORNODE* temp = node->headInnerList;

        while(temp != NULL){

            if(temp->id == destiny){
                return true;
            }

        }

    }

    return false;
}

void MyGraph::Dijsktra(char ID){

}
