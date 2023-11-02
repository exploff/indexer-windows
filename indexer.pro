QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

GIT_VERSION = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
GIT_COMMITS = $$system(git --git-dir $$PWD/.git --work-tree $$PWD rev-list HEAD --count)

VERSION += 1.0.0.$$GIT_COMMITS
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

SOURCES += \
    common/token/token.cpp \
    common\dbadapter\dbadapter.cpp \
    common\fileinfo\fileinfo.cpp \
    common\action\getaction.cpp \
    common\action\indexeraction.cpp \
    common\debug\debug.cpp \
    executor\executor.cpp \
    indexerrunner/indexer.cpp \
    commandHandler\commandhandler.cpp \
    commandhandler/parserfactory/parser/addparser.cpp \
    commandhandler/parserfactory/parser/clearparser.cpp \
    commandhandler/parserfactory/parser/getparser.cpp \
    commandhandler/parserfactory/parser/pushparser.cpp \
    main.cpp \
    commandhandler\normalizer\normalizer.cpp \
    commandhandler\parserfactory\parser\indexerparser.cpp \
    commandhandler\parserfactory\parserfactory.cpp \
    server.cpp

RESOURCES += \
    dataset.qrc \
    dataset.qrc

HEADERS += \
    common/constants.h \
    commandhandler/parserfactory/parser/indexerparser.h \
    common/token/token.h \
    common\action\action.h \
    common\dbadapter\dbadapter.h \
    common\enum\enum.h \
    common\fileinfo\fileinfo.h \
    common\action\getaction.h \
    common\action\indexeraction.h \
    common\debug\debug.h \
    executor\executor.h \
    indexerrunner/indexer.h \
    commandhandler\commandhandler.h \
    commandhandler\normalizer\normalizer.h \
    commandhandler\parserfactory\parser\parser.h \
    commandhandler\parserfactory\parserfactory.h \
    server.h

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
