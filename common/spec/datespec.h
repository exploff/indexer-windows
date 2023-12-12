#ifndef DATESPEC_H
#define DATESPEC_H

#include <QDate>

class DateSpec
{
    public:
        DateSpec();
        DateSpec(QDate date);
        DateSpec(QDate minDate, QDate maxDate);
        QDate getDate();
        bool isBetween();
        QDate getMinDate();
        QDate getMaxDate();
    private:
        QDate _date;
        bool _between;
        QDate _minDate;
        QDate _maxDate;
};

#endif // DATESPEC_H
