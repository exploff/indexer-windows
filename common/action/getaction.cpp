#include "getaction.h"
#include <string>
#include <QDebug>
#include "../dbadapter/dbadapter.h"

GetAction::GetAction(std::string name)
{
    qDebug() << "GetAction constructor" << __LINE__ << __FUNCTION__;
    this->name = name;
}

GetAction::~GetAction() {
    qDebug() << "GetAction destructor" << __LINE__ << __FUNCTION__;
}

std::string GetAction::getName() {
    return this->name;
}

void GetAction::run() {
    qDebug() << __FUNCTION__ << __LINE__;

    // Déclencher status recherche start
    // Ouvrir une connexion à la DB
        // Rechercher la donnée
    // Renvoyer le resultat
    // Déclencher status recherche end
}

void GetAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
