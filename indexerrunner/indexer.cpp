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


Indexer::Indexer(QString dirPath, QStringList ext, Sender* sender) : dirPath(dirPath), ext(ext), sender(sender)
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

    //Extension type
    Enum::FileType type = Enum::FileType::TEXT;
    QDirIterator it(dirPath, ext, QDir::Files, QDirIterator::Subdirectories);
    QFileInfo fileMetadata = QFileInfo();

    FileInfo fileInfo;

    dbAdapter.prepareSaveTransaction();
    int i = 0;
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

        i++;
        if (i % Constants::LIMIT_PACK_FILES_INDEX == 0) {
            sender->sendLogs(QString("Nombre de fichier actuellement indexer : %1").arg(i));
            dbAdapter.commitTransaction();
            dbAdapter.prepareSaveTransaction();
        }

        //Voir pour optimiser : it.fileInfo(); et ne plus utiliser fileInfo, directement passer le QFileInfo

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
    sender->sendLogs(QString("Nombre total de fichier indexer : %1").arg(i));

    sender->sendLogs("FIN INDEXATION");
    sender->endIndexing();

    dbAdapter.close();

    emit resultReady("Thread Indexer DONE");
}
