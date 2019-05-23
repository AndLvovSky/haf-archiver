#ifndef BYTE_OSTREAM_H
#define BYTE_OSTREAM_H

/**
 * @brief The ByteOstream interface determines classes, that
 * put bytes to an output.
 *
 * The ByteOstream is a bridge between Decompressor and the output object.
 */
struct ByteOstream {

    /**
     * Puts specified byte to the output.
     */
    virtual void putByte(char byte) = 0;

};

#endif // BYTE_OSTREAM_H
