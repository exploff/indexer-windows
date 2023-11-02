#include "indexerrunner.h"

#include "../common/dbadapter/dbadapter.h"
#include "../common//fileinfo/fileinfo.h"
#include "../common/enum/enum.h"
#include "../common/constants.h"
#include <QDate>
#include <QDirIterator>
#include <QFileInfo>

IndexerRunner::IndexerRunner(DBAdapter &dbAdapter) : dbAdapter(dbAdapter)
{

}

void IndexerRunner::start() {
    qDebug() << "IndexerRunner START";

    //Dossier racine que l'on doit indéxer
    QString dirPath = "C:\\";

    //Extension que l'on indexe
    QStringList ext;
    ext.append("*");

    //Extension type
    Enum::FileType type = Enum::FileType::TEXT;
    QDirIterator it(dirPath, ext, QDir::Files, QDirIterator::Subdirectories);
    QFileInfo fileMetadata = QFileInfo();

    this->dbAdapter.prepareSaveTransaction();
    int i = 0;
    while (it.hasNext()) {
        i++;
        if (i % Constants::LIMIT_PACK_FILES_INDEX == 0) {
            this->dbAdapter.commitTransaction();
            this->dbAdapter.prepareSaveTransaction();
        }

        //qDebug() << it.next();
        fileMetadata.setFile(it.next());
        //qDebug() << fileMetadata.fileName();

        FileInfo fileInfo(fileMetadata.absolutePath(), fileMetadata.fileName(), fileMetadata.size(),
                          fileMetadata.suffix(), type, fileMetadata.lastModified().date(), fileMetadata.birthTime().date());

        this->dbAdapter.save(fileInfo);

    }

    this->dbAdapter.commitTransaction();

    qDebug() << "IndexerRunner END";
}
