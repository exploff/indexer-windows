#ifndef PUSHPARSER_H
#define PUSHPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class PushParser : public TParser<PushParser> {
public:
    PushParser();

    virtual Action* parse() override;
};


#endif // PUSHPARSER_H
