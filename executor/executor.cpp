#include "executor.h"
#include "qstandardpaths.h"

Executor::Executor()
{
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dbFileName = "test.db";

    db = DBAdapter(appDataLocation, dbFileName);


}

void Executor::runAction(Action *action)
{ 
    action->run(db);
}
