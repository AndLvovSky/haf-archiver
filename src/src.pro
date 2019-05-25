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
    util/data.cpp \
    stream/ram/ram_byte_istream.cpp \
    stream/ram/ram_byte_ostream.cpp \
    stream/std/byteinputstream.cpp \
    stream/std/byteoutputstream.cpp \
    archive/archiver.cpp \
    archive/unarchiver.cpp \
    info/archiveinfo.cpp \
    info/fileinfo.cpp \
    util/charwithsize.cpp

HEADERS += \
    compression/bit_reader.h \
    compression/bit_writer.h \
    stream/byte_istream.h \
    stream/byte_ostream.h \
    compression/compressor.h \
    compression/decompressor.h \
    compression/key.h \
    compression/node.h \
    util/data.h \
    stream/ram/ram_byte_istream.h \
    stream/ram/ram_byte_ostream.h \
    stream/std/byteinputstream.h \
    stream/std/byteoutputstream.h \
    archive/archiver.h \
    archive/unarchiver.h \
    info/archiveinfo.h \
    info/fileinfo.h \
    util/charwithsize.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
