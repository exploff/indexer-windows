#include "executor.h"
#include "qstandardpaths.h"

Executor::Executor()
{

}

QVariant Executor::runAction(Action *action, Sender* sender)
{
    return action->run(sender);
}
