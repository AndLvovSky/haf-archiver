#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "compressed.h"

class Decompressor {

public:

    Decompressor(const Compressed& compressed);

    Data decompress();

};

#endif // DECOMPRESSOR_H
