#include "edge.h"
#include "node.h"

#include <qmath.h>
#include <QPainter>

Edge::Edge(Node *sourceNode, Node *destNode, bool isDashed, QColor edgeColor) : edgeColor(edgeColor), arrowSize(10)  {
    this->isDashed = isDashed;
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

Node* Edge::sourceNode() const{
    return source;
}

Node* Edge::destNode() const{
    return dest;
}

void Edge::adjust(){
    if (!source || !dest)
            return;

        QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
        qreal length = line.length();

        prepareGeometryChange();

        if (length > qreal(20.)) {
            QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
            sourcePoint = line.p1() + edgeOffset;
            destPoint = line.p2() - edgeOffset;
        } else {
            sourcePoint = destPoint = line.p1();
        }
}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself and set dashing
    if (isDashed) {
         painter->setPen(QPen(edgeColor, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    }else{
         painter->setPen(QPen(edgeColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    painter->drawLine(line);

//    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

//    QPointF sourceArrowP1 = ((sourcePoint + destPoint) / 2) + QPointF(sin(angle + M_PI / 3) * arrowSize,
//                                                  cos(angle + M_PI / 3) * arrowSize);
//    QPointF sourceArrowP2 = ((sourcePoint + destPoint) / 2) + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
//                                                  cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPointF destArrowP1 = ((sourcePoint + destPoint) / 2) + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = ((sourcePoint + destPoint) / 2) + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                             cos(angle - M_PI + M_PI / 3) * arrowSize);
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setBrush(Qt::black);
    //painter->drawPolygon(QPolygonF() << ((line.p1() + line.p2()) / 2) << sourceArrowP1 << sourceArrowP2);
      painter->drawPolygon(QPolygonF() << ((line.p1() + line.p2()) / 2) << destArrowP1 << destArrowP2);
}

