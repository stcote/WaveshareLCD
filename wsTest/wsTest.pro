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
INCLUDEPATH += /home/steve/dev/GitHub/WaveshareLCD
LIBS += -L /home/steve/dev/GitHub/WaveshareLCD
LIBS += -lm -lwaveshareLCD /usr/local/lib/liblgpio.so
