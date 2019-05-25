#ifndef BYTEOUTPUTSTREAM_H
#define BYTEOUTPUTSTREAM_H

#include "iostream"
#include <QFile>
#include "byte_ostream.h"
#include <QDataStream>

class ByteOutputStream : public ByteOstream
{
private:
    QFile file;

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
};

#endif // BYTEOUTPUTSTREAM_H
