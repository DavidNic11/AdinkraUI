#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

struct ActualCoordinate{
    double x;
    double y;
    double z;

    int d = 150;
    int s = 100;

    ActualCoordinate(int xCoord, int yCoord, int zCoord) : x(xCoord),y(yCoord),z(zCoord){}

    void rotateX(double degree);
    void rotateY(double degree);
    void rotateZ(double degree);
};

struct ScreenCoordinate{
    double x;
    double y;

    ScreenCoordinate(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
};

class Node : public QGraphicsItem {
public:
    // Coordinate Stuff
    ActualCoordinate *actualCoord;
    ScreenCoordinate *screenCoord;

    Node(GraphWidget *graphWidget, bool isBoson);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1};
    int type() const override {return Type;}

    // Painting
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Projection
    void projectPoint();
    void setACoord(ActualCoordinate *a);

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
};


#endif // NODE_H
