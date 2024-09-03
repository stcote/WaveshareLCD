QT       += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.hpp

FORMS += \
    MainWindow.ui

# Waveshare stuff
INCLUDEPATH += /home/steve/dev/waveshare
LIBS += -L /home/steve/dev/waveshare
LIBS += -lm -lwaveshare /usr/local/lib/liblgpio.so
