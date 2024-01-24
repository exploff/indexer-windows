#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "executor/executor.h"
#include "normalizer/normalizer.h"
#include "parserfactory/parserfactory.h"
#include "receiver.h"
#include "sender.h"

class CommandHandler
{
    Normalizer normalizer;
    ParserFactory parserFactory;
    Executor executor;
    public:
        CommandHandler(Sender* sender);
    public:
        void processCommand(QString command);

    private:
        Sender* sender;
};

#endif // COMMANDHANDLER_H
