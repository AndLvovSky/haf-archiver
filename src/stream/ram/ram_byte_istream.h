#ifndef RAM_BYTE_ISTREAM_H
#define RAM_BYTE_ISTREAM_H

#include "stream/byte_istream.h"

/**
 * @brief The RamByteIstream class implements ByteIstream, using RAM memory.
 *
 * The source file is entirely reading to the operative memory.
 * Basically used for testing.
 */
class RamByteIstream : public ByteIstream {

private:

    /** Representation of the source file. */
    Data data;

    /** Number of bytes, read from the 'data'. */
    Data::SizeType byteNumber;

public:

    /**
     * Deleted default constructor.
     */
    RamByteIstream() = delete;

    /**
     * Creates RamByteIstream with specified string.
     * String can be either Data or a file name to read from, according to
     * the second flag parameter.
     * @param s - Data representation or file name.
     * @param isFile - is aforementioned string a file name.
     */
    RamByteIstream(std::string s, bool isFile = false);

    void reset() override;

    char getByte() override;

    Data::SizeType byteCount() const override;

};

#endif // RAM_BYTE_ISTREAM_H
