QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    client.cpp \
    existingrooms.cpp \
    game.cpp \
    main.cpp \
    mainwindow.cpp \
    room.cpp \
    round.cpp \
    server.cpp \
    settings.cpp

HEADERS += \
    canvas.h \
    client.h \
    existingrooms.h \
    game.h \
    mainwindow.h \
    room.h \
    round.h \
    server.h \
    settings.h

FORMS += \
    existingrooms.ui \
    game.ui \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
