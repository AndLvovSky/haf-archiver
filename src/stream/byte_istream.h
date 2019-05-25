#ifndef BYTE_ISTREAM_H
#define BYTE_ISTREAM_H

#include "util/data.h"

/**
 * @brief The ByteIstream interface determines classes, that
 * read bytes from a source and pass them one by one.
 *
 * The ByteIstream is a bridge between the source to compress and Compressor.
 */
struct ByteIstream {

    /**
     * Starts passing bytes from the begin of the source.
     */
    virtual void reset() = 0;

    /**
     * @return Next byte in the source.
     */
    virtual char getByte() = 0;

    /**
     * @return Number of bytes in the source.
     */
    virtual Data::SizeType byteCount() const = 0;

};

#endif // BYTE_ISTREAM_H
