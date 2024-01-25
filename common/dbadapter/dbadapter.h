#ifndef DBADAPTER_H
#define DBADAPTER_H

#include "../fileinfo/fileinfo.h"
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "common/searchoption.h"

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
        void addAction(QString table,QList<QString> folderOrTypes);
        QList<QString> getAction(QString table);
        QList<FileInfo> searchAction(SearchOption searchOption);
        QString getRootFolderToBeIndexed();
        void updateRootFolderToBeIndexed(QString path);
    private:
        QString buildSizeCondition(const QString& condition, const QString& size, bool& isFirstCondition);
        QString buildWhereCondition(const QString& condition, const QString& value, bool& isFirstCondition);
        QString buildExtCondition(const QString& exts, bool& isFirstCondition);
        QString buildDateCondition(const QString& field, const QString& condition, const QString& date, bool& isFirstCondition);
        QString buildNameCondition(const QString& name, bool& isFirstCondition);
        QSqlDatabase db;
        QSqlQuery * query;
};

#endif // DBADAPTER_H
