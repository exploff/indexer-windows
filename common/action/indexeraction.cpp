#include "indexeraction.h"
#include <string>
#include <QDebug>
#include "../dbadapter/dbadapter.h"
#include "../../indexerrunner/indexerrunner.h"

/**
 * Classe qui va permettre d'executer la tache d'indexation des fichiers
 *
 * @brief IndexerAction::IndexerAction
 * @param name
 */
IndexerAction::IndexerAction(std::string name)
{
    qDebug() << "IndexerAction constructor" << __LINE__ << __FUNCTION__;
    this->name = name;
}


IndexerAction::~IndexerAction()
{
    qDebug() << "IndexerAction destructor" << __LINE__ << __FUNCTION__;
}

std::string IndexerAction::getName() {
    return this->name;
}

void IndexerAction::run(DBAdapter &dbAdapter) {
    qDebug() << "IndexerAction" << __FUNCTION__ << __LINE__;
    IndexerRunner indexerRunner(dbAdapter);
    indexerRunner.start();
}

void IndexerAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
