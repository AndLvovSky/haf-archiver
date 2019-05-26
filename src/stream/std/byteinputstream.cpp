#include "byteinputstream.h"

#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <stdexcept>

ByteInputStream::ByteInputStream(QString filePath)
    : file(filePath) {
    fileSize = file.size();
    if (file.open(QIODevice::ReadOnly)) {
        readToCache();
    } else {
        throw std::runtime_error("Can not open file " + file.fileName().toStdString());
    }
}

void ByteInputStream::close()
{
    if (cache != nullptr) {
        delete[] cache;
    }
    file.close();
}

void ByteInputStream::reset() {
    if (file.seek(resetOffset)) {
        readToCache();
        curCounter = 0;
    } else {
        throw std::runtime_error("file.seek() returned false on file " +
                                 file.fileName().toStdString());
    }
}

Data::SizeType ByteInputStream::byteCount() const {
    return fileSize;
}

void ByteInputStream::setFileSize(int size)
{
    fileSize = size;
}

void ByteInputStream::setResetOffset(int offset)
{
    resetOffset = offset;
}

int ByteInputStream::readInt()
{
    int a;
    char* c = read(sizeof (int));
    memcpy(&a, c, sizeof (int));
    delete[] c;
    return a;
}

char* ByteInputStream::read(int length)
{
    char* c = new char[length];
    for (int i = 0; i < length; i++) {
        c[i] = getByte();
    }
    return c;
}

QByteArray ByteInputStream::readByteArray(int length)
{
    QByteArray a;
    for (int i = 0; i < length; i++) {
        a.append(getByte());
    }
    return a;
}

char ByteInputStream::getByte() {
    if (curCounter >= CACHE_SIZE) {
        readToCache();
        curCounter = 0;
    }
    char byte = cache[curCounter];
    curCounter++;
    return byte;
}

void ByteInputStream::readToCache()
{
    char* data = new char[CACHE_SIZE];
    int response = file.read(data, CACHE_SIZE);
    if (response == -1) {
        throw std::runtime_error("Error when reading from file " +
                                     file.fileName().toStdString());
    }
    if (cache != nullptr) {
        delete[] cache;
    }
    cache = data;
}
