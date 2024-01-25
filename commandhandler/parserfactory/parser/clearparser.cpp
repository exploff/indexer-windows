#include "clearparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/clearaction.h"

ClearParser::ClearParser()
{

}

Action* ClearParser::parse()
{
    QString tableName;
    QList<QString> folderOrTypes;
    for (Token* token :  this->getTokens()) {
        if (token->type() == Enum::TokenTypes::TABLE) {
            tableName = token->value();
        }
    }
    return new ClearAction(tableName);
}
