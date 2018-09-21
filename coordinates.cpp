#include "coordinates.h"
#include<QtDebug>

Coordinates::Coordinates(int dim, QVector<double> *startingCoord) :  projectedX(0), projectedY(0), dimension(dim), d(200), s(50), indexOfTwoD(0)
{
//    allCoordinates = new QVector<CoordinateNode*>();
//    CoordinateNode *node = new CoordinateNode(-1,startingCoord, dimension);
//    allCoordinates->append(node);
      coordinates = *startingCoord;
      projectPoint();

      //setProjectedValues();
}

void Coordinates::projectPoint()
{
//    int i;
//    for(i = 0; i < dimension-1; i++){
//        CoordinateNode *currentNode = (*allCoordinates)[i];
//        double valueDropped = (*(currentNode->coordinates))[currentNode->coordinates->count()-1];

//        QVector<double> *nextCoord = new QVector<double>();
//        for(int j = 0; j < currentNode->coordinates->count()-1; j++){
//            nextCoord->append(((*(currentNode->coordinates))[j]*d /(valueDropped + s + d)));

//        }
//        allCoordinates->append(new CoordinateNode(valueDropped, nextCoord, dimension-1));
//    }

//    indexOfTwoD = i - 1;
    QVector<double> lowerDimCoord = coordinates;
    for(int i = 0; i < dimension-2; i++){
        qDebug() << i;
        double valueDropped = lowerDimCoord[lowerDimCoord.count()-1];
        qDebug() << valueDropped;
        for(int j = 0; j < lowerDimCoord.count()-1; j++){
            qDebug() << j;
            lowerDimCoord[j] = lowerDimCoord[j]*d / (valueDropped + s + d);

        }
        lowerDimCoord.removeLast();
        qDebug() << lowerDimCoord;
        qDebug() << coordinates;
    }

    projectedX = lowerDimCoord[0];
    projectedY = lowerDimCoord[1];

    qDebug() << lowerDimCoord;
    qDebug() << coordinates;

}

void Coordinates::setProjectedValues()
{
//    projectedX = (*(*allCoordinates)[indexOfTwoD]->coordinates)[0];
//    projectedY = (*(*allCoordinates)[indexOfTwoD]->coordinates)[1];
}

//CoordinateNode::CoordinateNode(double dropped, QVector<double> *coord, int dimension) :  coordinates(coord), droppedCoord(dropped), dimension(dimension)
//{

//}
