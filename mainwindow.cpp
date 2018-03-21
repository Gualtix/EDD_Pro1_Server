#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){


    /*

    QString fileName = QFileDialog::getOpenFileName(NULL, tr("JSON PRODUCTOS"));
    //QString fileName = QFileDialog::getOp
        if(fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QByteArray ba = file.readAll();

        //JSonReader::Load_Files(ba);

        /*  "/home/wrm/SERVER_PRO_1/SERVER_PRO_1/usuarios.json" */
        /*  "/home/wrm/SERVER_PRO_1/SERVER_PRO_1/archivos.json" */






        ui->setupUi(this);
    }

MainWindow::~MainWindow()
{
    delete ui;
}
