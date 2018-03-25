#ifndef TCP_SERVER_H
#define TCP_SERVER_H

//C++

//Qt
#include <QLabel>
#include <QTcpServer>

//ADT


class QTcpSocket;

class Tcp_Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Tcp_Server(QObject *parent = nullptr);
    ~Tcp_Server();

public slots:
    void socketSend(QString msg);
    void socketReceive();
    void startListening();


public:
    QTcpSocket* Tcp_Socket_Client;
    QString Server_Client_Status;
};

#endif // TCP_SERVER_H
