#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sbX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotXChanged);
    connect(ui->sbY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotYChanged);
    connect(ui->sbZ, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui->widget, &GraphWidget::rotZChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbStart_clicked()
{
    ui->widget->startAnimation();
}

void MainWindow::on_pbEnd_clicked()
{
    ui->widget->stopAnimation();
}
