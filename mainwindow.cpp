#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
//#include <QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dimModel = new QStandardItemModel(this);
    ui->rotateTable->setModel(dimModel);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            dimModel->appendRow(new QStandardItem("text"));
        }
    }
//    connect(ui->sbX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotXChanged);
//    connect(ui->sbY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotYChanged);
//    connect(ui->sbZ, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotZChanged);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(printAction);
}

void MainWindow::createActions()
{
    printAction = new QAction(tr("&Print"), this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(tr("Print"));

    connect(printAction, &QAction::triggered, this, &MainWindow::print);
}

void MainWindow::on_pbStart_clicked()
{
    ui->widget->startAnimation();
}

void MainWindow::on_pbEnd_clicked()
{
    ui->widget->stopAnimation();
}

void MainWindow::print()
{
    //qDebug() << "Print Button Pressed";
    //QSize fn = QSize();
//    QImage image = QImage();
//    QPainter painter(&image);
//    painter.setRenderHint(QPainter::Antialiasing);
//     ui->widget->scene()->render(&painter);
//    image.save("file_name.png");


}
