#ifndef BYTEOUTPUTSTREAM_H
#define BYTEOUTPUTSTREAM_H

#include "iostream"
#include <QFile>
#include "byte_ostream.h"
#include <memory>

class ByteOutputStream : ByteOstream
{
private:
    int BUFFER_SIZE = 1000;

    std::unique_ptr<QFile> file;
    char* buffer = new char[BUFFER_SIZE];
    int bufferCounter = 0;

public:
    /**
     * @brief ByteOutputStream Creates and initializes output file
     * @param filePath output file path
     */
    ByteOutputStream(std::string filePath);

    /**
     * @brief close closes descriptor of the output file
     */
    void close();

    void putByte(char byte);

    void flush();
};

#endif // BYTEOUTPUTSTREAM_H