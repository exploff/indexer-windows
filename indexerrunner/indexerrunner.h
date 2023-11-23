#ifndef INDEXERRUNNER_H
#define INDEXERRUNNER_H

#include <QString>
#include "indexerrunner/indexer.h"

class IndexerRunner
{
    public:
        void start();
        void stop();
        void pause();
        void resume();
        void notify();
        static IndexerRunner* getInstance();
        static IndexerRunner* indexerRunner_;

    private:
        IndexerRunner();
        IndexerRunner(const IndexerRunner&) = delete;
        IndexerRunner& operator=(const IndexerRunner&) = delete;
        ~IndexerRunner();

        QString status;
        Indexer * threadIndexer;


};

#endif // INDEXERRUNNER_H
