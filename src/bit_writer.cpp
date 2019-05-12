#include "bit_writer.h"

#include <stdexcept>

BitWriter::BitWriter(Data& data) :
    data(data), charCount(0), bitCount(0) {
    for (int i = 0; i < data.size; i++) {
        data[i] = 0;
    }
}

void BitWriter::write(bool bit) {
    if (charCount >= data.size) {
        throw std::runtime_error("Data is full!");
    }
    if (bit) {
        data[charCount] ^= 1 << bitCount;
    }
    bitCount++;
    if (bitCount == 8) {
        bitCount = 0;
        charCount++;
    }
}
