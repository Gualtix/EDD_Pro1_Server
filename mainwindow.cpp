//C++

//Qt
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>

//ADT
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decoder.h"
#include "static_storage.h"


//Static Storage Definition
QString Static_Storage::Nickname = "Nobody Logged";
QString Static_Storage::Repy_Status = "None";
QString Static_Storage::JSon_URL = "";

//(^< ............ ............ ............ Constructor: Set
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //(^< ............ T A B L E
    ui->tblRequest_History->setColumnWidth(1,140);
    ui->tblRequest_History->setColumnWidth(2,250);
    ui->tblRequest_History->setEditTriggers(QAbstractItemView::NoEditTriggers);

    Mtx = new SparseMatrix();

    //(^< ............ S E R V E R
    mServer = new QTcpServer(this);
    mServer->setMaxPendingConnections(2);

    //(^< ............ C L I E N T
    mClient = new QTcpSocket(this);

    Original();

    on_btnServer_Start_clicked();
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

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Server Management
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


void MainWindow::Nw_Connection(){
    ui->lblListening->setText("<font color='green'>Connection Established...</font>");
    mClient = mServer->nextPendingConnection();
    connect(mClient,SIGNAL (readyRead()),this,SLOT (socketReceive()));
}


void MainWindow::Star_Server(){


    if (!mServer->listen(QHostAddress::Any, 4328)){
        QMessageBox::critical(this,"Error",mServer->errorString());
    }
    else{
        connect(mServer,SIGNAL(newConnection()),this,SLOT(Nw_Connection()));
        Iniciado();
        Load_Mattix();
        //QMessageBox::information(this,"Servidor","Server has Started");
    }
}

void MainWindow::Stop_Server(){
    Apagado();
    QMessageBox::critical(this,"Error","Server has Stopped");
    //close();
}


//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Socket Handle
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::socketReceive(){

    QByteArray Bf;
    Bf.resize(mClient->bytesAvailable());
    mClient->read(Bf.data(),Bf.size());

    QString msg = (QString (Bf));

    ui->tboxRequest->setText("");
    ui->tboxRequest->setText(msg);

    Decoder* decoTools = new Decoder();

    decoTools->GetStack_of_Instructions(msg);

    QString Answer = decoTools->Answer_Request(Mtx);
    SendMessage(Answer);

    QString Req = decoTools->WList->First->Data->Cad;
    UpDate_Req(Req);
}

void MainWindow::SendMessage(QString msg){

    ui->tboxReply->setText("");
    ui->tboxReply->setText(msg);

    if(mClient){
        QTextStream T(mClient);
        T << msg;
        mClient->flush();
    }
}

//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Matrix Handle
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............

void MainWindow::Load_Mattix(){


    //Mtx->Load_JSon_Vertical_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/usuarios.json");
    //Mtx->Load_JSon_Horizontal_Headers("/home/wrm/SERVER_PRO_1/SERVER_PRO_1/archivos.json");


    Mtx->Load_JSon_Vertical_Headers("US_DIR/usuarios.json");
    Mtx->Load_JSon_Horizontal_Headers("ARCH_DIR/archivos.json");
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

    QTime Tm = QTime::currentTime();

    AddTableItem(0,Static_Storage::Nickname,Req,Static_Storage::Repy_Status,Tm.toString());

    if(Req == "Log_In"){
        ui->lblLastReq->setText("Log_In");
        ui->lblNickname->setText(Static_Storage::Nickname);

    }
    else if(Req == "Sign_In"){
        ui->lblLastReq->setText("Sign_In");
        ui->lblNickname->setText("<font color='red'>Nobody Logged</font>");
    }
    else if(Req == "Get_User_Files"){
        ui->lblLastReq->setText("Get_User_Files");
    }
    else if(Req == "Create_File"){
        ui->lblLastReq->setText("Create_File");
    }
    else if(Req == "Block_File"){
        ui->lblLastReq->setText("Block_File");
    }
    else if(Req == "Release_File"){
        ui->lblLastReq->setText("Release_File");
    }
    else if(Req == "Save_File"){
        ui->lblLastReq->setText("Save_File");
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
    ui->btnServer_Stop->setEnabled(true);
    ui->btnMatrix_Graph->setEnabled(true);
    //ui->btnLisent_to_Client->setEnabled(true);

    ui->lblStatus->setText("<font color='green'>ON</font>");
    ui->lblListening->setText("<font color='blue'>Listening...</font>");
}


void MainWindow::Apagado(){

    ui->btnServer_Start->setEnabled(true);
    ui->btnServer_Stop->setEnabled(false);
    ui->btnMatrix_Graph->setEnabled(true);
    //ui->btnLisent_to_Client->setEnabled(false);

    ui->lblStatus->setText("<font color='red'>OFF</font>");
    ui->lblListening->setText("<font color='red'>No Listening</font>");
}


//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............
//(^< ............ ............ ............ ............ ............ Actions
//(^< ............ ............ ............ ............ ............ ............ ............ ............ ............ ............


void MainWindow::AddTableItem(int Rk,QString Usuario,QString Solicitud,QString Respuesta,QString Tiempo){

    ui->tblRequest_History->insertRow(Rk);

    ui->tblRequest_History->setItem(Rk,0,new QTableWidgetItem(Usuario));
    ui->tblRequest_History->setItem(Rk,1,new QTableWidgetItem(Solicitud));
    ui->tblRequest_History->setItem(Rk,2,new QTableWidgetItem(Respuesta));
    ui->tblRequest_History->setItem(Rk,3,new QTableWidgetItem(Tiempo));

}











