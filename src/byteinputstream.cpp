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
        throw std::runtime_error("Can not open file!");
    }
}

void ByteInputStream::close()
{
    delete[] cache;
    file.close();
}

void ByteInputStream::reset() {
    file.seek(resetOffset);
    readToCache();
    curCounter = 0;
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
        throw new std::runtime_error("Reading from file error");
    }
    cache = data;
}
