#include "searchparser.h"

#include <QString>

#include "common/action/action.h"
#include "common/action/searchaction.h"

SearchParser::SearchParser()
{

}

Action* SearchParser::parse()
{
    SearchOption* searchOption = new SearchOption();


    QList<Token*> tokens = this->getTokens();
    if (tokens[1]->type() == Enum::TokenTypes::STRING) {
        searchOption->setValue(tokens[1]->value());
    } else {
        //Todo : Exception
    }

    for (int i = 0; i < tokens.size(); ++i) {
        const Token* currentToken = tokens.at(i);

        if (currentToken->type() == Enum::TokenTypes::OPTIONS &&
               (currentToken->value() == "MAX_SIZE" || currentToken->value() == "MIN_SIZE")) {
            // La valeur suivante est un COLON
            const Token* colonToken = tokens.at(++i);
            if (colonToken && colonToken->type() == Enum::TokenTypes::COLON) {
                const Token* sizeToken = tokens.at(++i);
                if (sizeToken && sizeToken->type() == Enum::TokenTypes::SIZE) {
                    SizeSpec sizeSpec = this->parseSizeString(sizeToken->value());
                    if (currentToken->value() == "MAX_SIZE") {
                        searchOption->setMaxSize(sizeSpec);
                    } else if (currentToken->value() == "MIN_SIZE") {
                        searchOption->setMinSize(sizeSpec);
                    }
                }
            }
        } else if (currentToken->type() == Enum::TokenTypes::OPTIONS &&
                   currentToken->value() == "SIZE") {


        }


    }



    //    qDebug() << "Value: " << token->value() << " => " << token->typeString();


    return new SearchAction(*searchOption);
}

SizeSpec SearchParser::parseSizeString(const QString& sizeString) {
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
