#ifndef INDEXER_H
#define INDEXER_H

#include "../common/dbadapter/dbadapter.h"
#include <QThread>
#include <QStringList>

class Indexer: public QThread
{
    Q_OBJECT

    public:
        Indexer(QString dirPath, QStringList ext);
        void run() override;
    private:
        QString dirPath;
        QStringList ext;
    signals:
        void resultReady(const QString &s);
};

#endif // INDEXER_H
