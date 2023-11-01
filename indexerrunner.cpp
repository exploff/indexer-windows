#include "indexerrunner.h"

#include "dbadapter.h"
#include "fileinfo.h"
#include "enum.h"
#include <QDate>

IndexerRunner::IndexerRunner(DBAdapter &dbAdapter) : dbAdapter(dbAdapter)
{

}

void IndexerRunner::start() {
    qDebug() << "IndexerRunner START" << __FUNCTION__ << __LINE__;

    FileInfo fileInfo1(0, "/path/to/files", "fichier.txt", 124, "txt", Enum::FileType::TEXT, QDate(2022, 1, 1), QDate(2022, 1, 1));
    this->dbAdapter.save(fileInfo1);
    FileInfo fileInfo2(0, "/path/to/files", "toto.txt", 124, "txt", Enum::FileType::TEXT, QDate(2022, 1, 1), QDate(2022, 1, 1));
    this->dbAdapter.save(fileInfo2);
    FileInfo fileInfo3(0, "/path/to/files", "test.txt", 124, "txt", Enum::FileType::TEXT, QDate(2022, 1, 1), QDate(2022, 1, 1));
    this->dbAdapter.save(fileInfo3);

    qDebug() << "IndexerRunner END";
}
