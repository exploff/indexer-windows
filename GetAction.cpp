#include "getaction.h"
#include <string>
#include <QDebug>
#include "dbadapter.h"

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

void GetAction::run(DBAdapter &dbAdapter) {
    qDebug() << __FUNCTION__ << __LINE__;
}

void GetAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
