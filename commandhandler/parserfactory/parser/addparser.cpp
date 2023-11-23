#include "addparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/addaction.h"

AddParser::AddParser()
{

}

Action* AddParser::parse()
{
    return new AddAction("ADD");
}
