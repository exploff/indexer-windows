#ifndef SEARCHACTION_H
#define SEARCHACTION_H


#include "action.h"
#include "../dbadapter/dbadapter.h"
#include "../searchoption.h"
#include <QObject>

class SearchAction : public Action
{

public:
    SearchAction(SearchOption searchOption);
    virtual ~SearchAction();
    virtual void notify() override;
    virtual void run(Sender* sender) override;
private:
    SearchOption _searchOption;

};

#endif // SEARCHACTION_H
