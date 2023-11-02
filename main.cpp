#include "commandhandler/normalizer/normalizer.h"
#include "server.h"

#include "common/action/action.h"
#include "common/action/getaction.h"
#include "common/dbadapter/dbadapter.h"
#include "common/fileinfo/fileinfo.h"
#include "common/enum/enum.h"
#include "common/action/indexeraction.h"
#include "common/debug/debug.h"

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

Q_LOGGING_CATEGORY(fooDebug, "foo")

void runAction(Action * obj, DBAdapter &dbAdapter) {
    obj->run(dbAdapter);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    initDebug();
    logAppInfo();

    qDebug() << "Hello world";

    qCDebug(fooDebug) << "TEST ME";

    CommandHandler commandHandler;

    commandHandler.processCommand("GET WHITELIST");

}

