#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H


#include "commandhandler/parserfactory/parser/parser.h"
#include <QString>
#include <QList>
class ParserFactory
{
public:
    ParserFactory();
    Parser* build(QStringList line);
};

#endif // PARSERFACTORY_H
