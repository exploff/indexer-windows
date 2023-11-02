#ifndef NORMALIZER_H
#define NORMALIZER_H
#include <QString>
#include <QStringList>
#include <QRegularExpression>

class Normalizer
{
public:
    Normalizer();
public:
    QStringList stringToList(QString line);
};

#endif // NORMALIZER_H
