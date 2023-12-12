#include "addaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

AddAction::AddAction(QString name)
{
    qDebug() << __LINE__ << __FUNCTION__;
    this->name = name;
}

AddAction::~AddAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

void AddAction::run() {
    qDebug() << __FUNCTION__ << __LINE__;
}

void AddAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
