QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    Card.h \
    Game.h \
    Menu.h \
    Window.h

SOURCES += \
    Card.cpp \
    Game.cpp \
    Menu.cpp \
    Window.cpp \
    main.cpp

DISTFILES += \
    cards/template.json
