#ifndef CLEARACTION_H
#define CLEARACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"


class ClearAction : public Action
{
public:
    ClearAction(QString name);
    virtual ~ClearAction();
    virtual void notify() override;
    virtual void run() override;
private:
    QString name;
};

#endif // CLEARACTION_H
