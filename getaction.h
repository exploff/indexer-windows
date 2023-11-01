#ifndef GETACTION_H
#define GETACTION_H

#include "action.h"
#include <string>
#include "dbadapter.h"

class GetAction : public Action {
    public:
        GetAction(std::string name);
        virtual ~GetAction();
        virtual std::string getName() override;
        virtual void notify() override;
        virtual void run(DBAdapter &dbAdapter) override;
    private:
        std::string name;

};

#endif // GETACTION_H
