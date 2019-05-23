#ifndef BIT_READER_H
#define BIT_READER_H

#include "data.h"
#include "byte_istream.h"

/**
 * @brief The BitReader class is an adapter for ByteIstream.
 */
class BitReader {

private:

    ByteIstream& in; /**< Byte read stream. */

    char ch; /**< Current byte. */

    /** Number of read from the current byte bits. */
    Data::SizeType bitCount;

public:

    /**
     * Creates BitReader to adapt specified ByteIstream.
     * @param in - byte read stream.
     */
    BitReader(ByteIstream& in);

    /**
     * @return Next bit from ByteIstream.
     */
    bool read();

};

#endif // BIT_READER_H
