#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "key.h"
#include "node.h"
#include "stream/byte_istream.h"
#include "stream/byte_ostream.h"

#include <vector>
#include <QMap>
#include <queue>
#include <QObject>

/**
 * @brief The Compressor class used to compress bytes that are
 * comming from ByteIstream and passes compressed bytes to ByteOstream.
 */
class Compressor : public QObject {

Q_OBJECT

private:

    static const int UPDATE_FREQUENCY = 10000;

    /** Node pointer. */
    typedef std::shared_ptr<Node> NodePtr;

    /** Key pointer. */
    typedef std::shared_ptr<Key> KeyPtr;

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

    KeyPtr key = nullptr;

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
     * Finds Haffman code.
     * @param node - current node in the tree.
     * @param code - accumulated code.
     */
    void findCode(NodePtr node, const QString& code = "");

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
     * Prepares for compressing.
     * @return Created key for the bytes from ByteIstream.
     */
    Key prepare();

    /**
     * Reads bytes from ByteIstream and passes compressed bytes to ByteOstream.
     */
    void compress();

signals:

    void prepared(long long bytes);

    void compressed(long long bytes);

};

#endif // COMPRESSOR_H
