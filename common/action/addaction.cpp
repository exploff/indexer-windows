#include "addaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"
#include "common/constants.h"
#include "qstandardpaths.h"

AddAction::AddAction(QString table,QList<QString> folderOrTypes)
{
    qDebug() << __LINE__ << __FUNCTION__;
    this->folderOrTypes = folderOrTypes;
    this->table = table;
}

AddAction::~AddAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

QVariant AddAction::run(Sender* sender) {

    if(!this->table.isNull() && !this->table.isEmpty() && this->folderOrTypes.size()>0){
        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QString dbFileName = Constants::DB_FILENAME;

        DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);
        dbAdapter.open();
        dbAdapter.addAction(this->table,this->folderOrTypes);
        dbAdapter.close();
        qDebug() << __FUNCTION__ << __LINE__;
        return "add correct";
    }else {
        qDebug() << "table name or folderOrTypes is empty";
        return "table name or folderOrTypes is empty";
    }
}

void AddAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
