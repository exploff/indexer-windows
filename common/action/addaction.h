#ifndef ADDACTION_H
#define ADDACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"

class AddAction: public Action
{
    public:
        AddAction(QString name);
        virtual ~AddAction();
        virtual QString getName() override;
        virtual void notify() override;
        virtual void run() override;
    private:
        QString name;

};

#endif // ADDACTION_H
