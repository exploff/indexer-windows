#include "commandhandler/normalizer/normalizer.h"

#include "common/action/action.h"
#include "common/action/getaction.h"
#include "common/dbadapter/dbadapter.h"
#include "common/fileinfo/fileinfo.h"
#include "common/enum/enum.h"
#include "common/action/indexeraction.h"
#include "common/debug/debug.h"
#include "common/constants.h"
#include "tcpserver.h"
#include "mainwindow.h"

#include <iostream>
#include <string>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>
#include <QList>
#include <QDate>
#include <QDebug>
#include <QUrl>
#include <QLoggingCategory>

//Q_LOGGING_CATEGORY(fooDebug, "foo")


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initDebug();
    logAppInfo();

    MainWindow window;
    window.show();

/*
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();
    dbAdapter.initTables();
    dbAdapter.close();

    //Log avec categorie
    //qCDebug(fooDebug) << "TEST ME";

    CommandHandler commandHandler;

    //commandHandler.processCommand("INDEXER START");

    commandHandler.processCommand("GET SKIPPED_FILTERS");

    qDebug() << "\n\n";

    commandHandler.processCommand("ADD SKIPPED_FILTERS \"C:/document/txt.txt\"");

    qDebug() << "\n\n";

    commandHandler.processCommand("PUSH SKIPPED_FILTERS /home/documents \"C:/Documents/text.txt\" DONE");

    qDebug() << "\n\n";
*/
    /*commandHandler.processCommand("SEARCH \"testme please\" \
        LAST_MODIFIED:BETWEEN 2 days and 3 days \
        LAST_MODIFIED: 12/12/2020 \
        LAST_MODIFIED: SINCE LAST 45 DAYS \
        LAST_MODIFIED: SINCE LAST 45 MINUTES \
        LAST_MODIFIED: SINCE LAST 45 MONTHS \
        LAST_MODIFIED: SINCE LAST 45 HOURS \
        LAST_MODIFIED: 58 MONTHS AGO \
        CREATED:31/12/2020 \
        MAX_SIZE:10M \
        MIN_SIZE:BETWEEN 1M AND 10M \
        SIZE:BETWEEN 10M AND 20M \
        EXT:txt,doc,xlsx \
        TYPE:image OR text  \
        DONE");
*/
/*
    commandHandler.processCommand("SEARCH \"testme please\" \
        LAST_MODIFIED: 12/12/2020 \
        MAX_SIZE:10M \
        MIN_SIZE:10G \
        DONE");

    dbAdapter = DBAdapter(appDataLocation, dbFileName);
    dbAdapter.open();

    //Affichage des resultats indexer pour le test
    QList<FileInfo> results = dbAdapter.getAll();
    qDebug() << "Nombre de résultats : " << results.size();

    dbAdapter.close();
*/

    TCPServer tcpserver;
    return a.exec();
}

