#include "commandhandler/normalizer/normalizer.h"
#include "server.h"

#include "common/action/action.h"
#include "common/action/getaction.h"
#include "common/dbadapter/dbadapter.h"
#include "common/fileinfo/fileinfo.h"
#include "common/enum/enum.h"
#include "common/action/indexeraction.h"
#include "common/debug/debug.h"
#include "common/constants.h"

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
    QCoreApplication a(argc, argv);
    initDebug();
    logAppInfo();

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();
    dbAdapter.initTables();
    dbAdapter.close();

    //Log avec categorie
    //qCDebug(fooDebug) << "TEST ME";

    CommandHandler commandHandler;

    commandHandler.processCommand("INDEXER");

    /*
    QStringList l;
    l << "helo"
      << "réda"
      << "multi word"
      << "\\plok\\"
      << "\"plok is my name\\"
      << "SEARCH \"testme please\" LAST_MODIFIED:2 days CREATED:31/12/2020 MAX_SIZE:1M EXT:txt,doc,xlsx TYPE:image OR "
         "text"

        ;
    qDebug() << "          ";
    qDebug() << "          ";
    Normalizer normalizer;
    for (const auto &i : qAsConst(l)) {
        qDebug() << normalizer.stringToList(i);
//        qDebug() << QUrl::toPercentEncoding(i);
    }
*/

    dbAdapter = DBAdapter(appDataLocation, dbFileName);
    dbAdapter.open();

    //Affichage des resultats indexer pour le test
    QList<FileInfo> results = dbAdapter.getAll();
    qDebug() << "Nombre de résultats : " << results.size();

    dbAdapter.close();

    /*
    //setup the driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (db.lastError().isValid()) {
        qCritical() << "addDatabase" << db.lastError().text();
        return -1;
    }

    //getting system app data folder
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);


    //create the application data folder
    QDir dir(appDataLocation);
    if (!dir.exists()) {
        dir.mkdir(appDataLocation);
        qDebug() << "mkdir" << appDataLocation;
    }

    //setup db filename and open it
    QString dbPath = appDataLocation+"/testdb.db";
    qDebug() << "dbPath" << dbPath;
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qCritical() << "unable to open db" << db.lastError().text() << dbPath;
        return -1;
    }

    // create table
    QString tblFileCreate = "CREATE TABLE IF NOT EXISTS files ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "filePath STRING,"
                            "fileSize BIGINT,"
                            "fileMTime BIGINT,"
                            "fileLastCheck BIGINT"
                            ")";
    QSqlQuery query;
    query.exec(tblFileCreate);
    if (query.lastError().isValid()) {
        qWarning() << "create table files" << query.lastError().text();
    }


    // insert data
    const int INSERTS_COUNT = 10;
    for (int i = 0; i < INSERTS_COUNT; i++) {
        QString sqlInsert = "INSERT INTO files(filePath, fileSize, fileMTime, fileLastCheck) " +
                            QString("VALUES('file%1', %1, %1, %1)").arg(i);

        query.exec(sqlInsert);
        if (query.lastError().isValid()) {
            qWarning() << "insert data into table files" << sqlInsert << query.lastError().text();
        }
    }

    // query the data
    QString sqlSelect = "SELECT * from files";
    query.exec(sqlSelect);
    if (query.lastError().isValid()) {
        qWarning() << "select data from table files" << sqlSelect << query.lastError().text();
    }

    while(query.next()) {
        uint id = query.value("id").toUInt();
        QString filePath = query.value("filePath").toString();
        uint fileSize = query.value("fileSize").toUInt();
        uint fileMTime = query.value("fileMTime").toUInt();
        uint fileLastCheck = query.value("fileLastCheck").toUInt();

        qDebug() << id << filePath << fileSize << fileMTime << fileLastCheck;
    }

    // update data

    QString sqlUpdate = "UPDATE files SET filePath = 'toto' WHERE id = 1";
    query.exec(sqlUpdate);
    if (query.lastError().isValid()) {
        qWarning() << "update data from table files" << sqlUpdate << query.lastError().text();
    }

    // check the update
    sqlSelect = "SELECT * from files WHERE id = 1";
    query.exec(sqlSelect);
    if (query.lastError().isValid()) {
        qWarning() << "select data from table files" << sqlSelect << query.lastError().text();
    }

    while(query.next()) {
        QString filePath = query.value("filePath").toString();
        if (filePath == "toto") {
            qDebug() << "UPDATE SUCCESS";
        } else {
            qDebug() << "UPDATE FAILS";
        }
    }

    // drop the table
    QString sqlDrop = "DROP TABLE files";
    query.exec(sqlDrop);
    if (query.lastError().isValid()) {
        qWarning() << "select data from table files" << sqlDrop << query.lastError().text();
    }

    */

    return 0;
}

