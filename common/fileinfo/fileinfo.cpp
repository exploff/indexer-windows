#include "fileinfo.h"
#include "../../common/enum/enum.h"
#include <QDate>

// Constructeur sans paramètre
FileInfo::FileInfo() {

}

// Constructeur prenant tous les paramètres
FileInfo::FileInfo(QString path, QString fileName, uint size, QString extension, Enum::FileType type, QDate modifiedDate, QDate createdDate)
    : path(path), fileName(fileName), size(size), extension(extension), type(type), modifiedDate(modifiedDate), createdDate(createdDate)
{
}

// Getter et setter pour 'path'
QString FileInfo::getPath() const
{
    return path;
}

void FileInfo::setPath(const QString &value)
{
    path = value;
}

// Getter et setter pour 'fileName'
QString FileInfo::getFileName() const
{
    return fileName;
}

void FileInfo::setFileName(const QString &value)
{
    fileName = value;
}

// Getter et setter pour 'size'
uint FileInfo::getSize() const
{
    return size;
}

void FileInfo::setSize(uint value)
{
    size = value;
}

// Getter et setter pour 'extension'
QString FileInfo::getExtension() const
{
    return extension;
}

void FileInfo::setExtension(const QString &value)
{
    extension = value;
}

// Getter et setter pour 'type'
Enum::FileType FileInfo::getType() const
{
    return type;
}

void FileInfo::setType(const Enum::FileType &value)
{
    type = value;
}

// Getter et setter pour 'modifiedDate'
QDate FileInfo::getModifiedDate() const
{
    return modifiedDate;
}

void FileInfo::setModifiedDate(const QDate &value)
{
    modifiedDate = value;
}

// Getter et setter pour 'createdDate'
QDate FileInfo::getCreatedDate() const
{
    return createdDate;
}

void FileInfo::setCreatedDate(const QDate &value)
{
    createdDate = value;
}

