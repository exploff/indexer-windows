#ifndef INDEXERACTION_H
#define INDEXERACTION_H

#include "action.h"
#include "../dbadapter/dbadapter.h"
#include <QObject>

class IndexerAction : public Action
{

    public:
        IndexerAction(Enum::Status state);
        virtual ~IndexerAction();
        virtual void notify() override;
        virtual QVariant run(Sender* sender) override;
    private:
        Enum::Status state;

};

#endif // INDEXERACTION_H
