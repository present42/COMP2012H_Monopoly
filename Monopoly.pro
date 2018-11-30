#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23T13:27:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Monopoly
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big

SOURCES += \
        main.cpp \
        ui/mainwindow.cpp \
    src/player.cpp \
    src/server.cpp \
    src/asset.cpp \
    src/railroad.cpp \
    src/utility.cpp \
    src/property.cpp \
    ui/gamewindow.cpp \
    src/block.cpp \
    ui/abstractblockui.cpp \
    ui/specialblockui.cpp \
    ui/normalblockui.cpp \
    ui/tokenui.cpp \
    ui/normalblockwithlabelui.cpp \
    ui/dialogue/unpurchasedassetwidget.cpp \
    ui/dialogue/rolldicewidget.cpp \
    ui/dialogue/endturnwidget.cpp \
    ui/dialogue/owemoneywidget.cpp \
    ui/dialogue/injailwidget.cpp


HEADERS += \
    ui/mainwindow.h \
    src/player.h \
    src/token.h \
    src/server.h \
    src/asset.h \
    src/railroad.h \
    src/property.h \
    src/utility.h \
    src/block.h \
    src/card.h \
    ui/gamewindow.h \
    ui/abstractblockui.h \
    ui/specialblockui.h \
    ui/normalblockui.h \
    ui/tokenui.h \
    ui/normalblockwithlabelui.h \
    ui/blockuifactory.h \
    ui/dialogue/unpurchasedassetwidget.h \
    ui/dialogue/rolldicewidget.h \
    ui/dialogue/endturnwidget.h \
    ui/dialogue/owemoneywidget.h \
    ui/dialogue/injailwidget.h



FORMS += \
    ui/gamewindow.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
