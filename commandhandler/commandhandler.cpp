#include "commandhandler.h"
#include "QDebug"
#include <QMetaEnum>
CommandHandler::CommandHandler()
{

}
void CommandHandler::processCommand(const QString input)
{

    this->normalizer.tokenize(input);
    for (Token* token : this->normalizer.tokens()) {
        qDebug() << "Value: " << token->value();
        qDebug() << "Type: " << token->type();
    }

    Parser* indexerParser = this->parserFactory.build(this->normalizer.tokens());
    Action* indexerAction = indexerParser->parse();

    //this->executor.runAction(indexerAction);


    //this->executor.runAction(this->parserFactory.build(this->normalizer.tokens())->parse());
}
