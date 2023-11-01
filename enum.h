#ifndef ENUM_H
#define ENUM_H

#include <QObject>

class Enum : public QObject
{
    Q_OBJECT

    public:
        enum class FileType {
            IMAGE,
            EXECUTABLE,
            TEXT,
            MEDIA,
            COMPRESSED
        };
        enum class Status {
            INDEXING,
            READY,
            STOPPED,
            PAUSED,
            QUERYING,
            RESULTS_AVAILABLE
        };

    Q_ENUM(FileType) // Enregistrer l'énumération pour qu'elle soit utilisable dans les signaux et slots
    Q_ENUM(Status)
};
#endif // ENUM_H
