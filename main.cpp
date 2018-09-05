#include "mainwindow.h"
#include <QApplication>

#include <graphwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWidget *widget = new GraphWidget;
    MainWindow w;
    w.setCentralWidget(widget);
    w.show();

    return a.exec();
}
