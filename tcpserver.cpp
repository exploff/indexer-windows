#include "tcpserver.h"
#include "commandhandler/commandhandler.h"
#include "common/dbadapter/dbadapter.h"
#include "common/constants.h"

#include <QStandardPaths>
#include <QDir>

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    //Connection d'un user ça emet un signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server couldn't start";
    } else {
        qDebug() << "Set up server";

        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QString dbFileName = Constants::DB_FILENAME;

        DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

        dbAdapter.open();
        dbAdapter.initTables();
        dbAdapter.close();

        qDebug() << "Server started !";
    }
}

void TCPServer::newConnection() {
    //Recupere la socket créé
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello client !");
    socket->flush();

    /*socket->waitForBytesWritten(3000);*/

    // Lire les données du client et les afficher dans la console

    while (socket->waitForReadyRead())
    {
        QByteArray receivedData = socket->readAll();
        qDebug() << "Received data from client:" << receivedData;
        // Vérifier si le client a envoyé "exit"
        if (QString(receivedData).trimmed().toLower() == "exit")
        {
            qDebug() << "Client requested exit. Closing connection.";
            socket->close();
            return;
        } else {

            Sender sender;
            CommandHandler commandHandler(&sender);
            const QVariant &data = commandHandler.processCommand(receivedData);

            QByteArray serializedData;
            QDataStream stream(&serializedData, QIODevice::WriteOnly);
            stream << data;

            // Perform some action based on the received data
            qDebug() << "Received data:" << data;

            // Send a response back through the connected socket
            if (socket->state() == QAbstractSocket::ConnectedState)
            {
                socket->write(serializedData);
                socket->flush();
            }
        }
    }

    socket->close();
}

void TCPServer::onResultReady()
{
    qDebug() << "Resultat fini";
}
