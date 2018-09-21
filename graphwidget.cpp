#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "coordinates.h"

#include <math.h>
#include <bitset>
#include <iostream>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

# define M_PI           3.14159265358979323846  /* pi */

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), nodeVector(), timer(new QTimer(this)), rotX(0), rotY(0), rotZ(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Adinkra Nodes"));

    rotation = 0;

    dimension = 4;
    int numNodes = (1 << dimension);

    QVector<QColor> colors;
       double nextHue = 0.2f;
       for(int i = 0; i < dimension; i++) {
           QColor nextColor = QColor(0,0,0);
           nextColor.toHsl();
           nextHue += .6135;
           if (nextHue>1) {
               nextHue-=1;
           }
           nextColor.setHslF(nextHue,.5f,.4f);
           colors.append(nextColor);
       }

    //qDebug() << numNodes;

    for(int i = 0; i < numNodes; i++){
        nodeVector.append(new Node(this, std::bitset<sizeof(int)>(i).count() % 2, i));
        QVector<double> *tempVector = createCoordinates(dimension, i);
        nodeVector[i]->coordinates = new Coordinates(dimension, tempVector);
        scene->addItem(nodeVector[i]);
        nodeVector[i]->setPos(nodeVector[i]->coordinates->projectedX, nodeVector[i]->coordinates->projectedY);
    }

    for(int i = 0; i < numNodes; i++){
        for(int j = i + 1; j < numNodes ; j++){
            std::bitset<sizeof(int)> result (nodeVector[i]->getNodeNumber() ^ nodeVector[j]->getNodeNumber());
            //std::cout << result<< endl;
            if(result.count() == 1){
                scene->addItem(new Edge(nodeVector[i], nodeVector[j], std::bitset<sizeof(int)> (i >> getDifferingPlace(i,j)).count()%2, colors[getDifferingPlace(i,j)]));

            }
        }


    }
    connect(timer, &QTimer::timeout, this, &GraphWidget::doStep);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        //centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        //centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        //centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        //centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{

}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();

    // Fill
    QColor backGroundColor = QColor(255,255,255);
    painter->fillRect(rect.intersected(sceneRect), backGroundColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::startAnimation(){
    timer->setInterval(20);
    timer->setSingleShot(false);
    timer->start();
}

void GraphWidget::stopAnimation()
{
    timer->stop();
}

void GraphWidget::rotXChanged(double newX)
{
    rotX = newX;
}

void GraphWidget::rotYChanged(double newY)
{
    rotY = newY;
}

void GraphWidget::rotZChanged(double newZ)
{
    rotZ = newZ;
}

void GraphWidget::doStep(){
    for(int i = 0; i < (1 << dimension); i++){
        nodeVector[i]->coordinates->rotate(0,1,M_PI* 1/200);
        nodeVector[i]->coordinates->rotate(0,2,M_PI/200);
        nodeVector[i]->coordinates->rotate(2,3,M_PI/200);

        nodeVector[i]->setPos(nodeVector[i]->coordinates->projectedX, nodeVector[i]->coordinates->projectedY);
    }
}

QVector<double>* GraphWidget::createCoordinates(int dim, int nodeNumber){
    QVector<double> *coordinates = new QVector<double>();
    for(int i = 0; i < dim; i++){
        coordinates->append(nodeNumber & 1 ? 100 : -100);
        nodeNumber = (nodeNumber >> 1);
    }

    return coordinates;
}

int GraphWidget::getDifferingPlace(int node1, int node2){
    int i = 0 ;
    int sum = node1 ^ node2;
    while(sum != 0){
        i++;
        sum = sum >> 1;
    }
    return i-1;
}
