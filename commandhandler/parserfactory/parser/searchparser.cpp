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
    bool setCreatedDate = false;
    bool setModifiedDate = false;
    bool isDateBetween = false;

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

    this->m_searchfsm->connectToState("OPTION_EXT", [this, searchOption]() {
        qDebug() << "OPTION EXT";
    });

    this->m_searchfsm->connectToState("OPTION_TYPE", [this, searchOption]() {
        qDebug() << "OPTION TYPE";
    });

    this->m_searchfsm->connectToState("STRING", [this, searchOption]() {
        Token* token = this->currentToken();
        if (token->type() == Enum::TokenTypes::STRING) {
            searchOption->setValue(token->value());
        }
    });

    this->m_searchfsm->connectToState("EXTENSION", [this, searchOption]() {
        qDebug() << "AJOUT D EXTENSION";
        Token* token = this->currentToken();
        if (token->type() == Enum::TokenTypes::EXTENSION) {
            searchOption->addExtension(token->value());
        }
    });


    this->m_searchfsm->connectToState("TYPE", [this, searchOption]() {
        qDebug() << "AJOUT TYPE";
        Token* token = this->currentToken();
        if (token->type() == Enum::TokenTypes::TYPE) {
            searchOption->addType(token->value());
        }
    });

    this->m_searchfsm->connectToState("OPTION_CREATED", [this, searchOption, &setCreatedDate, &setModifiedDate]() {
        qDebug() << "AJOUT DATE CREATION";
        setModifiedDate = false;
        setCreatedDate = true;
    });
    this->m_searchfsm->connectToState("OPTION_LAST_MODIFIED", [this, searchOption, &setCreatedDate, &setModifiedDate]() {
        qDebug() << "AJOUT DATE CREATION";
        setCreatedDate = false;
        setModifiedDate = true;
    });
    this->m_searchfsm->connectToState("DATE", [this, searchOption, &isDateBetween, &setCreatedDate, &setModifiedDate]() {
        qDebug() << "AJOUT DATE";
        Token* token = this->currentToken();
        if (token->type() == Enum::TokenTypes::DATE) {
            QDate date = stringToDate(token->value());

            qDebug() << "CONVERSION DATE  : " << token->value();


            if (setCreatedDate) {
                DateSpec oldDateSpec = searchOption->getCreatedDate();
                oldDateSpec.addDate(date);
                searchOption->setCreatedDate(oldDateSpec);

                setCreatedDate = isDateBetween ? oldDateSpec.getDates()->length() < 2 : false;

            } else if (setModifiedDate) {
                DateSpec oldDateSpec = searchOption->getLastModifiedDate();
                oldDateSpec.addDate(date);
                searchOption->setLastModifiedDate(oldDateSpec);

                setModifiedDate = isDateBetween ? oldDateSpec.getDates()->length() < 2 : false;
            }
        }
    });

    this->m_searchfsm->connectToState("BETWEEN", [this, searchOption, &isDateBetween, &setCreatedDate, &setModifiedDate]() {
        if (setCreatedDate || setModifiedDate) {
            isDateBetween = true;
        }
    });


    this->m_searchfsm->init();
    this->m_searchfsm->start();

    for (Token* token : tokens) {

        qDebug() << "Traitement token " << token->value();
        QString transitionName = this->getTransitionName(token->typeString());

        if (sendNextOption(token)) {
            qDebug() << "Transition to " << "is_next_option";
            this->m_searchfsm->submitEvent("is_next_option");
            QApplication::processEvents();
        }
        qDebug() << "Transition to " << transitionName;
        this->m_searchfsm->submitEvent(transitionName);
        QApplication::processEvents();

        this->currentTokenI++;

    }

    qDebug() << "Value Max Size set : " << searchOption->getMaxSize().getSize() << searchOption->getMaxSize().getType();
    qDebug() << "Value Min Size set : " << searchOption->getMinSize().getSize() << searchOption->getMinSize().getType();

    for (SizeSpec sizeSpec : searchOption->getSizes()) {
        qDebug() << "Value Size : " << sizeSpec.getSize() << sizeSpec.getType();
    }

    for (QString ext : searchOption->getExtensions()) {
        qDebug() << "Value ext : " << ext;
    }

    for (QString type : searchOption->getTypes()) {
        qDebug() << "Value type : " << type;
    }

    return new SearchAction(*searchOption);
}

bool SearchParser::sendNextOption(Token * token) {
    return (token->type() == Enum::TokenTypes::OPTION_SIZE ||
        token->type() == Enum::TokenTypes::OPTION_MIN_SIZE ||
        token->type() == Enum::TokenTypes::OPTION_MAX_SIZE ||
        token->type() == Enum::TokenTypes::OPTION_EXT ||
        token->type() == Enum::TokenTypes::OPTION_TYPE ||
        token->type() == Enum::TokenTypes::OPTION_CREATED ||
        token->type() == Enum::TokenTypes::OPTION_LAST_MODIFIED);

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

QDate SearchParser::stringToDate(QString dateString) {
    QStringList formats = {"MM/yyyy", "dd/MM/yyyy", "yyyy", "yy"};

    // Essayer chaque format jusqu'à ce que la conversion réussisse
    QDate date;
    for (const QString& format : formats) {
        date = QDate::fromString(dateString, format);
        if (date.isValid()) {
            break;  // Sortir de la boucle si la conversion réussit
        }
    }

    // Vérification de la validité de la conversion
    if (!date.isValid()) {
        qDebug() << "La conversion de la chaîne en QDate a échoué.";
        // Vous pouvez gérer l'erreur ici selon vos besoins.
    }

    return date;
}
