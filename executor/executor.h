#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "common/action/action.h"
#include "common/dbadapter/dbadapter.h"
#include "sender.h"
class Executor
{
    DBAdapter db;
    public:
        Executor();
        void runAction(Action *action, Sender* sender);
};

#endif // EXECUTOR_H
