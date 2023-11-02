#include "indexerrunner.h"

#include "../common/dbadapter/dbadapter.h"
#include "../common//fileinfo/fileinfo.h"
#include "../common/enum/enum.h"
#include <QDate>
#include <QDirIterator>
#include <QFileInfo>

IndexerRunner::IndexerRunner(DBAdapter &dbAdapter) : dbAdapter(dbAdapter)
{

}

void IndexerRunner::start() {
    qDebug() << "IndexerRunner START";

    //Dossier racine que l'on doit indéxer
    QString dirPath = "C:\\Users\\Julien\\Documents";

    //Extension que l'on indexe
    QStringList ext;
    ext.append("*.txt");

    //Extension type
    Enum::FileType type = Enum::FileType::TEXT;
    QDirIterator it(dirPath, ext, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        //qDebug() << it.next();
        QFileInfo fileMetadata = QFileInfo(it.next());
        //qDebug() << fileMetadata.fileName();

        FileInfo fileInfo(fileMetadata.absolutePath(), fileMetadata.fileName(), fileMetadata.size(),
                          fileMetadata.suffix(), type, fileMetadata.lastModified().date(), fileMetadata.birthTime().date());

        this->dbAdapter.save(fileInfo);
    }
    qDebug() << "IndexerRunner END";
}
