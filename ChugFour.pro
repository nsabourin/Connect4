TEMPLATE = vcapp
TARGET = ChugFour

HEADERS += \
    menu.h \
    menudeux.h \
    menutrois.h \
    gameplay.h \
    token.h \
    jouerToken.h \
    tableau.h \
    ia.h \
    deplacement.h \
    infos.h \
	CommunicationFPGA.h
SOURCES += \
    main.cpp \
    menu.cpp \
    menudeux.cpp \
    menutrois.cpp \
    gameplay.cpp \
    token.cpp \
    jouerToken.cpp \
    tableau.cpp \
    ia.cpp \
    deplacement.cpp \
    infos.cpp
INCLUDEPATH += ../connect4
LIB			+= ../connectFour/CommunicationFPGA.lib
CONFIG += warn_on qt debug windows console
QT += widgets
