#include "ram_byte_ostream.h"
#include <QDebug>

RamByteOstream::RamByteOstream() {}

void RamByteOstream::putByte(char byte) {
    data.push_back(byte);
}

Data RamByteOstream::getData() {
    return Data(data.size(), data);
}
