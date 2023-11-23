#include "searchparser.h"

#include <QString>

#include "common/action/action.h"
#include "common/action/searchaction.h"

SearchParser::SearchParser()
{

}

Action* SearchParser::parse()
{
    return new SearchAction("SEARCH");
}

