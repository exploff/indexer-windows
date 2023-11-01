#ifndef FILEINFO_H
#define FILEINFO_H

#include "../../common/enum/enum.h"
#include <QDate>

class FileInfo
{
    public:
        FileInfo(uint id, QString path, QString fileName, uint size, QString extension, Enum::FileType type, QDate modifiedDate, QDate createdDate);

        uint getId() const;
        void setId(uint id);

        QString getPath() const;
        void setPath(const QString &value);

        QString getFileName() const;
        void setFileName(const QString &value);

        uint getSize() const;
        void setSize(uint value);

        QString getExtension() const;
        void setExtension(const QString &value);

        Enum::FileType getType() const;
        void setType(const Enum::FileType &value);

        QDate getModifiedDate() const;
        void setModifiedDate(const QDate &value);

        QDate getCreatedDate() const;
        void setCreatedDate(const QDate &value);
    private:
        uint id;
        QString path;
        QString fileName;
        uint size;
        QString extension;
        Enum::FileType type;
        QDate modifiedDate;
        QDate createdDate;

};

#endif // FILEINFO_H
