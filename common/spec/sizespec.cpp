#include "sizespec.h"

SizeSpec::SizeSpec()
{

}

SizeSpec::SizeSpec(double size, QString type): _size(size), _type(type)
{

}

double SizeSpec::getSize()
{
    return this->_size;
}

QString SizeSpec::getType()
{
    return this->_type;
}

