#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//C++

//Qt
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>

//ADT
#include "jsonreader.h"


class LocalServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_iniciar_clicked();

    void on_enviar_clicked();

    void on_quitar_clicked();



private:
    Ui::MainWindow *ui;
    LocalServer* mLocalServer;
};

#endif // MAINWINDOW_H
