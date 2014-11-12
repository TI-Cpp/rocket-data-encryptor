TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

QMAKE_CXXFLAGS += -finline-small-functions -momit-leaf-frame-pointer

SOURCES += main.cpp \
    des.cpp \
    des3.cpp \
    descbc.cpp \
    fileencryption.cpp

HEADERS += \
    des.h \
    des_data.h \
    tests.h \
    des3.h \
    descbc.h \
    fileencryption.h

