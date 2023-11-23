// Parser.h

#ifndef PARSER_H
#define PARSER_H

#include "common/action/action.h"
#include "common/token/token.h"
#include <QString>
#include "common/enum/enum.h"

class Parser {


    public:
        virtual ~Parser() {}
        virtual Action* parse() = 0;
        virtual void setTokens(QList<Token*> tokens);
        virtual void setCommand(QString command);

    private:
        QList<Token*> _tokens;
        QString _command;

};

typedef Parser *(*CreateParserFn)();

#endif // PARSER_H
