QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main_test.cpp \
    test_compression.cpp

LIBS += -L$$OUT_PWD/../src/debug/ -lhafarchiverlib

INCLUDEPATH += $$PWD/../src

DEPENDPATH += $$PWD/../src

DESTDIR = $$OUT_PWD/../src/debug/

HEADERS += \
    test_compression.h

RESOURCES += \
    big_tests.qrc
