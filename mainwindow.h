#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPropertyAnimation *animation;

    void createMenus();
    void createActions();

    QMenu *fileMenu;
    QAction *printAction;

public slots:
    void on_pbStart_clicked();
    void on_pbEnd_clicked();

    void print();

};

#endif // MAINWINDOW_H
