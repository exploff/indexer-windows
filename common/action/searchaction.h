#ifndef SEARCHACTION_H
#define SEARCHACTION_H


#include "action.h"
#include "../dbadapter/dbadapter.h"
#include <QObject>

class SearchAction : public Action
{
public:
    SearchAction(QString name);
    virtual ~SearchAction();
    virtual QString getName() override;
    virtual void notify() override;
    virtual void run() override;
private:
    QString name;

};

#endif // SEARCHACTION_H
