#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include "data.h"

class BitWriter {

private:

    Data& data;

    Data::SizeType charCount;

    unsigned int bitCount;

public:

    BitWriter(Data& data);

    void write(bool bit);

};

#endif // BIT_WRITER_H
