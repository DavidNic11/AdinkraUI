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
       // qDebug() << i;
        double valueDropped = lowerDimCoord[lowerDimCoord.count()-1];
        //qDebug() << valueDropped;
        for(int j = 0; j < lowerDimCoord.count()-1; j++){
            //qDebug() << j;
            lowerDimCoord[j] = lowerDimCoord[j]*d / (valueDropped + s + d);

        }
        lowerDimCoord.removeLast();
//        qDebug() << lowerDimCoord;
//        qDebug() << coordinates;
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
    //qDebug() << "In Rotate";
    //vector<vector<int> > matrix;
    //vector<vector<int> > v(10, vector<int>(10,1));
    QVector<QVector<double>> matrix (dimension, QVector<double>(dimension));

    for(int row = 0; row < dimension; row++){
           for(int col = 0; col < dimension; col++){
               if (row == col)
                   matrix[i][j] = 1;
               else
                   matrix[i][j] = 0;
           }
       }
        //qDebug() << "here";
        matrix[i][i] = cos(theta);
        matrix[j][j] = cos(theta);
        matrix[i][j] = sin(theta);
        matrix[j][i] = -sin(theta);

        QVector<QVector<double>> rotatedCoordinates (dimension, QVector<double>(1));

        QVector<QVector<double>> currentCoordinates (dimension, QVector<double>(1));


        for(int i = 0; i < dimension; i++){
                currentCoordinates[i][0] = coordinates[i];
                rotatedCoordinates[i][0] = 0;
        }

        for(int i = 0; i < dimension; i++){
            //currentCoordinates[i][0] = coordinates[i];
            for(int j = 0; j < 1; j++){
                for(int k = 0; k < dimension; k++){
                    rotatedCoordinates[i][j] += matrix[i][k] * currentCoordinates[k][j];
                }
            }
        }

        for(int i = 0; i < dimension; i++){
            coordinates[i] = currentCoordinates[i][0];
        }

        projectPoint();
}

//CoordinateNode::CoordinateNode(double dropped, QVector<double> *coord, int dimension) :  coordinates(coord), droppedCoord(dropped), dimension(dimension)
//{

//}
