#ifndef ADDPARSER_H
#define ADDPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class AddParser : public TParser<AddParser> {
public:
    AddParser();

    virtual Action* parse() override;
};

#endif // ADDPARSER_H
