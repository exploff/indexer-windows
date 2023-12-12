#ifndef ADDACTION_H
#define ADDACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"

class AddAction: public Action
{
    public:
    AddAction(QString table,QList<QString> folderOrTypes);
        virtual ~AddAction();
        virtual void notify() override;
        virtual void run() override;
    private:
        QList<QString> folderOrTypes;
        QString table;

};

#endif // ADDACTION_H
