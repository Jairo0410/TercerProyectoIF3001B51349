#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mygraph.h"

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyGraph *graph;

    typedef struct GraphicNode{

        QGraphicsEllipseItem *ellipse;
        int x;
        int y;
        char ID;
        GraphicNode *next;

    } GRAPHICNODE;

    typedef struct GraphicNeighbor{

        QGraphicsLineItem *line;
        GRAPHICNODE *origin;
        GRAPHICNODE *destiny;
        int cost;
        GraphicNeighbor *next;

    } GRAPHICNEIGHBOR;

    GRAPHICNODE *node_head;
    GRAPHICNEIGHBOR *neighbor_head;

    // atributos para dibujar
    const int NODE_SIZE = 40;
    QPen nodeLine = QPen(Qt::black);
    QBrush nodeFill = QBrush(Qt::green);
    QPen normalNeighbor = QPen(Qt::blue, 2);
    QPen highlitNeighbor = QPen(Qt::cyan, 3);

    QGraphicsScene *scene;

    void paint_graph_path(MyGraph *graph);
    void insert_graphic_node(char ID, int x, int y);
    GRAPHICNODE* get_graphic_node(char ID);
    void insert_graphic_neighbor(char origin, char destiny, int cost);

};

#endif // MAINWINDOW_H
