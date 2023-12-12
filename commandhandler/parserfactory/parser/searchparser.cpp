#include "searchparser.h"

#include <QString>

#include "common/action/action.h"
#include "common/action/searchaction.h"

SearchParser::SearchParser()
{

}

Action* SearchParser::parse()
{
    SearchOption* searchOption = new SearchOption();


    QList<Token*> tokens = this->getTokens();



    return new SearchAction(*searchOption);
}

