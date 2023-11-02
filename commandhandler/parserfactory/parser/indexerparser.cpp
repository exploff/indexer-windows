#include "indexerparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/indexeraction.h"

IndexerParser::IndexerParser()
{

}
Action* IndexerParser::parse()
{
    return  new IndexerAction("test");
}

