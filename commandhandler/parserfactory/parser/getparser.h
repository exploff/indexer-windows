#ifndef GETPARSER_H
#define GETPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class GetParser : public TParser<GetParser> {
public:
    GetParser();

    virtual Action* parse() override;
};

#endif // GETPARSER_H
