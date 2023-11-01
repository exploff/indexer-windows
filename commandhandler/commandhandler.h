#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "normalizer/normalizer.h"
#include "parserfactory/parserfactory.h"

class CommandHandler
{
    Normalizer normalizer;
    ParserFactory parserFactory;
    public:
        CommandHandler();
    public:
        void processCommand(QString command);
};

#endif // COMMANDHANDLER_H
