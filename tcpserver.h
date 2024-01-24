#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = 0);
signals:

public slots:
    void newConnection();
    void onResultReady();


private:
    QTcpServer *server;
};

#endif // TCPSERVER_H
