#ifndef PUSHACTION_H
#define PUSHACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"

class PushAction : public Action
{
    public:
        PushAction(QString name);
        virtual ~PushAction();
        virtual void notify() override;
        virtual void run() override;
    private:
        QString name;

};

#endif // PUSHACTION_H
