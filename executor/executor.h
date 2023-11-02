#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "common/action/action.h"
#include "common/dbadapter/dbadapter.h"

class Executor
{
    DBAdapter db;
    public:
        Executor();
        void runAction(Action *action);
};

#endif // EXECUTOR_H
