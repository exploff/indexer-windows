#ifndef TOKEN_H
#define TOKEN_H
#include "common/enum/enum.h"

#include <QString>

class Token
{
public:
    Token(const QString &value, const Enum::TokenTypes &type);

    QString value() const;
    Enum::TokenTypes type() const;

private:
    QString _value;
    Enum::TokenTypes _type;
};

#endif // TOKEN_H
