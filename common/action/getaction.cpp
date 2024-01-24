#include "getaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"
#include "common/constants.h"
#include "qstandardpaths.h"

GetAction::GetAction(QString table)
{
    qDebug() << "GetAction constructor" << __LINE__ << __FUNCTION__;
    this->_table = table;
}

GetAction::~GetAction() {
    qDebug() << "GetAction destructor" << __LINE__ << __FUNCTION__;
}

void GetAction::run(Sender* sender) {
    if(!this->_table.isNull() && !this->_table.isEmpty()){
        qDebug() << __FUNCTION__ << __LINE__;

        // Déclencher status recherche start
        // Ouvrir une connexion à la DB
        // Rechercher la donnée
        // Renvoyer le resultat
        // Déclencher status recherche end

        QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QString dbFileName = Constants::DB_FILENAME;

        DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

        dbAdapter.open();
        dbAdapter.getAction(this->_table);
        dbAdapter.close();
    }else{
        qDebug() << "table name is empty";
    }

}

void GetAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
