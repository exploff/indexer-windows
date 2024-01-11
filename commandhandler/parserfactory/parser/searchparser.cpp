#include "searchparser.h"

#include <QString>

#include "common/action/action.h"
#include "common/action/searchaction.h"

#include "searchfsm.h"

#include <QApplication>

SearchParser::SearchParser()
{

}

Action* SearchParser::parse()
{
    SearchOption* searchOption = new SearchOption();

    QList<Token*> tokens = this->getTokens();

    this->m_searchfsm = new Searchfsm();

    bool setMinSize = false;
    bool setMaxSize = false;
    bool setSize = false;

    //Utiliser les tokens
    //nextToken

    this->m_searchfsm->connectToState("SIZE_AND", [this, searchOption, &setSize]() {
        qDebug() << "1 > TRAITEMENT DE SIZE AND";
        setSize = true;
    });

    this->m_searchfsm->connectToState("OPTION_SIZE", [this, searchOption, &setSize]() {
        qDebug() << "1 > SIZE";
        setSize = true;
    });


    this->m_searchfsm->connectToState("OPTION_MIN_SIZE", [this, searchOption, &setMinSize]() {
        setMinSize = true;
    });

    this->m_searchfsm->connectToState("OPTION_MAX_SIZE", [this, searchOption, &setMaxSize]() {
        setMaxSize = true;
    });

    this->m_searchfsm->connectToState("SIZE_UNIT", [this, searchOption, &setMaxSize, &setMinSize, &setSize]() {
        SizeSpec sizeSpec = this->parseSizeString(this->currentToken()->value());
        if (setMinSize) {
            searchOption->setMinSize(sizeSpec);
            setMinSize = false;
        } else if(setMaxSize) {
            searchOption->setMaxSize(sizeSpec);
            setMaxSize = false;
        } else if (setSize) {
            searchOption->addSize(sizeSpec);
            setSize = false;
        }
    });

    this->m_searchfsm->init();
    this->m_searchfsm->start();

    for (Token* token : tokens) {

        qDebug() << "Traitement token " << token->value();
        QString transitionName = this->getTransitionName(token->typeString());
        qDebug() << "Transition to " << transitionName;

        if (sendNextOption(token)) {
            this->m_searchfsm->submitEvent("is_next_option");
            QApplication::processEvents();
        }



        this->m_searchfsm->submitEvent(transitionName);
        QApplication::processEvents();

        this->currentTokenI++;

    }

    qDebug() << "Value Max Size set : " << searchOption->getMaxSize().getSize() << searchOption->getMaxSize().getType();
    qDebug() << "Value Min Size set : " << searchOption->getMinSize().getSize() << searchOption->getMinSize().getType();

    for (SizeSpec sizeSpec : searchOption->getSizes()) {
        qDebug() << "Value Size : " << sizeSpec.getSize() << sizeSpec.getType();
    }

    return new SearchAction(*searchOption);
}

bool SearchParser::sendNextOption(Token * token) {
    return (token->type() == Enum::TokenTypes::OPTION_SIZE ||
        token->type() == Enum::TokenTypes::OPTION_MIN_SIZE ||
        token->type() == Enum::TokenTypes::OPTION_MAX_SIZE);

}

Token* SearchParser::nextToken() {
    this->currentTokenI++;
    return this->getTokens()[this->currentTokenI];
}

Token* SearchParser::currentToken() {
    return this->getTokens()[this->currentTokenI];
}

QString SearchParser::getTransitionName(QString value) {
    return "is_" + value.toLower();
}

SizeSpec SearchParser::parseSizeString(const QString& sizeString) {

    //    if (tokens[1]->type() == Enum::TokenTypes::STRING) {
    //        searchOption->setValue(tokens[1]->value());
    //    } else {
    //        //Todo : Exception
    //    }

    //    for (int i = 0; i < tokens.size(); ++i) {
    //        const Token* currentToken = tokens.at(i);

    //        if (currentToken->type() == Enum::TokenTypes::OPTIONS &&
    //               (currentToken->value() == "MAX_SIZE" || currentToken->value() == "MIN_SIZE")) {
    //            // La valeur suivante est un COLON
    //            const Token* colonToken = tokens.at(++i);
    //            if (colonToken && colonToken->type() == Enum::TokenTypes::COLON) {
    //                const Token* sizeToken = tokens.at(++i);
    //                if (sizeToken && sizeToken->type() == Enum::TokenTypes::SIZE) {
    //                    SizeSpec sizeSpec = this->parseSizeString(sizeToken->value());
    //                    if (currentToken->value() == "MAX_SIZE") {
    //                        searchOption->setMaxSize(sizeSpec);
    //                    } else if (currentToken->value() == "MIN_SIZE") {
    //                        searchOption->setMinSize(sizeSpec);
    //                    }
    //                }
    //            }
    //        } else if (currentToken->type() == Enum::TokenTypes::OPTIONS &&
    //                   currentToken->value() == "SIZE") {


    //        }


    //    }



    qDebug() << "Value: " << sizeString;

    if (sizeString.isEmpty()) {
        //TODO: exception ?
        return SizeSpec();
    }

    qDebug() << "Conversion de : " << sizeString.left(sizeString.length() - 1);
    double sizeValue = sizeString.left(sizeString.length() - 1).toDouble();
    qDebug() << "Valeur converti : " << sizeValue;

    QString sizeType = sizeString.right(1).toUpper();

    // Vérifier le type et ajuster la valeur
    if (sizeType == "K") {
        sizeValue *= 1024;  // kilo-octets
    } else if (sizeType == "M") {
        sizeValue *= 1024 * 1024;  // mégaoctets
    } else if (sizeType == "G") {
        sizeValue *= 1024 * 1024 * 1024;  // gigaoctets
    }


    return SizeSpec(sizeValue, sizeType);
}
