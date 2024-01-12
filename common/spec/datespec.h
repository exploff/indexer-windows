#ifndef DATESPEC_H
#define DATESPEC_H

#include <QDate>

class DateSpec
{
    public:
        DateSpec();
        bool isBetween();
        QList<QDate>* getDates();
        void addDate(QDate date);
    private:
        bool _between;
        QList<QDate>* _dates;
};

#endif // DATESPEC_H
