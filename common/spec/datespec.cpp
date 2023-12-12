#include "datespec.h"

DateSpec::DateSpec()
{

}
DateSpec::DateSpec(QDate date): _date(date)
{
    this->_between = false;
}

DateSpec::DateSpec(QDate minDate, QDate maxDate): _minDate(minDate), _maxDate(maxDate)
{
    this->_between = true;
}

bool DateSpec::isBetween()
{
    return this->_between;
}

QDate DateSpec::getDate()
{
    return this->_date;
}

QDate DateSpec::getMinDate()
{
    return this->_minDate;
}

QDate DateSpec::getMaxDate()
{
    return this->_maxDate;
}
