#ifndef TPARSER_H
#define TPARSER_H

#include "commandhandler/parserfactory/parser/parser.h"

template <class T>
class TParser : public Parser {
public:
    static Parser *create() {
        return new T;
    }
};


#endif // TPARSER_H
