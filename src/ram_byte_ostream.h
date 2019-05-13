#ifndef RAM_BYTE_OSTREAM_H
#define RAM_BYTE_OSTREAM_H

#include "byte_ostream.h"
#include "data.h"

#include <vector>

class RamByteOstream : public ByteOstream {

private:

    std::vector<char> data;

public:

    RamByteOstream();

    void putByte(char byte) override;

    Data getData();

};

#endif // RAM_BYTE_OSTREAM_H
