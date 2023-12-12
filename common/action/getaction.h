#ifndef GETACTION_H
#define GETACTION_H

#include "action.h"

class GetAction : public Action {
public:
    GetAction(QString table);
    virtual ~GetAction();
    virtual void notify() override;
    virtual void run() override;
private:
    QString _table;

};

#endif // GETACTION_H
