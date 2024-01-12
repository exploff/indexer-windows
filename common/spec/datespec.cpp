#include "datespec.h"

DateSpec::DateSpec(): _dates(new QList<QDate>)
{

}

bool DateSpec::isBetween()
{
    return this->_between;
}

QList<QDate>* DateSpec::getDates()
{
    return this->_dates;
}

void DateSpec::addDate(QDate date)
{
    this->_dates->append(date);
    this->_between = this->_dates->length() > 1;
}

