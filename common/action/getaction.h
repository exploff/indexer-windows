#ifndef GETACTION_H
#define GETACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"

class GetAction : public Action {
public:
    GetAction(QString name);
    virtual ~GetAction();
    virtual void notify() override;
    virtual void run() override;
private:
    QString name;

};

#endif // GETACTION_H
