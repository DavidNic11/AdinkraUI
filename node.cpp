#include "edge.h"
#include "node.h"
#include "graphwidget.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <math.h>

int Node::getNodeNumber()
{
    return nodeNumber;
}

Node::Node(GraphWidget *graphWidget, bool isBoson, int number)
    : graph(graphWidget), actualCoord(nullptr), screenCoord(new ScreenCoordinate(0,0)), coordinates(nullptr), nodeNumber(number)
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
    //painter->drawEllipse(-7, -7, 20, 20);

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

    double xPrime = double(actualCoord->x * actualCoord->d) / double(actualCoord->z + actualCoord->s + actualCoord->d);
    double yPrime = double(actualCoord->y * actualCoord->d) / double(actualCoord->z + actualCoord->s + actualCoord->d);

    screenCoord->x = xPrime;
    screenCoord->y = yPrime;
}
void Node::setACoord(ActualCoordinate *a){
    actualCoord = a;
}


// Coordinate Stuff (Probably should move this to a new file)
void ActualCoordinate::rotateX(double theta){
    double mult [3][1] = {{0},{0},{0}};

    double rotationMatrix[3][3] = {{cos(theta), -1*sin(theta), 0},
                                    {sin(theta), cos(theta), 0},
                                    {0, 0, 1}};

    double xyzVector [3][1] = {{x},
                            {y},
                            {z}};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 1; j++){
            for(int k = 0; k < 3; k++){
                mult[i][j] += rotationMatrix[i][k] * xyzVector[k][j];
            }
        }
    }

    x = mult[0][0];
    y = mult[1][0];
    z = mult[2][0];
}

void ActualCoordinate::rotateY(double theta){
    double mult [3][1] = {{0},{0},{0}};

    double rotationMatrix[3][3] = {{cos(theta), 0, sin(theta)},
                                    {0, 1, 0},
                                    {-1*sin(theta), 0, cos(theta)}};

    double xyzVector [3][1] = {{x},
                            {y},
                            {z}};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 1; j++){
            for(int k = 0; k < 3; k++){
                mult[i][j] += rotationMatrix[i][k] * xyzVector[k][j];
            }
        }
    }

    x = mult[0][0];
    y = mult[1][0];
    z = mult[2][0];
}

void ActualCoordinate::rotateZ(double theta){
    double mult [3][1] = {{0},{0},{0}};

    double rotationMatrix[3][3] = {{1, 0, 0},
                                    {0, cos(theta), -1*sin(theta)},
                                    {0, sin(theta), cos(theta)}};

    double xyzVector [3][1] = {{x},
                            {y},
                            {z}};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 1; j++){
            for(int k = 0; k < 3; k++){
                mult[i][j] += rotationMatrix[i][k] * xyzVector[k][j];
            }
        }
    }

    x = mult[0][0];
    y = mult[1][0];
    z = mult[2][0];
}
