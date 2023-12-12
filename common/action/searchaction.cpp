#include "searchaction.h"
#include <QDebug>
#include "../dbadapter/dbadapter.h"

SearchAction::SearchAction(SearchOption searchOption): _searchOption(searchOption)
{
    qDebug() << __LINE__ << __FUNCTION__;
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
