#ifndef BYTE_ISTREAM_H
#define BYTE_ISTREAM_H

#include "data.h"

struct ByteIstream {

    virtual void reset() = 0;

    virtual char getByte() = 0;

    virtual Data::SizeType byteCount() const = 0;

};

#endif // BYTE_ISTREAM_H
