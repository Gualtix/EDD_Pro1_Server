#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//C++

//Qt
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>

//ADT
#include "jsonreader.h"




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
};

#endif // MAINWINDOW_H
