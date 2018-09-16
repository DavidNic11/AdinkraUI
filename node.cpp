#include "edge.h"
#include "node.h"
#include "graphwidget.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

Node::Node(GraphWidget *graphWidget, bool isBoson)
    : graph(graphWidget), actualCoord(nullptr), screenCoord(nullptr)
{
    this->isBoson = isBoson;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    int r = 255;
    int g = 84;
    int b = 0;
    int alpha = 255;

    // Add Fermion and Boson Colors Here

    QColor color = (this->isBoson ? QColor(r,g,b,alpha) : QColor(71,67,76,255));
    QColor penColor = QColor(57,54,61,255);

    painter->setBrush(color);

    painter->setPen(QPen(penColor, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Node::projectPoint(){
    qInfo() <<"X = " <<actualCoord->x;
     qInfo() <<"Y = " <<actualCoord->y;
      qInfo() <<"Z = " <<actualCoord->z;
       qInfo() <<"S = " <<actualCoord->s;
        qInfo() <<"D = " <<actualCoord->d;

    double xPrime = double(actualCoord->x * actualCoord->d) / double(actualCoord->z + actualCoord->s + actualCoord->d);
    double yPrime = double(actualCoord->y * actualCoord->d) / double(actualCoord->z + actualCoord->s + actualCoord->d);
     qInfo()<<"XPRIME = " << xPrime;
      qInfo()<<"YPRIME = " << yPrime;

    screenCoord = new ScreenCoordinate(xPrime, yPrime);
}
void Node::setACoord(ActualCoordinate *a){
    actualCoord = a;
}
