#include "searchoption.h"

SearchOption::SearchOption(): _sizes(new QList<SizeSpec>), _extensions(new QList<QString>), _types(new QList<QString>)
{
    this->_lastModifiedDate = DateSpec();
    this->_createdDate = DateSpec();
    this->_maxSize = SizeSpec();
    this->_minSize = SizeSpec();
}

SearchOption::~SearchOption()
{
    delete this->_sizes;
    delete this->_extensions;
    delete this->_types;
}

void SearchOption::setValue(QString value)
{
    this->_value = value;
}

QString SearchOption::getValue()
{
    return this->_value;
}


void SearchOption::setLastModifiedDate(DateSpec lastModifiedDate)
{
    this->_lastModifiedDate = lastModifiedDate;
    this->_hasLastModifiedDate = true;
}

DateSpec SearchOption::getLastModifiedDate()
{
    return this->_lastModifiedDate;
}

bool SearchOption::hasLastModifiedDate()
{
    return this->_hasLastModifiedDate;
}

void SearchOption::setCreatedDate(DateSpec createdDate)
{
    this->_createdDate = createdDate;
    this->_hasCreatedDate = true;
}

DateSpec SearchOption::getCreatedDate()
{
    return this->_createdDate;
}

bool SearchOption::hasCreatedDate()
{
    return this->_hasCreatedDate;
}

void SearchOption::setMaxSize(SizeSpec maxSize)
{
    this->_maxSize = maxSize;
    this->_hasMaxSize = true;
}

SizeSpec SearchOption::getMaxSize()
{
    return this->_maxSize;
}

bool SearchOption::hasMaxSize()
{
    return this->_hasMaxSize;
}

void SearchOption::setMinSize(SizeSpec minSize)
{
    this->_minSize = minSize;
    this->_hasMinSize = true;
}

SizeSpec SearchOption::getMinSize()
{
    return this->_minSize;
}

bool SearchOption::hasMinSize()
{
    return this->_hasMinSize;
}

void SearchOption::addSize(SizeSpec size)
{
    this->_sizes->append(size);
    this->_hasSizes = true;
}

QList<SizeSpec> SearchOption::getSizes()
{
    return *this->_sizes;
}

bool SearchOption::hasSizes()
{
    return this->_hasSizes;
}

void SearchOption::addExtension(QString extension)
{
    this->_extensions->append(extension);
    this->_hasExtensions = true;
}

QList<QString> SearchOption::getExtensions()
{
    return *this->_extensions;
}

bool SearchOption::hasExtensions()
{
    return this->_hasExtensions;
}

void SearchOption::addType(QString type)
{
    this->_types->append(type);
    this->_hasTypes = true;
}

QList<QString> SearchOption::getTypes()
{
    return *this->_types;
}

bool SearchOption::hasTypes()
{
    return this->_hasTypes;
}


