#ifndef RAM_BYTE_ISTREAM_H
#define RAM_BYTE_ISTREAM_H

#include "byte_istream.h"

class RamByteIstream : public ByteIstream {

private:

    Data data;

    Data::SizeType byteNumber;

public:

    RamByteIstream() = delete;

    RamByteIstream(std::string s, bool isFile = false);

    void reset() override;

    char getByte() override;

    Data::SizeType byteCount() const override;

};

#endif // RAM_BYTE_ISTREAM_H
