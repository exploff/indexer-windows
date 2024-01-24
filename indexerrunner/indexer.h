#ifndef INDEXER_H
#define INDEXER_H

#include "../common/dbadapter/dbadapter.h"
#include <QThread>
#include <QStringList>
#include "sender.h"

class Indexer: public QThread
{
    Q_OBJECT

    public:
        Indexer(QString dirPath, QStringList ext, Sender* sender);
        void run() override;
        void setStateThread(Enum::Status state);
    private:
        QString dirPath;
        QStringList ext;
        Sender * sender;
        Enum::Status stateThread;
    signals:
        void resultReady(const QString &s);
        void stateChanged();
};

#endif // INDEXER_H
