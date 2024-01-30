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

QVariant PushAction::run(Sender* sender) {
    qDebug() << __FUNCTION__ << __LINE__;
    return "push action";
}

void PushAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}

