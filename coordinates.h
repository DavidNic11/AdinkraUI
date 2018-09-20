#ifndef COORDINATES_H
#define COORDINATES_H

#include <QVector>

struct CoordinateNode{

    QVector<double> *coordinates;
    double droppedCoord;
    int dimension;

    CoordinateNode(double dropped, QVector<double> *coord, int dimension);
};

class Coordinates
{
public:
    Coordinates(int dim, QVector<double> *startingCoord);

    void projectPoint();
private:
    int dimension;
    int d;
    int s;
    QVector<CoordinateNode*> *allCoordinates;
};

#endif // COORDINATES_H
