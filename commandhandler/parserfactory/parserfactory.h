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
        ~ParserFactory();
        Parser* build(QString command, QList<Token*> line);
        void Register(QString command, CreateParserFn fn);

    private:
        QMap<QString, CreateParserFn> m_factoryMap;
        QList<Parser *>               parserList;

};

#endif // PARSERFACTORY_H
