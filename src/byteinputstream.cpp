#include "byteinputstream.h"

#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <stdexcept>

ByteInputStream::ByteInputStream(std::string filePath)
    : file(QString::fromStdString(filePath)){
    fileSize = file.size();
    if (file.open(QIODevice::ReadOnly)) {
        readToCache();
    } else {
        throw std::runtime_error("Can not open file!");
    }
}

void ByteInputStream::reset() {
    file.reset();
    if (resetOffset > 0) {
        char* data = new char[resetOffset];
        file.read(data, resetOffset);
    }
    readToCache();
    curCounter = 0;
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

void ByteInputStream::readToCache()
{
    char* data = new char[CACHE_SIZE];
    int response = file.read(data, CACHE_SIZE);
    if (response == -1) {
        throw new std::runtime_error("Reading from file error");
    }
    cache = Data(CACHE_SIZE);
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i] =  data[i];
    }
}
