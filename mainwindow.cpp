#include "mainwindow.h"
#include "mygraph.h"

#include "ui_mainwindow.h"

#include <QGraphicsEllipseItem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    this->scene->setBackgroundBrush(QBrush(Qt::yellow));

    this->graph = new MyGraph();

    this->node_head = NULL;
    this->neighbor_head = NULL;

    insert_graphic_node('B', 40, 30);
    insert_graphic_node('E', 220, 30);
    insert_graphic_node('F', 80, 200);
    insert_graphic_node('T', 220, 300);

    insert_graphic_neighbor('F', 'B', 6);
    insert_graphic_neighbor('F', 'E', 8);
    insert_graphic_neighbor('F', 'T', 10);
    insert_graphic_neighbor('T', 'B', 17);

    paint_graph_path(this->graph->get_Prim());

    ui->graphicsView->setScene(this->scene);
}

MainWindow::GRAPHICNODE* MainWindow::get_graphic_node(char ID){
    GRAPHICNODE *temp = this->node_head;

    while(temp != NULL && temp->ID != ID){
        temp = temp->next;
    }

    return temp;
}

void MainWindow::insert_graphic_node(char ID, int x, int y){
    // insertar de manera logica
    this->graph->insert_graph_node(ID);

    // insertar de manera grafica
    GRAPHICNODE *newNode = (GRAPHICNODE*) malloc(sizeof(GRAPHICNODE));
    newNode->ID = ID;
    newNode->x = x;
    newNode->y = y;

    // insertar
    newNode->next = this->node_head;
    this->node_head = newNode;

    // dibujar el nodo
    newNode->ellipse = this->scene->addEllipse(x, y, NODE_SIZE, NODE_SIZE, nodeLine, nodeFill);

    QGraphicsTextItem *label = scene->addText(QString(ID));

    label->setX(x+NODE_SIZE/3);
    label->setY(y+NODE_SIZE/4);
}

void MainWindow::insert_graphic_neighbor(char origin, char destiny, int cost){
    // insertar de manera logica
    this->graph->insert_neighbor_non_addresed(origin, destiny, cost);

    // insertar de manera grafica
    GRAPHICNEIGHBOR *newNeighbor = (GRAPHICNEIGHBOR*) malloc(sizeof(GRAPHICNEIGHBOR));
    newNeighbor->cost = cost;
    newNeighbor->origin = get_graphic_node(origin);
    newNeighbor->destiny = get_graphic_node(destiny);

    // insertar
    newNeighbor->next = this->neighbor_head;
    this->neighbor_head = newNeighbor;

    // dibujar el vecino

    // con estos datos se conoce quien esta "arriba" y quien "abajo"
    int minX = std::min(newNeighbor->origin->x, newNeighbor->destiny->x);
    int minY = std::min(newNeighbor->origin->y, newNeighbor->destiny->y);

    int maxX = std::max(newNeighbor->origin->x, newNeighbor->destiny->x);
    int maxY = std::max(newNeighbor->origin->y, newNeighbor->destiny->y);

    // si estan a una misma altura
    if(minY == maxY){
        newNeighbor->line = this->scene->addLine(newNeighbor->origin->x+NODE_SIZE/2, minY,
                                                 newNeighbor->destiny->x+NODE_SIZE/2, maxY, this->normalNeighbor);
    }else{
        if(newNeighbor->origin->y == minY){
            newNeighbor->line = this->scene->addLine(newNeighbor->origin->x+NODE_SIZE/2, minY+NODE_SIZE,
                                                     newNeighbor->destiny->x+NODE_SIZE/2, maxY, this->normalNeighbor);
        }else{
            newNeighbor->line = this->scene->addLine(newNeighbor->destiny->x+NODE_SIZE/2, minY+NODE_SIZE,
                                                     newNeighbor->origin->x+NODE_SIZE/2, maxY, this->normalNeighbor);
        }
    }

    QGraphicsTextItem *label = scene->addText(QString::number(cost));

    label->setFlag(QGraphicsItem::ItemIsMovable);

    label->setX(minX + std::abs(minX - maxX)/2);
    label->setY(minY + std::abs(minY - maxY)/2);
}

void MainWindow::paint_graph_path(MyGraph *graph){
    GRAPHICNEIGHBOR *temp = this->neighbor_head;

    while(temp != NULL){
        if(graph->has_neighbor(temp->origin->ID, temp->destiny->ID)){
            temp->line->setPen(this->highlitNeighbor);
        }else{
            temp->line->setPen(this->normalNeighbor);
        }

        temp = temp->next;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
