#include "coordinates.h"
#include<QtDebug>

Coordinates::Coordinates(int dim, QVector<double> *startingCoord) :  projectedX(0), projectedY(0), dimension(dim), d(100), s(100), indexOfTwoD(0)
{
    allCoordinates = new QVector<CoordinateNode*>();
    CoordinateNode *node = new CoordinateNode(-1,startingCoord, dimension);
    allCoordinates->append(node);
    projectPoint();

    setProjectedValues();
}

void Coordinates::projectPoint()
{
    int i;
    for(i = 0; i < dimension-1; i++){
        CoordinateNode *currentNode = (*allCoordinates)[i];
        double valueDropped = (*(currentNode->coordinates))[currentNode->coordinates->count()-1];

        QVector<double> *nextCoord = new QVector<double>();
        for(int j = 0; j < currentNode->coordinates->count()-1; j++){
            nextCoord->append(((*(currentNode->coordinates))[j]*d /(valueDropped + s + d)));

        }
        allCoordinates->append(new CoordinateNode(valueDropped, nextCoord, dimension-1));
    }

    indexOfTwoD = i - 1;

}

void Coordinates::setProjectedValues()
{
    projectedX = (*(*allCoordinates)[indexOfTwoD]->coordinates)[0];
    projectedY = (*(*allCoordinates)[indexOfTwoD]->coordinates)[1];
}

CoordinateNode::CoordinateNode(double dropped, QVector<double> *coord, int dimension) :  coordinates(coord), droppedCoord(dropped), dimension(dimension)
{

}
