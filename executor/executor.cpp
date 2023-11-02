#include "executor.h"
#include "qstandardpaths.h"

Executor::Executor()
{

}

void Executor::runAction(Action *action)
{
    action->run();
}
