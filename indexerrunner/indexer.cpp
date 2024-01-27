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


Indexer::Indexer(QStringList ext, Sender* sender) : ext(ext), sender(sender)
{

}

void Indexer::setStateThread(Enum::Status state)
{
    stateThread = state;
    emit stateChanged();
}

void Indexer::run() {


    //Créer l'instance de la DB
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = Constants::DB_FILENAME;

    DBAdapter dbAdapter = DBAdapter(appDataLocation, dbFileName);

    dbAdapter.open();

    qDebug() << "Execution du thread INDEXER";
    sender->startIndexing();
    sender->sendLogs("DEBUT INDEXATION");

    dbAdapter.clearTable("files");

    QList<QString> blacklistsFolders = dbAdapter.getAction(Constants::BLACKLIST_DB);
    QList<QString> skippedExtensions = dbAdapter.getAction(Constants::SKIPPED_FILTERS_DB);
    QList<QString> filterExtensions = dbAdapter.getAction(Constants::FILTERS_DB);

    QString rootFolderToBeIndexed = dbAdapter.getRootFolderToBeIndexed();
    if (rootFolderToBeIndexed == "") {
        rootFolderToBeIndexed = "C:/";
    }

    //Extension type
    Enum::FileType type = Enum::FileType::TEXT;
    QDirIterator it(rootFolderToBeIndexed, ext, QDir::Files, QDirIterator::Subdirectories);
    QFileInfo fileMetadata = QFileInfo();

    FileInfo fileInfo;

    dbAdapter.prepareSaveTransaction();
    int i = 0;
    int nbFichierSkipped = 0;

    while (it.hasNext()) {

        if (this->stateThread == Enum::Status::PAUSED) {
            sender->sendLogs("PAUSE INDEXING");
            sender->pauseIndexing();
            QEventLoop loop;
            connect(this, &Indexer::stateChanged, &loop, &QEventLoop::quit);
            loop.exec();
            sender->resumeIndexing();
            sender->sendLogs("RESUME INDEXING");
        }

        if (this->stateThread == Enum::Status::STOPPED) {
            sender->sendLogs("STOP INDEXING");
            break;
        }

        fileMetadata.setFile(it.next());

        //qDebug() << shouldSkipFile(fileMetadata.absolutePath(), blacklistsFolders) ;
        //qDebug() <<             shouldSkipFileByExtension(Constants::SKIPPED_FILTERS_DB, fileMetadata.suffix(), skippedExtensions);
        //qDebug() <<    shouldSkipFileByExtension(Constants::FILTERS_DB, fileMetadata.suffix(), filterExtensions);
        // Vérifier si le dossier parent est dans la liste de la blacklist
        if (shouldSkipFile(fileMetadata.absolutePath(), blacklistsFolders) ||
            shouldSkipFileByExtension(Constants::SKIPPED_FILTERS_DB, fileMetadata.suffix(), skippedExtensions) ||
            shouldSkipFileByExtension(Constants::FILTERS_DB, fileMetadata.suffix(), filterExtensions)) {
            nbFichierSkipped++;
            continue;
        }


        i++;
        if (i % Constants::LIMIT_PACK_FILES_INDEX == 0) {
            sender->sendLogs(QString("Nombre de fichier actuellement indexer : %1").arg(i));
            dbAdapter.commitTransaction();
            dbAdapter.prepareSaveTransaction();
        }

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
    sender->sendLogs(QString("Nombre total de fichier indexer : %1").arg(i));
    sender->sendLogs(QString("Nombre total de fichier skip : %1").arg(nbFichierSkipped));

    sender->sendLogs("FIN INDEXATION");
    sender->endIndexing();

    dbAdapter.close();

    emit resultReady("Thread Indexer DONE");
}

bool Indexer::shouldSkipFile(const QString &filePath, const QList<QString> &folderList) {
    for (const QString &folder : folderList) {
        if (filePath.startsWith(folder, Qt::CaseInsensitive)) {
            return true;
        }
    }

    return false;
}

bool Indexer::shouldSkipFileByExtension(const QString &condition, const QString &fileExtension, const QList<QString> &extensions) {

    if (condition == Constants::SKIPPED_FILTERS_DB && extensions.contains(fileExtension)) {
        return true;
    } else if (condition == Constants::FILTERS_DB && extensions.length() > 0 && !extensions.contains(fileExtension)) {
        return true;
    }

    return false;
}
