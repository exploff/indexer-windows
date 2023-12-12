#include "parser.h"
#include <QDebug>

void Parser::setTokens(const QList<Token *>& tokens) {
    qDebug() << __FUNCTION__ << tokens.size();
    _tokens = tokens;
}

void Parser::setCommand(QString command) {
    qDebug() << __FUNCTION__ << command;
    _command = command;
}

QList<Token*> Parser::getTokens()
{
    return this->_tokens;
}
