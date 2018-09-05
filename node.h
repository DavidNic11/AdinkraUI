#ifndef NODE_H
#define NODE_H

#endif // NODE_H

#include <QGraphicsItem>
#include <QPointF>

#include <edge.h>
#include <graphwidget.h>

class Node : public QGraphicsItem {
public:
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1};
  //  int type() const override {return type}

    void calculateForeces();
    bool advancePosition();
    // Painting
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    // Mouse Events
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

// Constructor
Node::Node(GraphWidget *graphWidget) : graph(graphWidget) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

//Methods
void Node::addEdge(Edge *edge){
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const {
    return edgeList;
}
