#include "localserver.h"
//Local ---> #include <QLocalSocket>
#include <QTcpSocket>
#include <QTextStream>


//Local ---> LocalServer::LocalServer(QObject *parent) : QLocalServer(parent){
LocalServer::LocalServer(QObject *parent) : QTcpServer(parent){
    mSocket = nullptr;
    connect(this, &LocalServer::newConnection, [&](){
        mSocket = nextPendingConnection();
    });
}

void LocalServer::envia(const QString &msj){

    if(mSocket){
        QTextStream T(mSocket);
        T << msj;
        mSocket->flush();
    }
}

LocalServer::~LocalServer(){


}
