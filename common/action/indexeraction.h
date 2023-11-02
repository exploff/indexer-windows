#ifndef INDEXERACTION_H
#define INDEXERACTION_H

#include "action.h"
#include <string>
#include "../dbadapter/dbadapter.h"
#include <QObject>

class IndexerAction : public Action
{

    public:
        IndexerAction(std::string name);
        virtual ~IndexerAction();
        virtual std::string getName() override;
        virtual void notify() override;
        virtual void run() override;
    private:
        std::string name;

};

#endif // INDEXERACTION_H
