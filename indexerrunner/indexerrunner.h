#ifndef INDEXERRUNNER_H
#define INDEXERRUNNER_H

#include <QObject>
#include "../common/enum/enum.h"
#include "../common/dbadapter/dbadapter.h"

class IndexerRunner : public QObject
{
    Q_OBJECT
    public:
        IndexerRunner(DBAdapter &dbAdapter);
        void start();
        void stop();
        void pause();
        void resume();
        void notify();

    private:
        Enum::Status state;
        DBAdapter &dbAdapter;
};

#endif // INDEXERRUNNER_H
