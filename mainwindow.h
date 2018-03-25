#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//C++

//Qt
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>

//ADT
#include "jsonreader.h"
#include "sparsematrix.h"



class Tcp_Server;

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
    void socketReceive();

    void Star_Server();

    void Stop_Server();

    void Star_Listening();

    void SendMessage(QString msg);

    void on_btnServer_Start_clicked();

    void on_btnServer_Stop_clicked();

    void on_btnMatrix_Graph_clicked();

    void Load_Mattix();

    void Graph_Matrix();

    void on_btnLisent_to_Client_clicked();

    void Original();

    void Iniciado();

    void Apagado();

    void Escuchando();

    void UpDate_Req(QString Req);

private:
    Ui::MainWindow *ui;

    SparseMatrix* Mtx;
    Tcp_Server* mServer;
    //Decoder* decoTools;
};

#endif // MAINWINDOW_H
