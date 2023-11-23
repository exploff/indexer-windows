#include "getparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/getaction.h"

GetParser::GetParser()
{

}

Action* GetParser::parse()
{
    return new GetAction("GET");
}
