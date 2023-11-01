QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbadapter.cpp \
    fileinfo.cpp \
    getaction.cpp \
    indexeraction.cpp \
    indexerrunner.cpp \
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

HEADERS += \
    action.h \
    dbadapter.h \
    enum.h \
    fileinfo.h \
    getaction.h \
    indexeraction.h \
    indexerrunner.h \
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
