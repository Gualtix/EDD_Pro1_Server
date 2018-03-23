#ifndef LOCALSERVER_H
#define LOCALSERVER_H

//Local ---> #include <QLocalServer>
#include <QTcpServer>

class QLocalSocket;

//Local ---> class LocalServer : public QLocalServer
class LocalServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);
    ~LocalServer();
    void envia(const QString &msj);

private:
    //Local ---> QLocalSocket* mSocket;
    QTcpSocket* mSocket;
};

#endif // LOCALSERVER_H
