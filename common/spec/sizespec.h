#ifndef SIZESPEC_H
#define SIZESPEC_H

#include <QString>

class SizeSpec
{
    public:
        SizeSpec();
        SizeSpec(double size, QString type);
        double getSize();
        QString getType();
    private:
        double _size;
        QString _type;
};

#endif // SIZESPEC_H
