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
        Indexer(QStringList ext, Sender* sender);
        void run() override;
        void setStateThread(Enum::Status state);
    private:
        QStringList ext;
        Sender * sender;
        Enum::Status stateThread;
        bool shouldSkipFile(const QString &filePath, const QList<QString> &stringLists);
        bool shouldSkipFileByExtension(const QString &condition, const QString &fileExtension, const QList<QString> &extensions);

    signals:
        void resultReady(const QString &s);
        void stateChanged();
};

#endif // INDEXER_H
