// Parser.h

#ifndef INDEXERPARSER_H
#define INDEXERPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>

class IndexerParser : public TParser<IndexerParser> {
public:
    IndexerParser();

    virtual Action* parse() override;

};

#endif // INDEXERPARSER_H
