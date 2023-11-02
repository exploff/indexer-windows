#ifndef ACTION_H
#define ACTION_H
#include <string>
#include <QObject>

#include "../dbadapter/dbadapter.h"

class Action {
    public:
        virtual ~Action() = default;
        virtual std::string getName() = 0;
        virtual void notify() = 0;
        virtual void run() = 0;
};

#endif // ACTION_H
