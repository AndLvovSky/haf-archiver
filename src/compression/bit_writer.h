#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include "util/data.h"
#include "stream/byte_ostream.h"

/**
 * @brief The BitWriter class is an adapter for ByteOstream.
 */
class BitWriter {

private:

    ByteOstream& out; /**< Byte write stream. */

    char ch; /**< Current byte */

    /**< Number of bits, written to current byte. */
    Data::SizeType bitCount;

public:

    /**
     * Creates BitWriter to adapt specified ByteOstream.
     * @param in - byte write stream.
     */
    BitWriter(ByteOstream& out);

    /**
     * Writes specified bit to ByteOstream.
     */
    void write(bool bit);

    /**
     * Forces to writing the last byte to ByteOstream.
     */
    void flush();

};

#endif // BIT_WRITER_H
