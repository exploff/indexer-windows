#include "searchaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

SearchAction::SearchAction(QString name)
{
    qDebug() << __LINE__ << __FUNCTION__;
    this->name = name;
}

SearchAction::~SearchAction() {
    qDebug() << __LINE__ << __FUNCTION__;
}

void SearchAction::run() {
    qDebug() << __FUNCTION__ << __LINE__;


}

void SearchAction::notify() {
    qDebug() << __FUNCTION__ << __LINE__;
}
