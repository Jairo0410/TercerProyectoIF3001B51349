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

    if(this->headGraphNode == NULL){
        this->headGraphNode = newNode;
        this->tailGraphNode = newNode;
    }else{
        newNode->nextGraphNode = this->headGraphNode;
        this->headGraphNode = newNode;
    }

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

/**
 * @brief MyGraph::Dijsktra
 * @param ID
 * Implementacion de pseudocodigo del Algoritmo de Dijkstra
 */
void MyGraph::Dijsktra(char ID){
    reset_values();

    GraphNode *node = get_node(ID);

    node->distance = 0;

    Queue *queue = new Queue();
    queue->enqueue(node->id, node->distance);

    while(!queue->is_empty()){
        node = queue->dequeue();

        // mientras que este visitado, seguir sacando nodos de la lista
        while(node->isVisited){
            node = queue->dequeue();
        }

        /* el nodo se encuentra en una cola, pero en realidad
         * no posee toda la informacion necesaria, asi que se
         * recupera del grafo original*/
        node = get_node(node->id);
        node->isVisited = true;

        // recorrer los nodos adyacentes

        NeighborNode* neighbor = node->headInnerList;

        while(neighbor != NULL){
            GraphNode *neighborNode = get_node(neighbor->id);

            if(!neighborNode->isVisited){
                relax(node, neighborNode, neighbor->cost);
                queue->enqueue(neighbor->id, neighborNode->distance);
            }

            neighbor = neighbor->nextNeighbor;
        }

    }
}

MyGraph* MyGraph::get_Dijkstra(char start, char goal){
    // ejecutar el Algoritmo de Dijkstra
    this->Dijsktra(start);

    // construir el camino a partir de las distancias de "atras hacia adelante"
    MyGraph *result = new MyGraph();

    GraphNode *currentNode = get_node(goal);

    result->insert_graph_node(currentNode->id);

    // mientras que la distancia no sea 0
    while(currentNode->distance){
        NeighborNode* neighbor = currentNode->headInnerList;

        while(neighbor != NULL){

            GraphNode *neighborNode = get_node(neighbor->id);

            if(currentNode->distance - neighbor->cost == neighborNode->distance){

                result->insert_graph_node(neighbor->id);
                result->insert_neighbor_non_addresed(currentNode->id, neighbor->id, neighbor->cost);

                currentNode = neighborNode;
                break;
            }

            neighbor = neighbor->nextNeighbor;
        }

    }

    return result;
}

void MyGraph::relax(GraphNode *current, GraphNode *adjacent, int cost){
    if(current->distance + cost < adjacent->distance){
        adjacent->distance = current->distance + cost;
    }
}

MyGraph* MyGraph::get_Prim(){
    MyGraph *result = new MyGraph();

    GraphNode *node = this->headGraphNode;

    result->insert_graph_node(node->id);

    while(result->size < this->size){

        node = result->headGraphNode;

        // buscar la arista de longitud minima que no pertenezca al conjunto solucion

        GraphNode* minimumNode = NULL;
        NeighborNode* minimumNeighbor = NULL;

        while(node != NULL){
            GraphNode* originalNode = this->get_node(node->id);
            NeighborNode* neighbor = originalNode->headInnerList;

            while(neighbor != NULL){

                if(minimumNeighbor == NULL || neighbor->cost < minimumNeighbor->cost){
                    // revisar que no exista aun en el conjunto solucion
                    if(!result->exists(neighbor->id)){
                        minimumNeighbor = neighbor;
                        minimumNode = node;
                    }
                }

                neighbor = neighbor->nextNeighbor;
            }

            node = node->nextGraphNode;
        }

        // insertar el nuevo nodo y la nueva arista en el conjunto solucion
        if(minimumNeighbor != NULL && minimumNode != NULL){
            result->insert_graph_node(minimumNeighbor->id);
            result->insert_neighbor_non_addresed(minimumNode->id, minimumNeighbor->id,
                                                 minimumNeighbor->cost);
        }

    }

    return result;
}

/**
 * @brief Queue::reset_values
 * reinicia los datos temporales de los nodos, de manera que no
 * afecten el resultado final
 */
void MyGraph::reset_values(){
    GraphNode* temp = this->headGraphNode;

    while(temp != NULL){
        temp->distance = GraphNode::MAX_VALUE;
        temp->isVisited = false;
        temp = temp->nextGraphNode;
    }
}
