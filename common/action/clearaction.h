#ifndef CLEARACTION_H
#define CLEARACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"

class ClearAction : public Action
{
public:
    ClearAction(QString table);
    virtual ~ClearAction();
    virtual void notify() override;
    virtual QVariant run(Sender* sender) override;
private:
    QString table;

};

#endif // CLEARACTION_H
