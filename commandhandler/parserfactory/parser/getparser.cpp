#include "getparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/getaction.h"

GetParser::GetParser()
{

}

Action* GetParser::parse()
{
    QString tableName;
    for (Token* token :  this->getTokens()) {
        if (token->type() == Enum::TokenTypes::TABLE) {
            tableName = token->value();
        }
    }
    return new GetAction(tableName);
}
