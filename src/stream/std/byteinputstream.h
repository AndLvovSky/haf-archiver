#ifndef BYTEINPUTSTREAM_H
#define BYTEINPUTSTREAM_H

#include "stream/byte_istream.h"
#include <qbytearray.h>
#include "qfile.h"

class ByteInputStream : public ByteIstream
{
private:
    int CACHE_SIZE = 1000;
    int fileSize;

private:
    char* cache;

    int curCounter = 0;

    QFile file;

    int resetOffset = 0;

public:
    ByteInputStream(QString filePath);

    void close();

    void reset() override;

    char getByte() override;

    Data::SizeType byteCount() const override;

    void setFileSize(int size);

    void setResetOffset(int offset);

    int readInt();

    char* read(int length);

    QByteArray readByteArray(int length);

private:
    void readToCache();
};

#endif // BYTEINPUTSTREAM_H
