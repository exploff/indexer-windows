#include "dbadapter.h"
#include "../fileinfo/fileinfo.h"
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>

DBAdapter::DBAdapter(QString dbPath, QString dbFileName)
{
    //Setup the driver DB
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    if (this->db.lastError().isValid()) {
        qCritical() << "addDatabase" << this->db.lastError().text();
    }

    //create the application data folder
    QDir dir(dbPath);
    if (!dir.exists()) {
        dir.mkdir(dbPath);
        qDebug() << "mkdir" << dbPath;
    }

    //setup db filename
    QString dbFullPath = dbPath + dbFileName;
    qDebug() << "dbPath" << dbFullPath;
    this->db.setDatabaseName(dbFullPath);
}

DBAdapter::~DBAdapter()
{
    if(this->db.isOpen()) {
        this->db.close();
    }
}

int DBAdapter::open()
{
    if(!this->db.isOpen()) {
        if (!this->db.open()) {
            qCritical() << "unable to open db" << this->db.lastError().text() << this->db.databaseName();
            return -1;
        }
    }
    return 0;
}

void DBAdapter::close()
{
    if(this->db.isOpen()) {
        this->db.close();
    }
}

int DBAdapter::initTables()
{
    // create table
    QString tblFile = "CREATE TABLE IF NOT EXISTS files ("
                            "path STRING,"
                            "fileName STRING,"
                            "modifiedDate DATE,"
                            "createdDate DATE,"
                            "size BIGINT,"
                            "extension STRING,"
                            "type STRING,"
                            "PRIMARY KEY (path, fileName)"
                            ")";
    QSqlQuery query;
    query.exec(tblFile);
    if (query.lastError().isValid()) {
        qWarning() << "create table files" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table";
    query.finish();

    return 0;
}


void DBAdapter::save(FileInfo fileInfo)
{
    QSqlQuery query;
    query.prepare("INSERT INTO files(path, fileName, modifiedDate, createdDate, size, extension, type) "
                  "VALUES(:path, :fileName, :modifiedDate, :createdDate, :size, :extension, :type)");

    query.bindValue(":path", fileInfo.getPath());
    query.bindValue(":fileName", fileInfo.getFileName());
    query.bindValue(":modifiedDate", fileInfo.getModifiedDate().toString(Qt::ISODate)); // Convertit la date en format ISODate
    query.bindValue(":createdDate", fileInfo.getCreatedDate().toString(Qt::ISODate)); // Convertit la date en format ISODate
    query.bindValue(":size", fileInfo.getSize());
    query.bindValue(":extension", fileInfo.getExtension());
    query.bindValue(":type", static_cast<int>(fileInfo.getType())); // Convertit l'énumération en int

    if (!query.exec()) {
        qWarning() << "insert data into table files" << query.lastQuery() << query.lastError().text();
    }
    query.finish();
}

QList<FileInfo> DBAdapter::getAll()
{
    QList<FileInfo> results;

    QString sqlSelect = "SELECT * FROM files";

    QSqlQuery query;
    query.exec(sqlSelect);
    if (query.lastError().isValid()) {
        qWarning() << "select data from table files" << sqlSelect << query.lastError().text();
    }

    while(query.next()) {
        QString path = query.value("path").toString();
        QString fileName = query.value("fileName").toString();
        uint size = query.value("size").toUInt();
        QString extension = query.value("extension").toString();

        // Convertir la valeur de l'énumération en int puis en FileType
        int typeValue = query.value("type").toInt();
        Enum::FileType type = static_cast<Enum::FileType>(typeValue);

        // Convertir la date en QDateTime et extraire la date
        QDateTime modifiedDateTime = query.value("modifiedDate").toDateTime();
        QDate modifiedDate = modifiedDateTime.date();

        QDateTime createdDateTime = query.value("createdDate").toDateTime();
        QDate createdDate = createdDateTime.date();

        // Créer un objet FileInfo et l'ajouter à la liste des résultats
        FileInfo fileInfo(path, fileName, size, extension, type, modifiedDate, createdDate);
        results.append(fileInfo);
    }
    query.finish();

    return results;
}

void DBAdapter::dropTable(QString tableName) {
    qDebug() << "Drop table " + tableName;
    QString sqlDrop = "DROP TABLE " + tableName;
    QSqlQuery query;
    query.exec(sqlDrop);
    if (query.lastError().isValid()) {
        qWarning() << sqlDrop << query.lastError().text();
    }

}
