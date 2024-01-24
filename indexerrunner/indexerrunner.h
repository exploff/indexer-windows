#ifndef INDEXERRUNNER_H
#define INDEXERRUNNER_H

#include <QString>
#include "indexerrunner/indexer.h"
#include "sender.h"
class IndexerRunner
{
    public:
        void start();
        void stop();
        void pause();
        void resume();
        void notify();
        static IndexerRunner* getInstance(Sender* sender);
        static IndexerRunner* indexerRunner_;

    private:
        IndexerRunner();
        IndexerRunner(Sender* sender);
        IndexerRunner(const IndexerRunner&) = delete;
        IndexerRunner& operator=(const IndexerRunner&) = delete;
        ~IndexerRunner();

        Indexer * threadIndexer;
        Sender * sender;


};

#endif // INDEXERRUNNER_H
