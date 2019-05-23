#include "bit_writer.h"

#include <stdexcept>
#include <QDebug>

BitWriter::BitWriter(ByteOstream& out) :
    out(out), ch(0), bitCount(0) {}

void BitWriter::write(bool bit) {
    if (bit) {
        ch ^= 1 << bitCount;
    }
    bitCount++;
    if (bitCount == 8) {
        out.putByte(ch);
        bitCount = 0;
        ch = 0;
    }
}

void BitWriter::flush() {
    if (bitCount) {
        out.putByte(ch);
    }
}
