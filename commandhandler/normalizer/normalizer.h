#ifndef NORMALIZER_H
#define NORMALIZER_H
#include "common/token/token.h"
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QObject>

class Normalizer
{

    public:
        Normalizer();
        QList<Token*> &tokens() ;
        void resetTokens();
        void tokenize(const QString source);
        void resetToken();

    private:

        void addToken(QString token);
        void addTokenString(QString token);
        void addToken(QStringList tokens);
        QString getType(QString token);

        QList<Token*> _tokens;
        QMap<QString, QStringList> _dictionary;
 };
#endif // NORMALIZER_H
