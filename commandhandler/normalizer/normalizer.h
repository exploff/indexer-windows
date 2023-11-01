#ifndef NORMALIZER_H
#define NORMALIZER_H
#include <QString>

class Normalizer
{
public:
    Normalizer();
public:
    QString normalize(const QString& command);
};

#endif // NORMALIZER_H
