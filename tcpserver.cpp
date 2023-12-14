#include "tcpserver.h"
#include "common/dbadapter/dbadapter.h"
#include "common/constants.h"
#include "commandhandler/commandhandler.h"

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

        //Log avec categorie
        //qCDebug(fooDebug) << "TEST ME";

        CommandHandler commandHandler;

        qDebug() << "Server started !";


    }
}

void TCPServer::newConnection() {
    //Recupere la socket créé
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello client !\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);

    // Lire les données du client et les afficher dans la console

    while (socket->waitForReadyRead())
    {
        QByteArray data = socket->readAll();
        qDebug() << "Received data from client:" << data;
        // Vérifier si le client a envoyé "exit"
        if (QString(data).trimmed().toLower() == "exit")
        {
            qDebug() << "Client requested exit. Closing connection.";
            socket->close();
            return;
        }
    }

    socket->close();
}
