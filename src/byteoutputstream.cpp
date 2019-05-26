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
            throw new std::runtime_error("Error creating or opening file "
                                         + file.fileName().toStdString());
        }
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void ByteOutputStream::close()
{
    file.close();
}

void ByteOutputStream::putByte(char byte)
{
    char *c = new char[1];
    c[0] = byte;
    int response = file.write(c, 1);
    if (response == -1) {
        throw new std::runtime_error("Error writing to file " +
                                     file.fileName().toStdString());
    }
    delete[] c;
}

void ByteOutputStream::writeInt(int n)
{
    int response = file.write((char*)&n, sizeof(int));
    if (response == -1) {
        throw new std::runtime_error("Error writing to file " +
                                     file.fileName().toStdString());
    }
}

void ByteOutputStream::writeString(QString s)
{
    int response = file.write(s.toStdString().c_str(), s.size());
    if (response == -1) {
        throw new std::runtime_error("Error writing to file " +
                                     file.fileName().toStdString());
    }
}

void ByteOutputStream::writeData(char *data, int length)
{
    int response = file.write(data, length);
    if (response == -1) {
        throw new std::runtime_error("Error writing to file " +
                                     file.fileName().toStdString());
    }
}
