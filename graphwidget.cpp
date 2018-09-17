#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

# define M_PI           3.14159265358979323846  /* pi */

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
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

    Node *node1 = new Node(this, true);
    Node *node2 = new Node(this, false);
    Node *node3 = new Node(this, false);
    Node *node4 = new Node(this, true);

    Node *node5 = new Node(this, false);
    Node *node6 = new Node(this, true);
    Node *node7 = new Node(this, true);
    Node *node8 = new Node(this, false);

    // Screen Coordinate
    ActualCoordinate *a1 = new ActualCoordinate(100,100,-100);
    ActualCoordinate *a2 = new ActualCoordinate(-100,100,-100);
    ActualCoordinate *a3 = new ActualCoordinate(100,-100,-100);
    ActualCoordinate *a4 = new ActualCoordinate(-100,-100,-100);
    ActualCoordinate *a5 = new ActualCoordinate(100,100,100);
    ActualCoordinate *a6 = new ActualCoordinate(-100,100,100);
    ActualCoordinate *a7 = new ActualCoordinate(100,-100,100);
    ActualCoordinate *a8 = new ActualCoordinate(-100,-100,100);

    a1->rotateX(M_PI/4);
    a2->rotateX(M_PI/4);
    a3->rotateX(M_PI/4);
    a4->rotateX(M_PI/4);
    a5->rotateX(M_PI/4);
    a6->rotateX(M_PI/4);
    a7->rotateX(M_PI/4);
    a8->rotateX(M_PI/4);

    // Give the people what they want
    node1->setACoord(a1);
    node2->setACoord(a2);
    node3->setACoord(a3);
    node4->setACoord(a4);
    node5->setACoord(a5);
    node6->setACoord(a6);
    node7->setACoord(a7);
    node8->setACoord(a8);
    //Node *center = new Node(this, false);



    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);

    scene->addItem(node5);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);

    //Front Face
    scene->addItem(new Edge(node1, node2, true));
    scene->addItem(new Edge(node1, node3, false));
    scene->addItem(new Edge(node3, node4, false));
    scene->addItem(new Edge(node2, node4, false));

    //Left Side
    scene->addItem(new Edge(node1, node5, true));
    scene->addItem(new Edge(node3, node7, false));

    //Back Face
    scene->addItem(new Edge(node7, node5, false));
    scene->addItem(new Edge(node5, node6, false));
    scene->addItem(new Edge(node8, node6, false));
    scene->addItem(new Edge(node7, node8, true));

    //Right Side
    scene->addItem(new Edge(node4, node8, false));
    scene->addItem(new Edge(node2, node6, true));

    node1->projectPoint();
    node2->projectPoint();
    node3->projectPoint();
    node4->projectPoint();
    node5->projectPoint();
    node6->projectPoint();
    node7->projectPoint();
    node8->projectPoint();

    node1->setPos(node1->screenCoord->x, node1->screenCoord->y);  //(-100 - 25, -100 + 25);
    node2->setPos(node2->screenCoord->x, node2->screenCoord->y);  //(-100 - 25, 100 + 25);
    node3->setPos(node3->screenCoord->x, node3->screenCoord->y);  //(100 - 25, 100 + 25);
    node4->setPos(node4->screenCoord->x, node4->screenCoord->y);  //(100 - 25, -100 + 25);

    node5->setPos(node5->screenCoord->x, node5->screenCoord->y);  //(-25 - 25, -175 + 25);
    node6->setPos(node6->screenCoord->x, node6->screenCoord->y);  //(175 - 25, -175 + 25);
    node7->setPos(node7->screenCoord->x, node7->screenCoord->y);  //(-25 - 25, 25 + 25);
    node8->setPos(node8->screenCoord->x, node8->screenCoord->y);  //(175 - 25, 25 + 25);


    /*
     * TODO:
     *  Add a number system for nodes
     *  Figure out how to center everything
     *  Create from Scratch (automated)
     *
     * spin the cubef
     *  three roatations
     *  nodes xyz
     *  screen xy
     *
     *  maybe add animation
    */
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
