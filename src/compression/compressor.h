#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "key.h"
#include "node.h"
#include "byte_istream.h"
#include "byte_ostream.h"

#include <vector>
#include <QMap>
#include <queue>

/**
 * @brief The Compressor class used to compress bytes that are
 * comming from ByteIstream and passes compressed bytes to ByteOstream.
 */
class Compressor {

private:

    /** Node pointer type. */
    typedef std::shared_ptr<Node> NodePtr;

    /**
     * @brief The Comparator class used to compare nodes.
     */
    struct Comparator {

        /**
         * Compares two nodes.
         */
        bool operator () (NodePtr a, NodePtr b);

    };

    ByteIstream& in; /**< Bytes reading stream. */

    ByteOstream& out; /**< Bytes writing stream. */

    /** Heap for Haffman algorithm. */
    std::priority_queue<NodePtr, std::vector<NodePtr>, Comparator> heap;

    /** Frequencies of each character. */
    QMap<char, int> frequencies;

    /** Haffman code. */
    QMap<char, QString> haffmanCode;

    /**
     * Finds frequencies of each character.
     */
    void findFrequencies();

    /**
     * @return Created key for the bytes from ByteIstream.
     */
    Key createKey();

    /**
     * Finds Haffman code.
     * @param node - current node in the tree.
     * @param code - accumulated code.
     */
    void findCode(NodePtr node, const QString& code = "");

    /**
     * Passes compressed bytes to ByteOstream.
     * @param key - optional current key for statistics.
     */
    void __compress(const Key& key);

    /**
     * @return Number of bits in compressed bytes.
     */
    Data::SizeType findBitCount();

public:

    /**
     * Creates compressor with specified read and write streams.
     * @param in - read byte stream.
     * @param out - write byte stream.
     */
    Compressor(ByteIstream& in, ByteOstream& out);

    /**
     * Reads bytes from ByteIstream and passes compressed
     * bytes to ByteOstream.
     * @return Key for decompression with some statistics.
     */
    Key compress();

};

#endif // COMPRESSOR_H
