//C++
#include <exception>

//Qt
#include <QTcpSocket>
#include <QTextStream>
#include "mainwindow.h"

//ADT
#include "tcp_server.h"

//Static_Defs


//(^< ............ ............ ............ Constructor: Set
Tcp_Server::Tcp_Server(QObject *parent) : QTcpServer(parent){

    parent = nullptr;
    Tcp_Socket_Client = nullptr;
    connect(this, &Tcp_Server::newConnection, [&](){
        Tcp_Socket_Client = nextPendingConnection();
        if(Tcp_Socket_Client){
            //startListening();
        }
    });
}

//(^< ............ ............ ............ Constructor: Send Message
void Tcp_Server::socketSend(QString msg){

    if(Tcp_Socket_Client){
        QTextStream T(Tcp_Socket_Client);
        T << msg;
        Tcp_Socket_Client->flush();
    }
}

//(^< ............ ............ ............ Constructor: catchMessage as Slot
void Tcp_Server::socketReceive(){

    QByteArray Bf;
    Bf.resize(Tcp_Socket_Client->bytesAvailable());
    Tcp_Socket_Client->read(Bf.data(),Bf.size());

    QString msg = (QString (Bf));

}

//(^< ............ ............ ............ Constructor: Receive Message
void Tcp_Server::startListening(){
    connect(Tcp_Socket_Client,SIGNAL (readyRead()),this,SLOT (socketReceive()));
}

//(^< ............ ............ ............ Destructor
Tcp_Server::~Tcp_Server(){

}
