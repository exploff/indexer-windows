#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H


#include "commandhandler/parserfactory/parser/parser.h"
#include "common/token/token.h"
#include <QString>
#include <QList>
class ParserFactory
{
public:
    ParserFactory();
    Parser* build(QList<Token*> line);
};

#endif // PARSERFACTORY_H
