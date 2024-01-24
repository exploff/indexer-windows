#include <QDebug>
#include <QObject>
#include "indexeraction.h"
#include "indexerrunner/indexerrunner.h"
#include "indexerrunner/indexer.h"

/**
 * Classe qui va permettre d'executer la tache d'indexation des fichiers
 *
 * @brief IndexerAction::IndexerAction
 * @param name
 */
IndexerAction::IndexerAction(Enum::Status state): state(state)
{
}


IndexerAction::~IndexerAction()
{
    qDebug() << "IndexerAction destructor" << __LINE__ << __FUNCTION__;
}

void IndexerAction::run(Sender* sender) {
    qDebug() << "IndexerAction" << __FUNCTION__ << __LINE__;

    qDebug() << "IndexerAction START";

    IndexerRunner* indexerRunner = IndexerRunner::getInstance(sender);
    if (this->state == Enum::Status::INDEXING)
    {
        indexerRunner->start();
    }
    else if(this->state == Enum::Status::STOPPED)
    {
        indexerRunner->stop();
    }
    else if (this->state == Enum::Status::PAUSED)
    {
        indexerRunner->pause();
    }
    else if (this->state == Enum::Status::READY)
    {
        indexerRunner->resume();
    }
}

void IndexerAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
