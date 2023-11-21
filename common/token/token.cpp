#include "token.h"

Token::Token(const QString &value, const Enum::TokenTypes &type)
    : _value(value), _type(type)
{
}

QString Token::value() const
{
    return _value;
}

Enum::TokenTypes Token::type() const
{
    return _type;
}
