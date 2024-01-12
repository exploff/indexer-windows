#ifndef SEARCHPARSER_H
#define SEARCHPARSER_H

#include "commandhandler/parserfactory/parser/tparser.h"
#include "common/action/action.h"
#include <QString>
#include "common/spec/sizespec.h"
#include "searchfsm.h"
class SearchParser : public TParser<SearchParser> {
public:
    SearchParser();

    virtual Action* parse() override;
private:
    SizeSpec parseSizeString(const QString& sizeString);
    Token* nextToken();
    Token* currentToken();
    bool sendNextOption(Token * token);
    QString getTransitionName(QString value);
    QDate stringToDate(QString date);
    int currentTokenI = 0;

    Searchfsm *m_searchfsm;

};

#endif // SEARCHPARSER_H
