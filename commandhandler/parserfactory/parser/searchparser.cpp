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


    //Utiliser les tokens
    //nextToken

    this->m_searchfsm->connectToState("OPTION_MIN_SIZE", [this, searchOption]() {
        qDebug() << "1 > MIN_SIZE";

    });

    this->m_searchfsm->connectToState("OPTION_MAX_SIZE", [this, searchOption]() {
        qDebug() << "1 > MAX_SIZE";
    });

    this->m_searchfsm->connectToState("SIZE_UNIT", [this]() {
        qDebug() << "2 > SIZE_UNIT";
        qDebug() << "AJOUT DANS LA SEARCH OPTION";

        // On est au bout on retourne a l'état search option
        this->m_searchfsm->submitEvent("is_next_option");
        QApplication::processEvents();
    });


    this->m_searchfsm->init();
    this->m_searchfsm->start();



    for (Token* token : tokens) {
        qDebug() << "Traitement token " << token->value();
        QString transitionName = this->getTransitionName(token->typeString());
        qDebug() << "Transition to " << transitionName;
        this->m_searchfsm->submitEvent(transitionName);
        QApplication::processEvents();

    }

    //CA FONCTIONNE FAUT CONTINUER LE MIN_SIZE et MAX_SIZE et attribuer la valeur au searchoption, faut juste enregistrer une variable tempon
    //quand on est dans l'état précédent min_size ça veut dire que dans le state unit_size on traite un min_size etc..

    /*
    qDebug() << "Traitement current token : " << token->value();
    if (token->type() == Enum::TokenTypes::OPTIONS) {
        QString transitionName = this->getTransitionName(token->typeString());
        qDebug() << "Transition" << transitionName;
        this->m_searchfsm->submitEvent(transitionName);
    }*/

    /*

    while (this->currentTokenI < tokens.size()) {

        Token* token = this->nextToken();
        qDebug() << "Traitement current token : " << token->value();

        if (token->type() == Enum::TokenTypes::OPTIONS) {
            QString transitionName = this->getTransitionName(token->value());
            qDebug() << "Transition" << transitionName;
            this->m_searchfsm->submitEvent(transitionName);
        }
        QApplication::processEvents();
    }
*/
    return new SearchAction(*searchOption);
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



    //    //    qDebug() << "Value: " << token->value() << " => " << token->typeString();

    if (sizeString.isEmpty()) {
        //TODO: exception ?
        return SizeSpec();
    }

    double sizeValue = sizeString.left(sizeString.length() - 1).toDouble();
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
