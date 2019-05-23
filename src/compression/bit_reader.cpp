#include "bit_reader.h"

#include <stdexcept>

BitReader::BitReader(ByteIstream& in) :
    in(in), ch(0), bitCount(0) {}

bool BitReader::read() {
    if (bitCount == 0) {
        ch = in.getByte();
    }
    bool res = (ch >> bitCount) & 1;
    bitCount = (bitCount + 1) % 8;
    return res;
}
