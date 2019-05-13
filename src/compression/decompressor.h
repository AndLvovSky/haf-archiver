#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "byte_istream.h"
#include "byte_ostream.h"
#include "bit_reader.h"
#include "key.h"

class Decompressor {

private:

    ByteIstream& in;

    ByteOstream& out;

    Key key;

    BitReader bitReader;

    char getByte();

public:

    Decompressor(ByteIstream& in, ByteOstream& out, const Key& key);

    void decompress();

};

#endif // DECOMPRESSOR_H
