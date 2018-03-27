//C++

//Qt
#include <QTcpSocket>
#include <QMessageBox>

//ADT
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcp_server.h"
#include "decoder.h"
#include "static_storage.h"

//Static Storage Definition
QString Static_Storage::Nickname = "<font color='red'>Nobody Logged</font>";

//(^< ............ ............ ............ Constructor: Set
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    Mtx = new SparseMatrix();
    mServer = new Tcp_Server(this);

    Original();

    on_btnServer_Start_clicked();
    //Star_Server();
    //Load_Mattix();


}

//(^< ............ ............ ............ Destructor
MainWindow::~MainWindow(){
    delete ui;
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ ui Events
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::on_btnServer_Start_clicked(){
    Star_Server();
}

void MainWindow::on_btnServer_Stop_clicked(){
    Stop_Server();
}

void MainWindow::on_btnMatrix_Graph_clicked(){
    Graph_Matrix();
}

void MainWindow::on_btnLisent_to_Client_clicked()
{
    Star_Listening();
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Server Management
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::Star_Server(){
    if(mServer->Tcp_Socket_Client == nullptr){
        if(!mServer->listen(QHostAddress::AnyIPv4,4328)){
            QMessageBox::critical(this,"Error",mServer->errorString());
            return;
        }
        else{
            Iniciado();
            Load_Mattix();
            //QMessageBox::information(this,"Servidor","Server has Started");
        }
    }
    else{
        Iniciado();
        ui->btnLisent_to_Client->setEnabled(false);
        QMessageBox::information(this,"Servidor","Server has Started");
    }
}

void MainWindow::Stop_Server(){
    Apagado();
    QMessageBox::critical(this,"Error","Server has Stopped");
    //close();
}

void MainWindow::Star_Listening(){

    if(mServer->Tcp_Socket_Client != nullptr){
        connect(mServer->Tcp_Socket_Client,SIGNAL (readyRead()),this,SLOT (socketReceive()));
        Escuchando();
    }
    else{
        QMessageBox::critical(this,"Error","Client APP has not Started");
    }
}


//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Socket Handle
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::socketReceive(){

    QByteArray Bf;
    Bf.resize(mServer->Tcp_Socket_Client->bytesAvailable());
    mServer->Tcp_Socket_Client->read(Bf.data(),Bf.size());

    QString msg = (QString (Bf));

    Decoder* decoTools = new Decoder();

    decoTools->GetStack_of_Instructions(msg);

    QString Answer = decoTools->Answer_Request(Mtx);
    SendMessage(Answer);

    QString Req = decoTools->WList->First->Data->Cad;
    UpDate_Req(Req);
}

void MainWindow::SendMessage(QString msg){
    mServer->socketSend(msg);
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Matrix Handle
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::Load_Mattix(){
    Mtx->Load_JSon_Vertical_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/usuarios.json");
    Mtx->Load_JSon_Horizontal_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/archivos.json");
}

void MainWindow::Graph_Matrix(){
    Mtx->DrawMatrix();
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Decoding
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ States
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::UpDate_Req(QString Req){

    if(Req == "Log_In"){
        ui->lblLastReq->setText("Log_In");
        ui->lblNickname->setText(Static_Storage::Nickname);

        mServer = new Tcp_Server(this);
    }
    else if(Req == "Sign_In"){
        ui->lblLastReq->setText("Sign_In");
        ui->lblNickname->setText("<font color='red'>Nobody Logged</font>");
    }

}

void MainWindow::Original(){

    //Buttons
    ui->btnServer_Start->setEnabled(true);
    ui->btnServer_Stop->setEnabled(false);
    ui->btnMatrix_Graph->setEnabled(false);
    ui->btnLisent_to_Client->setEnabled(false);

    //Labels
    ui->lblStatus->setText("<font color='red'>OFF</font>");
    ui->lblListening->setText("<font color='red'>No Listening</font>");
    ui->lblNickname->setText("<font color='red'>Nobody Logged</font>");

}

void MainWindow::Iniciado(){
    ui->btnServer_Start->setEnabled(false);
    ui->btnServer_Stop->setEnabled(false);
    ui->btnMatrix_Graph->setEnabled(true);
    ui->btnLisent_to_Client->setEnabled(true);

    ui->lblStatus->setText("<font color='green'>ON</font>");
}

void MainWindow::Escuchando(){
    ui->lblListening->setText("<font color='green'>Listenig</font>");
    ui->btnServer_Stop->setEnabled(true);
    ui->btnLisent_to_Client->setEnabled(false);
}

void MainWindow::Apagado(){

    ui->btnServer_Start->setEnabled(true);
    ui->btnServer_Stop->setEnabled(false);
    ui->btnMatrix_Graph->setEnabled(true);
    ui->btnLisent_to_Client->setEnabled(false);

    ui->lblStatus->setText("<font color='red'>OFF</font>");
}
























