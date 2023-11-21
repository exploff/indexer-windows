#include "normalizer.h"
#include "common/enum/enum.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QObject>
#include <QMimeDatabase>


Normalizer::Normalizer(){

    //QMimeDatabase mimeDatabase;
    //_mimeDatabase = mimeDatabase;

    _dictionary[Enum::TokenTypes::COMMANDE] << "INDEXER" << "GET" << "ADD" << "PUSH" << "CLEAR" << "SEARCH";
    _dictionary[Enum::TokenTypes::COLON] << ":";
    _dictionary[Enum::TokenTypes::COMMA] << ",";
    _dictionary[Enum::TokenTypes::OPTIONS] << "LAST_MODIFIED" << "CREATED" << "MAX_SIZE" << "MIN_SIZE" << "SIZE" << "EXT" << "TYPE";
    _dictionary[Enum::TokenTypes::OPERATOR] << "BETWEEN" << "OR" << "AND" << "SINCE" << "LAST" << "AGO";
    _dictionary[Enum::TokenTypes::TIME_UNIT] << "MINUTES" << "DAYS" << "HOURS" << "MONTHS" << "YEAR";
    _dictionary[Enum::TokenTypes::TYPE] << "image" << "text" << "exec";

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



Enum::TokenTypes Normalizer::getType(QString token) {
    // qDebug() << __FUNCTION__ << token << _dictionary.keys();

    foreach (Enum::TokenTypes category, _dictionary.keys()) {

        if (_dictionary[category].contains(token.toUpper())) {
            return category;
        }
    };

    static QRegularExpression re;
    re.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    re.setPattern("\\d{2}/\\d{2}/?");
    if (re.match(token).hasMatch()) {
        return Enum::TokenTypes::DATE;
    }

    re.setPattern("\\d+[KMG]+");
    if (re.match(token).hasMatch()) {
        return Enum::TokenTypes::SIZE;
    }

    re.setPattern("\\d+\\.\\d+");
    if (re.match(token).hasMatch()) {
        return Enum::TokenTypes::DOUBLE;
    }

    if (isExtension(token)) {
        return Enum::TokenTypes::EXTENSION;
    }

    re.setPattern("^[a-zA-Z_]{1}[0-9a-zA-Z_]+");
    if (re.match(token).hasMatch()) {
        return Enum::TokenTypes::IDENTIFIER;
    }

    re.setPattern("^\\d+$");
    if (re.match(token).hasMatch()) {
        return Enum::TokenTypes::NUMBER;
    }

    return Enum::TokenTypes::TOKEN_UNKNOWN;
}

bool Normalizer::isExtension(QString token) {
    QMimeType mimeType = _mimeDatabase.mimeTypeForFile("file." + token);

    if (mimeType.isValid()) {
        int i = _tokens.size() -1;
        //Get last token options and check if is OPTIONS EXT
        while (i >= 0) {
            Token* t = _tokens[i];
            if (t->type() == Enum::TokenTypes::OPTIONS) {
                return t->value() == "EXT";
            }
            i = i - 1;
        }
    }
    return false;
}

void Normalizer::addToken(QString token) {
    static Enum::TokenTypes lasttype;
    // dont add multiple final tokens
    Enum::TokenTypes type = getType(token);
    if (lasttype == Enum::TokenTypes::FINAL && type == Enum::TokenTypes::FINAL) {
        lasttype = type;
        return;
    }

    // Check if the current token is a time unit
    if (type == Enum::TokenTypes::TIME_UNIT) {
        // Combine with the previous token to form a time expression
        if (!_tokens.isEmpty()) {
            Token* previousToken = _tokens.last();
            QString combinedToken = previousToken->value() + " " + token;
            Token* combinedTokenObj = new Token(combinedToken, Enum::TokenTypes::TIME_EXPRESSION);
            _tokens.removeLast();  // Remove the previous token
            _tokens.append(combinedTokenObj);  // Add the combined time expression
            lasttype = Enum::TokenTypes::TIME_EXPRESSION;  // Update lasttype
            return;
        }
    }




    Token *tokenObj = new Token(token, type);
    _tokens.append(tokenObj);
    lasttype = type;
}

void Normalizer::addTokenString(QString token) {
    Token *tokenObj = new Token(token.trimmed(), Enum::TokenTypes::STRING);
    _tokens.append(tokenObj);
}

void Normalizer::addToken(QStringList tokens) {
    foreach (auto token, tokens) { addToken(token); }
}

void Normalizer::resetTokens() {
    _tokens.clear();
}



