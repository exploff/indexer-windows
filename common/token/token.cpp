#include "token.h"

#include <QMetaEnum>

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

QString Token::typeString() const {

    QMetaObject metaObject = Enum::staticMetaObject;
    int enumIndex = metaObject.indexOfEnumerator("TokenTypes");
    QMetaEnum metaEnum = metaObject.enumerator(enumIndex);

    int enumValue = static_cast<int>(this->_type);
    QString enumString = metaEnum.valueToKey(enumValue);
    return enumString;
}
