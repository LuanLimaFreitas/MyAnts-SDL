TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2

SOURCES += main.cpp \
    ant.cpp \
    droplet.cpp \
    network.cpp \
    window.cpp \
    auxiliary_functions.cpp \
    parameters.cpp \
    globals.cpp

HEADERS += \
    ant.h \
    droplet.h \
    network.h \
    window.h \
    auxiliary_functions.h \
    parameters.h \
    globals.h
