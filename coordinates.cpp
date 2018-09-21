#include "coordinates.h"
#include <QtDebug>

#include <math.h>

Coordinates::Coordinates(int dim, QVector<double> *startingCoord) :  projectedX(0), projectedY(0), dimension(dim), d(200), s(100), indexOfTwoD(0)
{
    matrix = QVector<QVector<double>>(dimension, QVector<double>(dimension));
    for(int row = 0; row < dimension; row++){
           for(int col = 0; col < dimension; col++){
               if (row == col)
                   matrix[row][col] = 1;
               else
                   matrix[row][col] = 0;
           }
       }


      coordinates = *startingCoord;
      projectPoint();

      coordinateMatrix = QVector<QVector<double>>(dimension, QVector<double>(1));
      for(int i = 0; i < dimension; i++){
              coordinateMatrix[i][0] = coordinates[i];
      }
}

void Coordinates::projectPoint()
{
    QVector<double> lowerDimCoord = coordinates;
    for(int i = 0; i < dimension-2; i++){
        double valueDropped = lowerDimCoord[lowerDimCoord.count()-1];
        for(int j = 0; j < lowerDimCoord.count()-1; j++){
            lowerDimCoord[j] = lowerDimCoord[j]*d / (valueDropped + s + d);

        }
        lowerDimCoord.removeLast();
}

    projectedX = lowerDimCoord[0];
    projectedY = lowerDimCoord[1];

//    qDebug() << lowerDimCoord;
//    qDebug() << coordinates;

}

void Coordinates::setProjectedValues()
{
//    projectedX = (*(*allCoordinates)[indexOfTwoD]->coordinates)[0];
    //    projectedY = (*(*allCoordinates)[indexOfTwoD]->coordinates)[1];
}

void Coordinates::rotate(int i, int j, double theta)
{
        QVector<double> tempVector = QVector<double>();
        tempVector.append(matrix[i][i]);
        tempVector.append(matrix[j][j]);
        tempVector.append(matrix[i][j]);
        tempVector.append(matrix[j][i]);

        matrix[i][i] = cos(theta);
        matrix[j][j] = cos(theta);
        matrix[i][j] = sin(theta);
        matrix[j][i] = -sin(theta);

        QVector<QVector<double>> rotatedCoordinates (dimension, QVector<double>(1));




        for(int i = 0; i < dimension; i++){
                rotatedCoordinates[i][0] = 0;
        }

        for(int i = 0; i < dimension; i++){
            //currentCoordinates[i][0] = coordinates[i];
            for(int j = 0; j < 1; j++){
                for(int k = 0; k < dimension; k++){
                    rotatedCoordinates[i][j] += matrix[i][k] * coordinateMatrix[k][j];
                }
            }
        }
    //qDebug() << coordinates;
        for(int i = 0; i < dimension; i++){
            coordinates[i] = rotatedCoordinates[i][0];
            coordinateMatrix[i][0] = rotatedCoordinates[i][0];
        }
    //qDebug() << coordinates;

        projectPoint();

        matrix[i][i] = tempVector[0];
        matrix[j][j] = tempVector[1];
        matrix[i][j] = tempVector[2];
        matrix[j][i] = tempVector[3];
}

//CoordinateNode::CoordinateNode(double dropped, QVector<double> *coord, int dimension) :  coordinates(coord), droppedCoord(dropped), dimension(dimension)
//{

//}
