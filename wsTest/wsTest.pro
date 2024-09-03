QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.hpp

FORMS += \
    MainWindow.ui

# WaveshareLCD library
INCLUDEPATH += ..
LIBS += -L ..
LIBS += -lm -lwaveshareLCD /usr/local/lib/liblgpio.so
