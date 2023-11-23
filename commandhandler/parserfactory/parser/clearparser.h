#ifndef CLEARPARSER_H
#define CLEARPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class ClearParser : public TParser<ClearParser> {
public:
    ClearParser();

    virtual Action* parse() override;
};

#endif // CLEARPARSER_H
