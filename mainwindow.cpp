#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    this->ui->cbxOrigin->addItem(QString("Seleccione"));
    this->ui->cbxDestiny->addItem(QString("Seleccione"));

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

void MainWindow::mousePressEvent(QMouseEvent *event){
    QPointF point = event->localPos();

    // se presiona el click derecho
    if(event->button() == Qt::RightButton){
        QString result = QInputDialog::getText(this, "Ingrese una letra", "Ingrese una letra");
        if(!result.isEmpty()){
            char ID = result.at(0).toLatin1();
            if(!this->graph->exists(ID)){
                this->insert_graphic_node(ID, point.x()-1000, point.y()-300);
                ui->cbxDestiny->addItem(QString(ID));
                ui->cbxOrigin->addItem(QString(ID));
            }else {
                QMessageBox::warning(this, "Error", "El nodo ya existe");
            }
        }
    }
}

void MainWindow::on_btnAddNeighbor_clicked()
{
    int origin = ui->cbxOrigin->currentIndex();
    int destiny = ui->cbxDestiny->currentIndex();

    if(origin != destiny && origin && destiny){
        unsigned int cost = QInputDialog::getInt(this, "Ingrese un valor entero", "Ingrese el costo del vecino");
        if(cost){
            char originID = ui->cbxOrigin->currentText().at(0).toLatin1();
            char destinyID = ui->cbxDestiny->currentText().at(0).toLatin1();
            if(!this->graph->has_neighbor(originID, destinyID)){
                insert_graphic_neighbor(originID, destinyID, cost);
            }else{
                QMessageBox::warning(this, "Ya existe", "El vecino ya existe");
            }
        }
    }else{
        QMessageBox::warning(this, "Incorrecto", "Origen o Destino incorrectos");
    }
}

void MainWindow::on_btnPrim_clicked()
{
    paint_graph_path(this->graph->get_Prim());
}

void MainWindow::on_btnMontecarlo_clicked()
{
    paint_graph_path(this->graph->get_Montecarlo());
}

void MainWindow::on_btnDijkstra_clicked()
{
    int origin = ui->cbxOrigin->currentIndex();
    int destiny = ui->cbxDestiny->currentIndex();

    if(origin != destiny && origin && destiny){
        char originID = ui->cbxOrigin->currentText().at(0).toLatin1();
        char destinyID = ui->cbxDestiny->currentText().at(0).toLatin1();

        paint_graph_path(this->graph->get_Dijkstra(originID, destinyID));

    }else{
        QMessageBox::warning(this, "Incorrecto", "Origen o Destino incorrectos");
    }
}
