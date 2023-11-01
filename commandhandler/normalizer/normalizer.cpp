#include "normalizer.h"
#include <QString>
Normalizer::Normalizer()
{
}
QString normalize(const QString& command) {
    // Implement your normalization logic here
    // For example, you can convert the command to lowercase
    return command.toLower();
}
