
#include "dbadapter.h"
#include "../fileinfo/fileinfo.h"
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>
#include <memory>

DBAdapter::DBAdapter()
{

}
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
        QString connectionName = this->db.connectionName();
        QSqlDatabase::database(connectionName).close();
        QSqlDatabase::removeDatabase(connectionName);

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
    QString whiteList = "CREATE TABLE IF NOT EXISTS WHITELIST ("
                        "path STRING,"
                        "PRIMARY KEY (path)"
                        ")";
    QString blackList = "CREATE TABLE IF NOT EXISTS BLACKLIST ("
                        "path STRING,"
                        "PRIMARY KEY (path)"
                        ")";
    QString filters = "CREATE TABLE IF NOT EXISTS FILTERS ("
                      "extension STRING,"
                      "PRIMARY KEY (extension)"
                      ")";
    QString skippedFilters = "CREATE TABLE IF NOT EXISTS SKIPPED_FILTERS ("
                             "extension STRING,"
                             "PRIMARY KEY (extension)"
                             ")";

    QSqlQuery query;
    query.exec(tblFile);
    if (query.lastError().isValid()) {
        qWarning() << "create table files" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table files";
    query.finish();

    query.exec(whiteList);
    if (query.lastError().isValid()) {
        qWarning() << "create table whiteList" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table whiteList";
    query.finish();

    query.exec(blackList);
    if (query.lastError().isValid()) {
        qWarning() << "create table blackList" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table blackList";
    query.finish();

    query.exec(filters);
    if (query.lastError().isValid()) {
        qWarning() << "create table filters" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table filters";
    query.finish();

    query.exec(skippedFilters);
    if (query.lastError().isValid()) {
        qWarning() << "create table skippedFilters" << query.lastError().text();
        return -1;
    }
    qDebug() << __FUNCTION__ << __LINE__ << "Init table skippedFilters";
    query.finish();

    return 0;
}


void DBAdapter::prepareSaveTransaction() {
    qDebug() << "Start transaction save file";
    this->query = new QSqlQuery();

    this->query->exec("pragma temp_store = memory");
    this->query->exec("PRAGMA synchronous = OFF");
    this->query->exec("pragma mmap_size = 30000000000");
    this->query->exec("PRAGMA journal_mode = MEMORY");

    this->db.transaction();

    this->query->prepare("INSERT INTO files(path, fileName, modifiedDate, createdDate, size, extension, type) "
                  "VALUES(:path, :fileName, :modifiedDate, :createdDate, :size, :extension, :type)");

}

void DBAdapter::commitTransaction() {
    qDebug() << "Commit transaction";
    this->db.commit();
    delete this->query;
}


void DBAdapter::save(FileInfo fileInfo)
{

    this->query->bindValue(":path", fileInfo.getPath());
    this->query->bindValue(":fileName", fileInfo.getFileName());
    this->query->bindValue(":modifiedDate", fileInfo.getModifiedDate().toString(Qt::ISODate)); // Convertit la date en format ISODate
    this->query->bindValue(":createdDate", fileInfo.getCreatedDate().toString(Qt::ISODate)); // Convertit la date en format ISODate
    this->query->bindValue(":size", fileInfo.getSize());
    this->query->bindValue(":extension", fileInfo.getExtension());
    this->query->bindValue(":type", static_cast<int>(fileInfo.getType())); // Convertit l'énumération en int

    if (!this->query->exec()) {
        qWarning() << "insert data into table files" << this->query->lastQuery() << this->query->lastError().text();
    }
    this->query->finish();
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

void DBAdapter::clearTable(QString tableName) {
    qDebug() << "Clear table " + tableName;
    QString sqlClear = "DELETE FROM " + tableName;
    QSqlQuery query;
    query.exec(sqlClear);
    if (query.lastError().isValid()) {
        qWarning() << sqlClear << query.lastError().text();
    }
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

void DBAdapter::addAction(QString table, QList<QString> folderOrTypes) {
    qDebug() << "add to table " + table;
    QSqlQuery query;

    for (const QString &value : folderOrTypes) {

        QString sqlInsert ="INSERT INTO " + table + " VALUES (\"" + value + "\")";

        query.exec(sqlInsert);
        if (query.lastError().isValid()) {
            qWarning() << sqlInsert << query.lastError().text();
        }

        query.finish();
    }
}

QList<QString> DBAdapter::getAction(QString table) {
    qDebug() << "add to table " + table;
    QSqlQuery query;
    QList<QString> resultList;

    QString sqlGet ="select * from  " + table;

    query.exec(sqlGet);
    if (query.lastError().isValid()) {
        qWarning() << sqlGet << query.lastError().text();
        return resultList;
    }
    while (query.next()) {
        // Assuming there is a single column in the result set, adjust as needed
        QString columnValue = query.value(0).toString();
        resultList.append(columnValue);
    }
    query.finish();

    for (QString string  : resultList) {
        qDebug() << "Table: " << table << " Value:" << string;
    }
    return resultList;
}
