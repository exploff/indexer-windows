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

void SearchAction::run(Sender* sender) {

    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();

    QList<FileInfo> results = dbAdapter.searchAction(this->_searchOption);

    dbAdapter.close();

    qDebug() << __FUNCTION__ << __LINE__;
    qDebug() << "Resultats : " << results.length();
    if (results.length() > 0) {
        qDebug() << results.first().getPath() << " / " << results.first().getFileName() << results.first().getCreatedDate() << results.first().getModifiedDate();
        sender->searchResult(results);
    }

}

void SearchAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
