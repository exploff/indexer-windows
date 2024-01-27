#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

#include <QException>

class ParserException : public QException
{
public:
    ParserException(const QString& message);

    const char* what() const noexcept override
    {
        return message.toUtf8().constData();
    }

private:
    QString message;
};

#endif // PARSEREXCEPTION_H
