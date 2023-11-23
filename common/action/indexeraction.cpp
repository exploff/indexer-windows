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
IndexerAction::IndexerAction(QString name)
{
    qDebug() << "IndexerAction constructor" << __LINE__ << __FUNCTION__;
    this->name = name;
}


IndexerAction::~IndexerAction()
{
    qDebug() << "IndexerAction destructor" << __LINE__ << __FUNCTION__;
}

QString IndexerAction::getName() {
    return this->name;
}

void IndexerAction::run() {
    qDebug() << "IndexerAction" << __FUNCTION__ << __LINE__;

    qDebug() << "IndexerAction START";

    IndexerRunner* indexerRunner = IndexerRunner::getInstance();
    indexerRunner->start();

    /*
    //Dossier racine que l'on doit indéxer
    QString dirPath = "C:\\Users\\Julien\\Documents";

    //Extension que l'on indexe
    QStringList ext;
    ext.append("*");

    Indexer *indexerThread = new Indexer(dirPath, ext);
    //connect(indexerThread, &Indexer::resultReady, this, &MyObject::handleResults);
    //connect(indexerThread, &Indexer::finished, indexerThread, &QObject::deleteLater);
    indexerThread->start();

    // TODO : A SUPPRIMER
    indexerThread->wait();
*/

    qDebug() << "IndexerAction END";
}

void IndexerAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
