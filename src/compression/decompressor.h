#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "compressed.h"
#include "bit_reader.h"

class Decompressor {

private:

    BitReader bitReader;

    Key key;

    char getByte();

public:

    Decompressor(const Compressed& compressed);

    Data decompress();

};

#endif // DECOMPRESSOR_H
