#ifndef INDEXERACTION_H
#define INDEXERACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"
#include <QObject>

class IndexerAction : public Action
{

    public:
        IndexerAction(QString name);
        virtual ~IndexerAction();
        virtual void notify() override;
        virtual void run() override;
    private:
        QString name;

};

#endif // INDEXERACTION_H
