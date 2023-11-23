#include "clearparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/clearaction.h"

ClearParser::ClearParser()
{

}

Action* ClearParser::parse()
{
    return new ClearAction("CLEAR");
}
