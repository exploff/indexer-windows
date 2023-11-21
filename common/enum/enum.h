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
        enum class TokenTypes {
            COMMANDE,
            DATE,
            SIZE,
            DOUBLE,
            IDENTIFIER,
            NUMBER,
            STRING,
            TIME_EXPRESSION,
            TIME_UNIT,
            OPTIONS,
            EXTENSION,
            TYPE,
            TOKEN_UNKNOWN,
            FINAL
        };
        Q_ENUM(TokenTypes)

    Q_ENUM(FileType) // Enregistrer l'énumération pour qu'elle soit utilisable dans les signaux et slots
    Q_ENUM(Status)
};
#endif // ENUM_H
