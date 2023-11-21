#include "normalizer.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QObject>



Normalizer::Normalizer(){
    _dictionary["COMMANDE"] << "INDEXER" << "GET" << "ADD" << "PUSH" << "CLEAR" << "SEARCH";
}


QList<Token*> &Normalizer::tokens() {
    return _tokens;
}

void Normalizer::tokenize(QString source) {
    qDebug() << __FUNCTION__;
    resetTokens();
    if (source.isEmpty())
        return;
    source = source.trimmed();
    static QRegularExpression re_simpleSpaces("(\\n+)");
    static QRegularExpression re_addSpaceAround("([^a-zA-Z0-9._/]{1})");
    static QRegularExpression re_splitSpaces("[ \\t]");
    static QRegularExpression re_splitQuotes("\"");
    static QRegularExpression re_replaceComments("#.+\\n");
    source.replace(re_simpleSpaces, "\n");


    QString cmd = source;

    bool inside = false;

    QStringList tmpList = cmd.split(re_splitQuotes);
    // qDebug() << tmpList;

    foreach (QString s, tmpList) {
        if (s.isEmpty())
            continue;
        if (inside) {          // If 's' is inside quotes ...
            addTokenString(s); // ... get the whole string
        } else {               // If 's' is outside quotes ...

            s.replace(re_addSpaceAround, " \\1 ");
            s = s.trimmed();
            // removes comments
            s.replace(re_replaceComments, "");
            // qDebug() << __FUNCTION__ << __LINE__ << s;
            addToken(s.split(re_splitSpaces, Qt::SkipEmptyParts)); // ... get the splitted string
        }
        inside = !inside;
    }
}



QString Normalizer::getType(QString token) {
    // qDebug() << __FUNCTION__ << token << _dictionary.keys();

    foreach (QString category, _dictionary.keys()) {

        if (_dictionary[category].contains(token.toUpper())) {
            return category;
        }
    };

    static QRegularExpression re;


    re.setPattern("\\d{2}/\\d{2}/?");
    if (re.match(token).hasMatch()) {
        return "DATE";
    }

    re.setPattern("\\d+[KMG]+");
    if (re.match(token).hasMatch()) {
        return "SIZE";
    }

    re.setPattern("\\d+\\.\\d+");
    if (re.match(token).hasMatch()) {
        return "DOUBLE";
    }

    re.setPattern("^[a-zA-Z_]{1}[0-9a-zA-Z_]+");
    if (re.match(token).hasMatch()) {
        return "IDENTIFIER";
    }
    re.setPattern("^\\d+$");
    if (re.match(token).hasMatch()) {
        return "NUMBER";
    }

    return "TOKEN_UNKNOWN";
}

void Normalizer::addToken(QString token) {
    static QString lasttype;
    // dont add multiple final tokens
    QString type = getType(token);
    if (lasttype == "FINAL" && type == "FINAL") {
        lasttype = type;
        return;
    }

    Token *tokenObj = new Token(token, type);
    _tokens.append(tokenObj);
    lasttype = type;
}

void Normalizer::addTokenString(QString token) {
    Token *tokenObj = new Token(token.trimmed(), "STRING");
    _tokens.append(tokenObj);
}

void Normalizer::addToken(QStringList tokens) {
    foreach (auto token, tokens) { addToken(token); }
}

void Normalizer::resetTokens() {
    _tokens.clear();
}



