#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "coordinates.h"

#include <algorithm>
#include <math.h>
#include <bitset>
#include <iostream>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QStack>
#include <QList>
#include <QQueue>

# define M_PI           3.14159265358979323846  /* pi */

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), nodeVector(), timer(new QTimer(this)), rotX(0), rotY(0), rotZ(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 720, 500);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Adinkra Nodes"));

    rotation = 0;
    basis.append(105);
    basis.append(202);
    basis.append(172);
    basis.append(240);
    length = 8;

//225 114 180 216
//    basis.append(225);
//    basis.append(114);
//    basis.append(180);
//    basis.append(216);

    //209 114 228 184

//    basis.append(209);
//    basis.append(114);
//    basis.append(228);
//    basis.append(184);

//53 86 120
//        basis.append(53);
//        basis.append(83);
//        basis.append(120);

//    basis.append(15);
//    basis.append(240);
    //23 232
//    basis.append(23);
//    basis.append(232);

//    basis.append(27);
//    basis.append(60);


    dimension = basis.size();
    //dimension = 4;
    int numNodes = (1 << (length - dimension));
    int totalCodeWords = 1 << length;
    QVector<QColor> colors;
       double nextHue = 0.2f;
//       for(int i = 0; i < length; i++) {
//           QColor nextColor = QColor(0,0,0);
//           nextColor.toHsl();
//           nextHue += .6135;
//           if (nextHue>1) {
//               nextHue-=1;
//           }
//           nextColor.setHslF(nextHue,.5f,.4f);
//           colors.append(nextColor);
//       }
       colors.append(QColor(255,96,96));
       colors.append(QColor(211,85,255));
       colors.append(QColor(87,98,255));
       colors.append(QColor(255,157,83));
       colors.append(QColor(255,217,83));
       colors.append(QColor(75,255,170));
       colors.append(QColor(75,194,255));
       colors.append(QColor(0,0,0));

       int start = -180;
       int end = 600;
       int numNodesPerLevel = numNodes/2;
       int dx = (abs(start) + abs(end)) / numNodesPerLevel;

       int evenStep = 0;
       int oddStep = 0;
       int step;

       //       QVector<int>* code = createCode();
       //       qDebug() << *code << endl;
       //       for(int i = 0; i < numNodes; i++){
       //
       //       }


    QVector<int> codeWordsToUse = QVector<int>();
    QVector<int> indices = {0,1,2,4};

    for(int codeword = 0; codeword < totalCodeWords; codeword++){
         int word = codeword;
         for(int bit = 0; bit < length; bit++){
             if(indices.contains(bit)){
                 if((word>>bit)&1){
                     int baseWord = (bit == 0 ? 105 : (bit == 1 ? 202: (bit == 2 ? 172 : 240))); // ew
                     word = word ^ baseWord;
                 }
             }
         }

         if(!codeWordsToUse.contains(word)){
             codeWordsToUse.append(word);
         }
    }

    for(int word = 0; word < numNodes; word++){
        bool isBoson = std::bitset<64> (codeWordsToUse[word]).count()%2;
        //qDebug() << (codeWordsToUse[word]) << ", numOnes = " << std::bitset<sizeof(int)>(codeWordsToUse[word]).count();
        step = isBoson ? oddStep++ : evenStep++;
        QVector<double> *coordinates = createLevelCoordinates(isBoson,start,dx*step);
        Node* node = new Node(this, isBoson, codeWordsToUse[word]);
        nodeVector.append(node);
        scene->addItem(node);
        //qDebug()<< (*coordinates);
        node->setPos((*coordinates)[0],(*coordinates)[1]);
        //node->setPos(100,100);
    }

    for(int node = 0; node < numNodes; node++){
        Node* first = nodeVector[node];
        for(int color = 0; color < colors.count(); color++){
            int firstNodeNumber = nodeVector[node]->getNodeNumber();
            int numberToFind = firstNodeNumber^(1<<color);
            for(int bit = 0; bit < length; bit++){
                if(indices.contains(bit)){
                    if((numberToFind>>bit)&1){
                        int baseWord = (bit == 0 ? 105 : (bit == 1 ? 202: (bit == 2 ? 172 : 240))); // ew
                        numberToFind = numberToFind ^ baseWord;
                    }
                }
            }
            for(int secondNode = node+1; secondNode < numNodes; secondNode++){
                Node* second = nodeVector[secondNode];
                if(second->getNodeNumber() == numberToFind){
                    //qDebug() << first->getNodeNumber()<<"," << second->getNodeNumber();
                    Edge* edge = new Edge(first,second,false,colors[color]);
                    scene->addItem(edge);
                    break;
                }
            }
        }


    }


//    for(int i =0 ; i < numNodes; i++){
//        if(nodeVector[i]->getBoson()){
//            for(int color= 0; color < colors.count(); color++){
//                int firstNodeNumber = nodeVector[i]->getNodeNumber();
//                int numToFind = (firstNodeNumber^(1<<color));
//                Node *secondNode;
//                for(int k = 0; k < nodeVector.count(); k++){
//                    if(nodeVector[k]->getNodeNumber() == numToFind){
//                        secondNode = nodeVector[k];
//                        break;
//                    }
//                }

//                scene->addItem(new Edge(nodeVector[i],secondNode, false, colors[color]));
//            }

//        }
//    }


     //QVector<int>* indices = createIndex();

//      int start = -180;
//       int end = 600;
//       int numNodesPerLevel = numNodes/2;
//       int dx = (abs(start) + abs(end)) / numNodesPerLevel;

//       int evenStep = 0;
//       int oddStep = 0;
//       int step;

//       QVector<int>* code = createCode();
//       qDebug() << *code << endl;
//       for(int i = 0; i < numNodes; i++){
//           step = (*code)[i] %2 ? evenStep++ : oddStep++;
//           //qDebug() << (*code)[i] << endl;
//           nodeVector.append(new Node(this, (*code)[i] % 2, (*code)[i]));
//           nodeVector[i]->setEdgeNumber(indices);
//           QVector<double> *tempVector = createLevelCoordinates((*code)[i] % 2, start, dx*step);
//           //nodeVector[i]->coordinates = new Coordinates(2,tempVector);
//           scene->addItem(nodeVector[i]);
//           nodeVector[i]->setPos((*tempVector)[0],(*tempVector)[1]);
//       }

//       for(int i = 0; i < numNodes; i++){
//           if(!nodeVector[i]->getBoson()){
//               for(int j = 0; j < numNodes ; j++){
//                   if(nodeVector[j]->getBoson()){
//                       qDebug() << "NODE I : " << nodeVector[i]->getNodeEdgeNumber() ;
//                       qDebug() << "NODE J : " << nodeVector[j]->getNodeEdgeNumber() ;
//                       qDebug() << "Result : " << (nodeVector[i]->getNodeEdgeNumber() ^ nodeVector[j]->getNodeEdgeNumber()) << endl;
//                       std::bitset<sizeof(int)> result (nodeVector[i]->getNodeEdgeNumber() ^ nodeVector[j]->getNodeEdgeNumber());
//                       qDebug() << result.count() << endl;
//                       if(result.count() == 1){
//                           scene->addItem(new Edge(nodeVector[i], nodeVector[j], std::bitset<sizeof(int)> (i >> getDifferingPlace(i,j)).count()%2, colors[getDifferingPlace(i,j)]));
//                        }
//                }
//           }

//        }
//       }

    //qDebug() << numNodes;

//       //For Cubes
//    for(int i = 0; i < numNodes; i++){
//         //int number = createNumber((*code)[i],indices);
//         //qDebug() << (*code)[i];
//         step = (*code)[i]%2 ? evenStep++ : oddStep++;
//         Node* node = new Node(this, (*code)[i]%2,(*code)[i]);
//         nodeVector.append(node);
//         //nodeVector.append(new Node(this, (*code)[i] % 2, (*code)[i]));
//         //nodeVector[i]->setEdgeNumber(number);
//        QVector<double> *coordinates = createLevelCoordinates((*code)[i] % 2, start, dx*step);
//       // qDebug() << *coordinates;
//        scene->addItem(nodeVector[i]);
//        nodeVector[i]->setPos((*coordinates)[0],(*coordinates)[1]);
//    }


//    int number = 0;
//    for(int i = 0; i < numNodes; i++){
//        if(nodeVector[i]->getBoson()){
//            for(int j = 0; j < numNodes; j++){
//                if(!(nodeVector[j]->getBoson())){
//                    int firstNodeNumber = nodeVector[i]->getNodeNumber();
//                    int secondNodeNumber = nodeVector[j]->getNodeNumber();
//                     qDebug() << firstNodeNumber <<"," << secondNodeNumber;
//                    int result = firstNodeNumber^secondNodeNumber;

//                            scene->addItem(new Edge(nodeVector[i],nodeVector[j],false,colors[getDifferingPlace(firstNodeNumber,secondNodeNumber)-1]));
//                            number++;

//                }
//            }
//        }
//    }

//    for(int i = 0; i < numNodes; i++){
//        int firstNodeNumber = nodeVector[i]->getNodeNumber();
//            for(int j = i+1; j < numNodes; j++){
//                int secondNodeNumber = nodeVector[j]->getNodeNumber();
//                qDebug() << firstNodeNumber <<"," << secondNodeNumber;
//                qDebug() << ((!(firstNodeNumber%2) && secondNodeNumber%2) || (firstNodeNumber%2 && !(secondNodeNumber%2)));
//                bool match = (!(firstNodeNumber%2)) ? ((!(firstNodeNumber%2) && secondNodeNumber%2)) : (firstNodeNumber%2 && !(secondNodeNumber%2));
//                if(match){
//                    int result = firstNodeNumber^secondNodeNumber;
//                    for(int color = 0; color < 4; color++){
//                       // qDebug() << result;
//                        if(result&1){
//                            qDebug() << color;
//                            scene->addItem(new Edge(nodeVector[i],nodeVector[j],false,colors[color]));
//                        }
//                        result = result >> 1;
//                    }
//                }

//            }


//    }
//    for(int i = 0; i < numNodes; i++){
//        for(int j = i + 1; j < numNodes ; j++){
//            std::bitset<sizeof(int)> result (nodeVector[i]->getNodeEdgeNumber() ^ nodeVector[j]->getNodeEdgeNumber());
//            //std::cout << result<< endl;
//            if(result.count() == 1){
//                int iNum = nodeVector[i]->getNodeEdgeNumber();
//                int jNum = nodeVector[j]->getNodeEdgeNumber();
//                qDebug() << "I:" << iNum << "J:" << jNum;
//                qDebug() <<"Differing Value: "<< getDifferingPlace(iNum,jNum);
//                qDebug() << "SHIFTED VALUE:" << ( ) << endl;

//                scene->addItem(new Edge(nodeVector[i], nodeVector[j], std::bitset<sizeof(int)> (iNum >> getDifferingPlace(iNum,jNum)).count()%2, colors[getDifferingPlace(iNum,jNum)-1]));

//            }
//        }


//    }
    bfs();
    connect(timer, &QTimer::timeout, this, &GraphWidget::doStep);
}

void GraphWidget::bfs()
{
    //Mark all nodes as not visited
    for(int node = 0; node < nodeVector.count(); node++){
        nodeVector[node]->visited = false;
        nodeVector[node]->height = 0;
    }
    QQueue<Node*> q = QQueue<Node*>();
    //Maybe add a node as a parameter but for now just the first
    q.enqueue(nodeVector[0]);

    int dx = 90;
    int dy = 125;

    int start = -180;

    int height = 1;
    int prevHeight = 0;
    int numNodesOnLine = 0;

    while(!q.isEmpty()){
        Node *n = q.dequeue();
        if(!n->visited){

            n->visited = true;

            if(prevHeight != n->height){
                height++;
                prevHeight = n->height;
                numNodesOnLine = 0;
            }else{
                numNodesOnLine++;

            }

            n->setPos(start+(numNodesOnLine*dx), n->height*dy);




            //Do math here

            QList<Edge*> edgeList = n->getEdgeList();
            for(int edge = 0;edge < edgeList.count(); edge++){
                Node* nextNode = edgeList[edge]->sourceNode()->getNodeNumber() == n->getNodeNumber() ?  edgeList[edge]->destNode() :  edgeList[edge]->sourceNode();
                nextNode->height = height;
                q.enqueue(nextNode);
            }

        }
    }
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        //centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        //centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        //centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        //centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
       // shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{

}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();

    // Fill
    QColor backGroundColor = QColor(255,255,255);
    painter->fillRect(rect.intersected(sceneRect), backGroundColor);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::startAnimation(){
    timer->setInterval(20);
    timer->setSingleShot(false);
    timer->start();
}

void GraphWidget::stopAnimation()
{
    timer->stop();
}

void GraphWidget::rotXChanged(double newX)
{
    rotX = newX;
}

void GraphWidget::rotYChanged(double newY)
{
    rotY = newY;
}

void GraphWidget::rotZChanged(double newZ)
{
    rotZ = newZ;
}

void GraphWidget::doStep(){
    for(int i = 0; i < (1 << dimension); i++){
        nodeVector[i]->coordinates->rotate(0,1,M_PI* 1/200);
        nodeVector[i]->coordinates->rotate(0,2,M_PI/200);
        nodeVector[i]->coordinates->rotate(2,3,M_PI/200);

        nodeVector[i]->setPos(nodeVector[i]->coordinates->projectedX, nodeVector[i]->coordinates->projectedY);
    }
}

QVector<double>* GraphWidget::createCoordinates(int dim, int nodeNumber){
    QVector<double> *coordinates = new QVector<double>();
    for(int i = 0; i < dim; i++){
        coordinates->append(nodeNumber & 1 ? 100 : -500);
        nodeNumber = (nodeNumber >> 1);
    }

    return coordinates;
}

QVector<double> *GraphWidget::createLevelCoordinates(bool isEven, int start, int step)
{
    QVector<double> *coordinates = new QVector<double>();
    coordinates->append(start + step);
    coordinates->append(isEven? 200 : -100);

    return coordinates;

}

QVector<int> *GraphWidget::createIndex()
{
     QVector<unsigned int> tempBasis = basis;
     QVector<int>* index = new QVector<int>();
     bool isLine;
     int shiftCounter = 0;
     for(int i = 0; i < tempBasis.size(); i++){
            bool foundOne = false;
            while(!foundOne || shiftCounter == length){
                if (tempBasis[i] & 1){
                    foundOne = true;
                    index->append(shiftCounter);
                }
                    //shift
                    for(int j = 0; j < tempBasis.size(); j++){
                        tempBasis[j] = tempBasis[j] >> 1;
                    }
                    shiftCounter++;

            }
     }
     return index;
}

int GraphWidget::createNumber(int nodeNumber, QVector<int>* indices)
{
    int number;
    int edgingNodeNumber = 0;
    for(int i = 0; i < indices->size(); i++){
        number = nodeNumber;
        if(((number >> (*indices)[i]) & 1)){
            edgingNodeNumber |= (1 << i);
        }
    }
    return edgingNodeNumber;
}

int GraphWidget::getDifferingPlace(int node1, int node2){
    int i = 0 ;
    int sum = node1 ^ node2;
    while(sum != 0){
        i++;
        sum = sum >> 1;
    }
    return i;//-1;
}

QVector<int>* GraphWidget::createCode(){
    QVector<int> *code = new QVector<int>();
    int res = 0;
        for (int n = 0; n < (1 << dimension); n++) {
            res = 0;
            for (int i = 0; i < dimension; i++) {
                if (n & ((int)pow(2, i))) {// cast int
                    res ^= basis[i];
                }
            }
            code->append(res);
            //qDebug() << res<< endl;
        }

    std::sort(code->begin(),code->end());
    return code;
}
