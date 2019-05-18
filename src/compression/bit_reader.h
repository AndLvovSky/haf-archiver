#ifndef BIT_READER_H
#define BIT_READER_H

#include "data.h"
#include "byte_istream.h"

class BitReader {

private:

    ByteIstream& in;

    char ch;

    Data::SizeType bitCount;

public:

    BitReader(ByteIstream& in);

    bool read();

};

#endif // BIT_READER_H
