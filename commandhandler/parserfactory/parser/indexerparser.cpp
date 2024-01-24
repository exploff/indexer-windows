#include "indexerparser.h"
#include <QString>

#include "common/action/action.h"
#include "common/action/indexeraction.h"

IndexerParser::IndexerParser()
{

}

Action* IndexerParser::parse()
{

    Token* tokenAction = this->getTokens()[1];

    QString action = tokenAction->value();
    Enum::Status state = Enum::Status::INDEXING;

    if (action == "START")
    {
        state = Enum::Status::INDEXING;
    }
    else if (action == "STOP") {
        state = Enum::Status::STOPPED;
    }
    else if (action == "PAUSE") {
        state = Enum::Status::PAUSED;
    }
    else if (action == "RESUME") {
        state = Enum::Status::READY;
    }


    return new IndexerAction(state);
}

