#ifndef DBADAPTER_H
#define DBADAPTER_H

#include "fileinfo.h"
#include <QList>
#include <QSqlDatabase>

class DBAdapter
{
    public:
        DBAdapter(QString dbPath, QString dbFileName);
        ~DBAdapter();
        int open();
        void close();
        int initTables();
        void save(FileInfo fileInfo);
        void dropTable(QString tableName);
        QList<FileInfo> getAll();
    private:
        QSqlDatabase db;
};

#endif // DBADAPTER_H
