#ifndef SEARCHOPTION_H
#define SEARCHOPTION_H

#include "spec/datespec.h"
#include "spec/sizespec.h"
#include <QString>

class SearchOption
{
    public:
        SearchOption();
        ~SearchOption();

        void setValue(QString value);
        QString getValue();

        void setLastModifiedDate(DateSpec lastModifiedDate);
        DateSpec getLastModifiedDate();
        bool hasLastModifiedDate();

        void setCreatedDate(DateSpec createdDate);
        DateSpec getCreatedDate();
        bool hasCreatedDate();

        void setMaxSize(SizeSpec maxSize);
        SizeSpec getMaxSize();
        bool hasMaxSize();

        void setMinSize(SizeSpec minSize);
        SizeSpec getMinSize();
        bool hasMinSize();

        void addSize(SizeSpec size);
        QList<SizeSpec> getSizes();
        bool hasSizes();

        void addExtension(QString extension);
        QList<QString> getExtensions();
        bool hasExtensions();

        void addType(QString type);
        QList<QString> getTypes();
        bool hasTypes();

    private:
        QString _value;

        DateSpec _lastModifiedDate;
        DateSpec _createdDate;
        SizeSpec _maxSize;
        SizeSpec _minSize;
        QList<SizeSpec> *_sizes;
        QList<QString> *_extensions;
        QList<QString> *_types;

        bool _hasLastModifiedDate = false;
        bool _hasCreatedDate = false;
        bool _hasMaxSize = false;
        bool _hasMinSize = false;
        bool _hasSizes = false;
        bool _hasExtensions = false;
        bool _hasTypes = false;
};

#endif // SEARCHOPTION_H
