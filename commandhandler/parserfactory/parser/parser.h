// Parser.h

#ifndef PARSER_H
#define PARSER_H

#include <QString>

class Parser {
public:
    virtual ~Parser() {}

    virtual bool parse(const QString& input) = 0;
};

#endif // PARSER_H
