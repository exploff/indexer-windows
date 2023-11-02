#ifndef DBADAPTER_H
#define DBADAPTER_H

#include "../fileinfo/fileinfo.h"
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>

class DBAdapter
{
    public:
        DBAdapter();
        DBAdapter(QString dbPath, QString dbFileName);
        ~DBAdapter();
        int open();
        void close();
        int initTables();
        void save(FileInfo fileInfo);
        void clearTable(QString tableName);
        void prepareSaveTransaction();
        void commitTransaction();
        void dropTable(QString tableName);
        QList<FileInfo> getAll();
    private:
        QSqlDatabase db;
        QSqlQuery * query;
};

#endif // DBADAPTER_H
