#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QTimer>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    int getDifferingPlace(int node1, int node2);
    int dimension;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void startAnimation();
    void stopAnimation();
    void rotXChanged(double newX);
    void rotYChanged(double newY);
    void rotZChanged(double newZ);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    QVector<Node*> nodeVector;
    QTimer *timer;
    int rotation;
    double rotX, rotY, rotZ;

    QVector<double>* createCoordinates(int dim, int nodeNumber);
private slots:
    void doStep();
};

#endif // GRAPHWIDGET_H
