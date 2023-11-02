#include "token.h"

Token::Token(const QString &value, const QString &type)
    : _value(value), _type(type)
{
}

QString Token::value() const
{
    return _value;
}

QString Token::type() const
{
    return _type;
}
