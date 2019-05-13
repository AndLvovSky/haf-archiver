#-------------------------------------------------
#
# Project created by QtCreator 2019-05-07T20:44:55
#
#-------------------------------------------------

QT       -= gui

TARGET = hafarchiverlib

TEMPLATE = lib

SOURCES += \
    bit_reader.cpp \
    bit_writer.cpp \
    compression/compressed.cpp \
    compression/compressor.cpp \
    compression/decompressor.cpp \
    compression/key.cpp \
    compression/node.cpp \
    data.cpp \
    ram_byte_istream.cpp \
    ram_byte_ostream.cpp

HEADERS += \
    bit_reader.h \
    bit_writer.h \
    byte_istream.h \
    byte_ostream.h \
    compression/compressed.h \
    compression/compressor.h \
    compression/decompressor.h \
    compression/key.h \
    compression/node.h \
    data.h \
    ram_byte_istream.h \
    ram_byte_ostream.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
