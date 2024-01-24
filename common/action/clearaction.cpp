#include "clearaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

ClearAction::ClearAction(QString name)
{
    qDebug() << __LINE__ << __FUNCTION__;
    this->name = name;
}

ClearAction::~ClearAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

void ClearAction::run(Sender* sender) {
    qDebug() << __FUNCTION__ << __LINE__;
}

void ClearAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
