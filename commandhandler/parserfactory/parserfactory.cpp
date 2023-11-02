#include "parserfactory.h"
#include "commandhandler/parserfactory/parser/indexerparser.h"

ParserFactory::ParserFactory()
{

}
Parser* ParserFactory::build(QStringList line)
{
    return new IndexerParser();
}
