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

    //commandHandler.processCommand("INDEXER STOP");

    //commandHandler.processCommand("GET SKIPPED_FILTERS");

    //commandHandler.processCommand("ADD SKIPPED_FILTERS \"C:\/"");

    //Faire à la fin
    //Gérer les C:/ d:/ et les /home/documents etc et gérer les sauts de lignes
    //commandHandler.processCommand("PUSH SKIPPED_FILTERS /home/documents DONE");

    //Gérer les dates avec days etc
    //Gérer les extensions
    //Gérer les types
    commandHandler.processCommand("SEARCH \"testme please\" \
        LAST_MODIFIED:BETWEEN 2 days and 3 days \
        CREATED:31/12/2020 \
        MAX_SIZE:10M \
        MIN_SIZE:BETWEEN 1M AND 10M \
        SIZE:BETWEEN 10M AND 20M \
        EXT:txt,doc,xlsx \
        TYPE:image OR text  \
        DONE");

    dbAdapter = DBAdapter(appDataLocation, dbFileName);
    dbAdapter.open();

    //Affichage des resultats indexer pour le test
    QList<FileInfo> results = dbAdapter.getAll();
    qDebug() << "Nombre de résultats : " << results.size();

    dbAdapter.close();
}

