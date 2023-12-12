#include "addparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/addaction.h"

AddParser::AddParser()
{

}

Action* AddParser::parse()
{
    QString tableName;
    QList<QString> folderOrTypes;
    for (Token* token :  this->getTokens()) {
        if (token->type() == Enum::TokenTypes::TABLE) {
            tableName = token->value();
        }
        if(tableName == "FILTERS" || tableName == "SKIPPED_FILTERS"){
            if (token->type() == Enum::TokenTypes::EXTENSION) {
                folderOrTypes.append(token->value());
            }
        }else{
            if (token->type() == Enum::TokenTypes::STRING) {
                folderOrTypes.append(token->value());
            }
        }
    }
    return new AddAction(tableName,folderOrTypes);
}
