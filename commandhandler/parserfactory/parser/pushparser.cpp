#include "parser.h"
#include <QString>
class PushParser : public Parser {
public:
    bool parse(const QString& input) override {
        // Implement your parsing logic here
        // Return true if parsing succeeds, false otherwise
        return true;
    }
};
