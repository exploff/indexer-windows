#include "pushaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

PushAction::PushAction(QString name)
{
    qDebug() << __LINE__ << __FUNCTION__;
    this->name = name;
}

PushAction::~PushAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

void PushAction::run(Sender* sender) {
    qDebug() << __FUNCTION__ << __LINE__;
}

void PushAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}

