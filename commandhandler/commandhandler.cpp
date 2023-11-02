#include "commandhandler.h"
#include "QDebug"
CommandHandler::CommandHandler()
{

}
void CommandHandler::processCommand(const QString input)
{


    this->normalizer.stringToList(input);

    this->executor.runAction(this->parserFactory.build(this->normalizer.stringToList(input))->parse());
}
