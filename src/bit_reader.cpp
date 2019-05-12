#include "bit_reader.h"

#include <stdexcept>

BitReader::BitReader(const Data& data) :
    data(data), charCount(0), bitCount(0) {}

bool BitReader::read() {
    if (charCount >= data.size) {
        throw std::runtime_error("Data is empty!");
    }
    bool res = (data[charCount] >> bitCount) & 1;
    bitCount++;
    if (bitCount == 8) {
        bitCount = 0;
        charCount++;
    }
    return res;
}
