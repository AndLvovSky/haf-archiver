#ifndef BYTEOUTPUTSTREAM_H
#define BYTEOUTPUTSTREAM_H

#include "iostream"
#include <QFile>
#include "byte_ostream.h"
#include <QDataStream>

class ByteOutputStream : ByteOstream
{
private:
    int BUFFER_SIZE = 1000;

    QFile file;
    char* buffer = new char[BUFFER_SIZE];
    int bufferCounter = 0;

public:
    static const int WRITE_NEW = 0;
    static const int APPEND = 1;

    /**
     * @brief ByteOutputStream Creates and initializes output file
     * @param filePath output file path
     */
    ByteOutputStream(QString filePath, int writeMode);

    /**
     * @brief close closes descriptor of the output file
     */
    void close();

    void putByte(char byte);

    void writeInt(int n);

    void writeString(QString s);

    void writeData(char* data, int length);

    void flush();
};

#endif // BYTEOUTPUTSTREAM_H
