#ifndef COORDINATES_H
#define COORDINATES_H

#include <QVector>

//struct CoordinateNode{

//    QVector<double> *coordinates;
//    double droppedCoord;
//    int dimension;

//    CoordinateNode(double dropped, QVector<double> *coord, int dimension);
//};

class Coordinates
{
public:
    Coordinates(int dim, QVector<double> *startingCoord);

    double projectedX;
    double projectedY;

    void projectPoint();
    void setProjectedValues();
    void rotate(int i, int j, double theta);
private:
    int dimension;
    int d;
    int s;
    int indexOfTwoD;

    QVector<QVector<double>> matrix;
    QVector<QVector<double>>coordinateMatrix;

    QVector<double> coordinates;
};

#endif // COORDINATES_H
