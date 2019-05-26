#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include "stream/byte_istream.h"
#include "stream/byte_ostream.h"
#include "bit_reader.h"
#include "key.h"
#include <QObject>

/**
 * @brief The Decompressor class used to decompress bytes that are
 * comming from ByteIstream using specified key and
 * passes decompressed bytes to ByteOstream.
 */
class Decompressor : public QObject {

Q_OBJECT

private:

    static const int UPDATE_FREQUENCY = 10000;

    ByteIstream& in; /**< Bytes reading stream */

    ByteOstream& out; /**< Bytes writing stream. */

    Key key; /**< Key for decompression. */

    BitReader bitReader; /**< BitReader for 'in' ByteStream. */

    /**
     * @return Next decompressed byte.
     */
    char getByte();

public:

    /**
     * Create Decompressor with specified read and write streams,
     * and key for decompression.
     * @param in - read byte stream.
     * @param out - write byte stream.
     * @param key - key returned from Compressor after compress.
     */
    Decompressor(ByteIstream& in, ByteOstream& out, const Key& key);

    /**
     * Reads bytes from ByteIstream and passes decompressed
     * bytes to ByteOstream.
     */
    void decompress();

signals:

    void decompressed(long long bytes);

};

#endif // DECOMPRESSOR_H
