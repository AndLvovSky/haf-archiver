#ifndef BYTEOUTPUTSTREAM_H
#define BYTEOUTPUTSTREAM_H

#include "iostream"
#include <QFile>
#include "byte_ostream.h"
#include <QDataStream>

using namespace std;

class ByteOutputStream : public ByteOstream
{
private:
    int BUFFER_SIZE = 1000;

    unique_ptr<QFile> file;
    char* buffer = new char[BUFFER_SIZE];
    int bufferCounter = 0;

public:
    static const int WRITE_NEW = 0;
    static const int APPEND = 1;

    /**
     * @brief ByteOutputStream Creates and initializes output file
     * @param filePath output file path
     */
    ByteOutputStream(string filePath, int writeMode);

    /**
     * @brief close closes descriptor of the output file
     */
    void close();

    void putByte(char byte);

    void flush();
};

#endif // BYTEOUTPUTSTREAM_H
