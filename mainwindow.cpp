#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localserver.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
        mLocalServer = new LocalServer(this);
    }

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_iniciar_clicked(){
    //Local ---> if(!mLocalServer->listen("Shared_Files_Server")){
    if(!mLocalServer->listen(QHostAddress::AnyIPv4,4328)){
        QMessageBox::critical(this,"Error",mLocalServer->errorString());
    }
    else{
        QMessageBox::information(this,"Servidor","Iniciado...");
    }

}

void MainWindow::on_enviar_clicked(){
    mLocalServer->envia(ui->msj->text());
}

void MainWindow::on_quitar_clicked(){
    close();
}


