#ifndef SEARCHPARSER_H
#define SEARCHPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class SearchParser : public TParser<SearchParser> {
public:
    SearchParser();

    virtual Action* parse() override;
};

#endif // SEARCHPARSER_H
