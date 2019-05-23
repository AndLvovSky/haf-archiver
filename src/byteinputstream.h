#ifndef BYTEINPUTSTREAM_H
#define BYTEINPUTSTREAM_H

#include "byte_istream.h"
#include <qbytearray.h>
#include "qfile.h"

class ByteInputStream : ByteIstream
{
private:
    int CACHE_SIZE = 1000;

private:
    Data cache;

    int curCounter = 0;

    QFile file;

public:
    ByteInputStream(std::string filePath);

    void reset() override;

    char getByte() override;

    Data::SizeType byteCount() const override;

private:
    void readToCache();
};

#endif // BYTEINPUTSTREAM_H
