#-------------------------------------------------
#
# Project created by QtCreator 2011-11-26T15:48:07
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       += network
QT       += xml
QT       += gui



TARGET = CUBookServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    userprofile.cpp \
    updatewrapper.cpp \
    removewrapper.cpp \
    newsflash.cpp \
    messageprotocol.cpp \
    getwrapper.cpp \
    flashsegment.cpp \
    flashboard.cpp \
    filter.cpp \
    database.cpp \
    cuurl.cpp \
    cutask.cpp \
    cuserver.cpp \
    cupicture.cpp \
    cuclient.cpp \
    addwrapper.cpp \
    sqlapi.cpp \
    messagetranslator.cpp

HEADERS += \
    cuserver.h \
    userprofile.h \
    updatewrapper.h \
    removewrapper.h \
    newsflash.h \
    messageprotocol.h \
    getwrapper.h \
    flashsegment.h \
    flashboard.h \
    database.h \
    cuurl.h \
    cutask.h \
    cupicture.h \
    cuclient.h \
    addwrapper.h \
    filter.h \
    sqlapi.h \
    messagetranslator.h

RESOURCES += \
    resources.qrc
