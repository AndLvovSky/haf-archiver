#include "byteoutputstream.h"
#include <QDebug>

ByteOutputStream::ByteOutputStream(QString filePath, int writeMode)
    : file(filePath)
{
    QIODevice::OpenModeFlag openMode =
            (writeMode == WRITE_NEW) ? QIODevice::WriteOnly :
            QIODevice::Append;

    try{
        if(!file.open(openMode)){
            throw new runtime_error("Error creating file");
        }
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void ByteOutputStream::close()
{
    //flush();
    file.close();
}

void ByteOutputStream::putByte(char byte)
{
    char *c = new char[1];
    c[0] = byte;
    file.write(c, 1);
    /*if (bufferCounter >= BUFFER_SIZE) {
      flush();
    }
    buffer[bufferCounter] = byte;
    bufferCounter++;*/
}

void ByteOutputStream::writeInt(int n)
{
    file.write((char*)&n, sizeof(int));
}

void ByteOutputStream::writeString(QString s)
{
    file.write(s.toStdString().c_str(), s.size());
}

void ByteOutputStream::writeData(char *data, int length)
{
    file.write(data, length);
}

void ByteOutputStream::flush()
{
    try {
       file.write(buffer, bufferCounter);
       bufferCounter = 0;
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}
