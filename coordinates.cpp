#include "coordinates.h"
#include<QtDebug>

Coordinates::Coordinates(int dim, QVector<double> *startingCoord) : dimension(dim), d(100), s(100), projectedX(0), projectedY(0), indexOfTwoD(0)
{

    CoordinateNode *node = new CoordinateNode(-1,startingCoord, dimension);
    qDebug() << "no0";
    allCoordinates->append(node);
    qDebug() << "closer";
    projectPoint();
    setProjectedValues();
}

void Coordinates::projectPoint()
{
    int i;
    for(i = 0; i < dimension-2; i++){
        CoordinateNode *currentNode = (*allCoordinates)[i];
        double valueDropped = (*(currentNode->coordinates))[currentNode->coordinates->count()-1];

        QVector<double> *nextCoord = new QVector<double>();

        for(int j = 0; j < currentNode->coordinates->count()-2; j++){
            nextCoord->append(((*(currentNode->coordinates))[j]*d / valueDropped + s + d));
        }
        allCoordinates->append(new CoordinateNode(valueDropped, nextCoord, dimension-1));
    }
    qDebug() << i;

    indexOfTwoD = i;

}

void Coordinates::setProjectedValues()
{
    projectedX = (*(*allCoordinates)[indexOfTwoD]->coordinates)[0];
    projectedY = (*(*allCoordinates)[indexOfTwoD]->coordinates)[1];
}

CoordinateNode::CoordinateNode(double dropped, QVector<double> *coord, int dimension) :  coordinates(coord), droppedCoord(dropped), dimension(dimension)
{

}
