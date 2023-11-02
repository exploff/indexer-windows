#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "executor/executor.h"
#include "normalizer/normalizer.h"
#include "parserfactory/parserfactory.h"

class CommandHandler
{
    Normalizer normalizer;
    ParserFactory parserFactory;
    Executor executor;
    public:
        CommandHandler();
    public:
        void processCommand(QString command);
};

#endif // COMMANDHANDLER_H
