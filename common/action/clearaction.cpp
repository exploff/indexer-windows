#include "clearaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"
#include "common/constants.h"

#include <QStandardPaths>

ClearAction::ClearAction(QString table): table(table)
{
}

ClearAction::~ClearAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

QVariant ClearAction::run(Sender* sender) {

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);
    dbAdapter.open();
    dbAdapter.clearTable(this->table);
    dbAdapter.close();
    sender->sendLogs("Clear DONE");
}

void ClearAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
