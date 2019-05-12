#ifndef BIT_READER_H
#define BIT_READER_H

#include "data.h"

class BitReader {


private:

    Data data;

    Data::SizeType charCount;

    unsigned int bitCount;

public:

    BitReader(const Data& data);

    bool read();

};

#endif // BIT_READER_H
