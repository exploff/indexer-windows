#include "parserfactory.h"
#include "commandhandler/parserfactory/parser/indexerparser.h"

ParserFactory::ParserFactory()
{

}
Parser* ParserFactory::build(QList<Token*> tokenList)
{
    Token* commandeToken = nullptr;
    for (Token* token : tokenList) {
        if (token->type() == "COMMANDE") {
            commandeToken = token;
            break;
        }
    }
    if(commandeToken){
        QString commande = commandeToken->value().toUpper();
        if (commande == "INDEXER") {
           return new IndexerParser();
        } else if (commande == "GET") {
           qDebug() << "Handle the 'GET' case";
           return new IndexerParser();
        } else if (commande == "ADD") {
           qDebug() << "Handle the 'ADD' case";
           return new IndexerParser();
        } else if (commande == "PUSH") {
            qDebug() << "Handle the 'PUSH' case";
           return new IndexerParser();
        } else if (commande == "CLEAR") {
            qDebug() << "Handle the 'CLEAR' case";
           return new IndexerParser();
        } else if (commande == "SEARCH") {
            qDebug() << "Handle the 'SEARCH' case";
           return new IndexerParser();
        }
    }else{
        qDebug() << "do not Handle commande";
        return new IndexerParser();
    }
}
