#ifndef ACTION_H
#define ACTION_H
#include <QObject>
#include "sender.h"
#include "../dbadapter/dbadapter.h"

class Action {
    public:
        virtual ~Action() = default;
        virtual void notify() = 0;
        virtual QVariant run(Sender* sender) = 0;
};

#endif // ACTION_H
