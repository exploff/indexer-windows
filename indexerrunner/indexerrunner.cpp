#include "indexerrunner.h"

#include "indexerrunner/indexer.h"

IndexerRunner* IndexerRunner::indexerRunner_ = nullptr;

IndexerRunner* IndexerRunner::getInstance(Sender* sender) {
    if (indexerRunner_ == nullptr) {
        indexerRunner_ = new IndexerRunner(sender);
    }
    return indexerRunner_;
}

IndexerRunner::IndexerRunner(Sender* sender)
{

    qDebug() << __FUNCTION__ << " create thread indexer ";
    QStringList ext;
    ext.append("*");

    Indexer *indexerThread = new Indexer(ext, sender);

    this->threadIndexer = indexerThread;
}



// A faire le destructeur pour arreter et detruire le thread

void IndexerRunner::start() {
    qDebug() << "Start";
    this->threadIndexer->setStateThread(Enum::Status::INDEXING);
    this->threadIndexer->start();
}

void IndexerRunner::pause() {
    this->threadIndexer->setStateThread(Enum::Status::PAUSED);
}

void IndexerRunner::stop() {
    this->threadIndexer->setStateThread(Enum::Status::STOPPED);
}

void IndexerRunner::resume() {
    this->threadIndexer->setStateThread(Enum::Status::INDEXING);
}

void IndexerRunner::notify() {
    qDebug() << "NOTIFY";
}
