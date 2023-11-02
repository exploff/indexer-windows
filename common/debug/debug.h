#ifndef DEBUG_H
#define DEBUG_H

#include <QDebug>

// set this to 1 to log fiunction / lines
#define DEBUG_FUNCTIONS 1

#if DEBUG_FUNCTIONS
#define LOGGING_MESSAGE_PATTERN                                                                                              \
"%{time hh:mm:ss.zzz} "                                                                                                  \
    "%{if-category}%{category}.%{endif}"                                                                                     \
    "%{if-debug}DBG%{endif}"                                                                                                 \
    "%{if-info}INF%{endif}"                                                                                                  \
    "%{if-warning}WRN%{endif}"                                                                                               \
    "%{if-critical}CRT%{endif}"                                                                                              \
    "%{if-fatal}FTL%{endif} "                                                                                                \
    "%{message} - %{file}@%{line} - %{function}"
#else
#define LOGGING_MESSAGE_PATTERN                                                                                              \
"%{time hh:mm:ss.zzz} "                                                                                                  \
    "%{if-category}%{category}.%{endif}"                                                                                     \
    "%{if-debug}DBG%{endif}"                                                                                                 \
    "%{if-info}INF%{endif}"                                                                                                  \
    "%{if-warning}WRN%{endif}"                                                                                               \
    "%{if-critical}CRT%{endif}"                                                                                              \
    "%{if-fatal}FTL%{endif} "                                                                                                \
    "%{message}"
#endif

// clang-format off

void    myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void    initDebug();
QString loadLoggingRules(QString filename);
void    logAppInfo();
// clang-format on

#endif // DEBUG_H
