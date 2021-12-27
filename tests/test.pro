QT = core \
    network \
    gui \
    widgets
    
TEMPLATE = app
    
CONFIG += c++17 \
        console

HEADERS += ../07-GuessMyDrawing/Application/messageparser.h \
    ../07-GuessMyDrawing/Application/client.h


SOURCES += ../07-GuessMyDrawing/Application/messageparser.cpp \
    ../07-GuessMyDrawing/Application/client.cpp \
    test.cpp

TARGET = test
