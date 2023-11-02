// Parser.h

#ifndef PARSER_H
#define PARSER_H

#include "common/action/action.h"
#include <QString>

class Parser {
public:
    virtual ~Parser() {}

    virtual Action* parse() = 0;
};

#endif // PARSER_H
