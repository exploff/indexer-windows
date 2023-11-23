#include "parserfactory.h"
#include "commandhandler/parserfactory/parser/indexerparser.h"
#include "commandhandler/parserfactory/parser/addparser.h"
#include "commandhandler/parserfactory/parser/getparser.h"
#include "commandhandler/parserfactory/parser/pushparser.h"
#include "commandhandler/parserfactory/parser/clearparser.h"
#include "commandhandler/parserfactory/parser/searchparser.h"

ParserFactory::ParserFactory()
{
    Register("INDEXER", &IndexerParser::create);
    Register("ADD", &AddParser::create);
    Register("GET", &GetParser::create);
    Register("PUSH", &PushParser::create);
    Register("CLEAR", &ClearParser::create);
    Register("SEARCH", &SearchParser::create);

}

ParserFactory::~ParserFactory() {

    foreach(auto parser, parserList) {
        delete parser;
    }
}

void ParserFactory::Register(QString command, CreateParserFn fn)
{
    qDebug() << __FUNCTION__ << command << fn;
    m_factoryMap[command] = fn;
}


Parser* ParserFactory::build(QString command, QList<Token*> tokenList)
{
    qDebug() << __FUNCTION__ << "START BUILD PARSER";

    CreateParserFn fn = m_factoryMap[command];
    if (fn == nullptr) {
        qDebug() << "NULL POINTER - COMMAND EXISTE PAS";
        //@Todo : declencher exception
    }

    qDebug() << "#############";
    qDebug() << "CREATE PARSER";
    Parser* parser = fn();

    parser->setTokens(tokenList);
    parser->setCommand(command);

    qDebug() << "#############";

    parserList.append(parser);

    return parser;
}
