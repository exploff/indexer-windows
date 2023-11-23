#include "indexerrunner.h"

#include "indexerrunner/indexer.h"

IndexerRunner* IndexerRunner::indexerRunner_ = nullptr;

IndexerRunner* IndexerRunner::getInstance() {
    if (indexerRunner_ == nullptr) {
        indexerRunner_ = new IndexerRunner();
    }
    return indexerRunner_;
}

IndexerRunner::IndexerRunner()
{

    qDebug() << __FUNCTION__ << " create thread indexer ";
    QString dirPath = "C:\\Users\\Julien\\Documents";
    QStringList ext;
    ext.append("*");

    Indexer *indexerThread = new Indexer(dirPath, ext);

    this->threadIndexer = indexerThread;
}

// A faire le destructeur pour arreter et detruire le thread

void IndexerRunner::start() {
    qDebug() << "Start";
    this->threadIndexer->start();

    this->status = "START";

    //TODO : a supprimer
    this->threadIndexer->wait();
}

void IndexerRunner::pause() {
    qDebug() << "PAUSE";
}

void IndexerRunner::stop() {
    qDebug() << "STOP";
}

void IndexerRunner::resume() {
    qDebug() << "PAUSE";
}

void IndexerRunner::notify() {
    qDebug() << "NOTIFY";
}
