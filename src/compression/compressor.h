#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "data.h"
#include "compressed.h"

class Compressor {

public:

    Compressor(const Data& data);

    Compressed compress();

};

#endif // COMPRESSOR_H
