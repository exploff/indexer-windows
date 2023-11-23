#include "commandhandler.h"
#include "QDebug"
#include <QMetaEnum>
#include "common/enum/enum.h"
CommandHandler::CommandHandler()
{

}
void CommandHandler::processCommand(const QString input)
{

    this->normalizer.tokenize(input);
    for (Token* token : this->normalizer.tokens()) {
        qDebug() << "Value: " << token->value() << " => " << token->typeString();
    }

    Token* commandToken = this->normalizer.tokens()[0];
    if (commandToken->type() == Enum::TokenTypes::COMMANDE) {
        QString commandName = commandToken->value();

        Parser* parser = this->parserFactory.build(commandName, this->normalizer.tokens());
        Action* action = parser->parse();

        this->executor.runAction(action);
    }


    //this->executor.runAction(this->parserFactory.build(this->normalizer.tokens())->parse());
}
