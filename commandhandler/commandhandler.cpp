#include "commandhandler.h"
#include "QDebug"
#include <QMetaEnum>
#include "common/enum/enum.h"
#include "common/exception/parserexception.h"

CommandHandler::CommandHandler(Sender* sender): sender(sender)
{

}
QVariant CommandHandler::processCommand(const QString input)
{

    this->normalizer.tokenize(input);
    for (Token* token : this->normalizer.tokens()) {
        qDebug() << "Value: " << token->value() << " => " << token->typeString();
    }

    Token* commandToken = this->normalizer.tokens()[0];
    if (commandToken->type() == Enum::TokenTypes::COMMANDE) {
        QString commandName = commandToken->value();

        try {
            Parser* parser = this->parserFactory.build(commandName, this->normalizer.tokens());
            Action* action = parser->parse();

            return this->executor.runAction(action, sender);
        } catch(const ParserException &e) {
            qDebug() << "Erreur parse" << e.what();
            this->sender->sendLogs(QString(e.what()));
            return "command not found";
        }
    }


    //this->executor.runAction(this->parserFactory.build(this->normalizer.tokens())->parse());
}
