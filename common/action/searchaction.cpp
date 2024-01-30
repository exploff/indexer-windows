#include "searchaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

#include <QStandardPaths>
#include "common/constants.h"

SearchAction::SearchAction(SearchOption searchOption): _searchOption(searchOption)
{
    qDebug() << __LINE__ << __FUNCTION__;
}

SearchAction::~SearchAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

QVariant SearchAction::run(Sender* sender) {

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();

    QList<FileInfo> results = dbAdapter.searchAction(this->_searchOption);

    dbAdapter.close();

    qDebug() << __FUNCTION__ << __LINE__;
    qDebug() << "Resultats : " << results.length();
    if (results.length() > 50000) {
        sender->sendLogs(QString("Trop de resultats, veuillez affiner la recherche : %1").arg(results.length()));
        return QString("Trop de resultats, veuillez affiner la recherche : %1").arg(results.length());
    } else if (results.length() > 0) {
        qDebug() << results.first().getPath() << " / " << results.first().getFileName() << results.first().getCreatedDate() << results.first().getModifiedDate();
        sender->sendLogs(QString("Nombre de résultat : %1").arg(results.length()));

        sender->searchResult(results);

        QList<QString> returnResult;
        if (results.length()>0){
            for (int var = 0; var < results.length(); ++var) {
                returnResult.append(
                    results[var].getPath() + " / " + results[var].getFileName() + " " + results[var].getCreatedDate().toString() + " " + results[var].getModifiedDate().toString()
                    );
            }

        }
        return returnResult;
    } else {
        sender->sendLogs("Aucun résultat");
            return "Aucun résultat";
    }

}

void SearchAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
