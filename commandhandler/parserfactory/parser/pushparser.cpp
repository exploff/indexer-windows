#include "pushparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/pushaction.h"

PushParser::PushParser()
{

}

Action* PushParser::parse()
{
    return new PushAction("PUSH");
}

