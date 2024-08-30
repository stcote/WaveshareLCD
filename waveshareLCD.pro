QT += gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

SOURCES += \
    WaveshareLCD.cpp \
    DEV_Config.cpp \
    LCD_1in28.cpp \
    WsBuffer.cpp

HEADERS += \
    WaveshareLCD.hpp \
    DEV_Config.hpp \
    LCD_1in28.hpp \
    WsBuffer.hpp

