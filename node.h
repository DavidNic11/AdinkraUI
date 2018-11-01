#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;
class Coordinates;

class Node : public QGraphicsItem {
public:
    // Coordinate Stuff

    Coordinates *coordinates;

    int getNodeNumber();
    int getNodeEdgeNumber();
    bool getBoson();

    QPointF oldPoint;

    Node(GraphWidget *graphWidget, bool isBoson, int number);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    void setEdgeNumber(int number);

    enum { Type = UserType + 1};
    int type() const override {return Type;}

    // Painting
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Projection
    void projectPoint();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    // Mouse Events
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    bool isBoson;
    int nodeNumber;
    int edgingNodeNumber;
};


#endif // NODE_H
