#include "normalizer.h"
#include <QString>
#include <QDebug>
#include <QUrl>

Normalizer::Normalizer()
{
}

/**
 * @brief stringToList
 * @abstract split a string as list with double quotes (") handling
 * @param line
 * @return QStringList
 */

QStringList Normalizer::stringToList(QString line) {
    QStringList list;
    QRegularExpression re("\"([^\"]*)\"");
    QRegularExpressionMatchIterator matchIterator = re.globalMatch(line);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString matchedString = match.captured(1);
        list << matchedString;
    }

    for (auto l : qAsConst(list)) {
        QString ol = l;
        l.replace(" ", "<SPC>");
        line.replace(ol, l);
    }

    list.clear();
    QStringList tmp = line.split(' ');
    for (auto l : qAsConst(tmp)) {
        if (l.isEmpty())
            continue;

        list << l.replace("<SPC>", " ");
    }

    return list;
}

