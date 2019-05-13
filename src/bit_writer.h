#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include "data.h"
#include "byte_ostream.h"

class BitWriter {

private:

    ByteOstream& out;

    char ch;

    Data::SizeType bitCount;

public:

    BitWriter(ByteOstream& out);

    void write(bool bit);

    void flush();

};

#endif // BIT_WRITER_H
