#-------------------------------------------------
#
# Project created by QtCreator 2019-05-07T20:44:55
#
#-------------------------------------------------

QT       -= gui

TARGET = hafarchiverlib

TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    compression/bit_reader.cpp \
    compression/bit_writer.cpp \
    compression/compressor.cpp \
    compression/decompressor.cpp \
    compression/key.cpp \
    compression/node.cpp \
    data.cpp \
    ram_byte_istream.cpp \
    ram_byte_ostream.cpp \
    byteinputstream.cpp \
    byteoutputstream.cpp \
    archiver.cpp \
    unarchiver.cpp \
    archiveinfo.cpp \
    fileinfo.cpp \
    charwithsize.cpp

HEADERS += \
    compression/bit_reader.h \
    compression/bit_writer.h \
    byte_istream.h \
    byte_ostream.h \
    compression/compressor.h \
    compression/decompressor.h \
    compression/key.h \
    compression/node.h \
    data.h \
    ram_byte_istream.h \
    ram_byte_ostream.h \
    byteinputstream.h \
    byteoutputstream.h \
    archiver.h \
    unarchiver.h \
    archiveinfo.h \
    fileinfo.h \
    charwithsize.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
