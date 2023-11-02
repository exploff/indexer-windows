#ifndef SERVER_H
#define SERVER_H


#include "commandhandler/commandhandler.h"
class Server
{
    CommandHandler commandHandler;
    public:
        Server();
        ~Server();
};
#endif // SERVER_H
