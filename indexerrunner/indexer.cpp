#include "indexer.h"

#include "../common/dbadapter/dbadapter.h"
#include "../common/enum/enum.h"
#include "../common/constants.h"
#include "../common/fileinfo/fileinfo.h"

#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>


Indexer::Indexer(QString dirPath, QStringList ext) : dirPath(dirPath), ext(ext)
{

}

void Indexer::run() {
    //Créer l'instance de la DB
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();

    qDebug() << "Execution du thread INDEXER";

    dbAdapter.clearTable("files");

    //Extension type
    Enum::FileType type = Enum::FileType::TEXT;
    QDirIterator it(dirPath, ext, QDir::Files, QDirIterator::Subdirectories);
    QFileInfo fileMetadata = QFileInfo();

    FileInfo fileInfo;

    dbAdapter.prepareSaveTransaction();
    int i = 0;
    while (it.hasNext()) {
        i++;
        if (i % Constants::LIMIT_PACK_FILES_INDEX == 0) {
            dbAdapter.commitTransaction();
            dbAdapter.prepareSaveTransaction();
        }

        //qDebug() << it.next();
        fileMetadata.setFile(it.next());
        //qDebug() << fileMetadata.fileName();

        fileInfo.setPath(fileMetadata.absolutePath());
        fileInfo.setFileName(fileMetadata.fileName());
        fileInfo.setSize(fileMetadata.size());
        fileInfo.setExtension(fileMetadata.suffix());
        fileInfo.setType(type);
        fileInfo.setCreatedDate(fileMetadata.birthTime().date());
        fileInfo.setModifiedDate(fileMetadata.lastModified().date());

        dbAdapter.save(fileInfo);

    }

    dbAdapter.commitTransaction();

    qDebug() << "Fin execution du thread INDEXER";

    dbAdapter.close();

    emit resultReady("Thread Indexer DONE");
}
