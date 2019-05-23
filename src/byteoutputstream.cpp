#include "byteoutputstream.h"
#include <QDebug>

ByteOutputStream::ByteOutputStream(string filePath, int writeMode)
{
    QIODevice::OpenModeFlag openMode =
            (writeMode == WRITE_NEW) ? QIODevice::WriteOnly :
            QIODevice::Append;

    file = make_unique<QFile>(QString::fromStdString(filePath));
    try{
        if(!file->open(openMode)){
            throw new runtime_error("Error creating file");
        }
    } catch(runtime_error err) {
        qInfo(err.what());
    }
}

void ByteOutputStream::close()
{
    flush();
    file->close();
}

void ByteOutputStream::putByte(char byte)
{
    if (bufferCounter >= BUFFER_SIZE) {
      flush();
      bufferCounter = 0;
    }
    buffer[bufferCounter] = byte;
    bufferCounter++;
}

void ByteOutputStream::flush()
{
    try {
       file->write(buffer, bufferCounter);
       bufferCounter = 0;
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}
