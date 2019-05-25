#ifndef KEY_H
#define KEY_H

#include "util/data.h"
#include "node.h"
#include <QString>
#include <QStringList>
#include "util/charwithsize.h"

/**
 * @brief The Key class contains information, that allows to
 * decompress file, compressed by Compressor.
 */
class Key {
    public:

    friend class Compressor;

    friend class Decompressor;

    static Key fromString(QString s);

    Node::NodePtr root; /**< Root of the Haffman tree. */

    /** Number of not compressed bytes. */
    Data::SizeType oldByteCount;

    /** Number of bits in compressed bytes. */
    Data::SizeType bitCount;

    /**
     * Key constructor.
     * @param root - root of the Haffman tree.
     * @param oldByteCount - number of not compressed bytes.
     * @param bitCount - number of bits in compressed bytes.
     */
    Key(Node::NodePtr root,
        Data::SizeType oldByteCount, Data::SizeType bitCount);

    QString toString();

    CharWithSize serialize();
    static Key deserialize(CharWithSize c);

private:
    QString stringOf(Node::NodePtr node);

    CharWithSize serialize(Node::NodePtr);
    static std::vector<char*> nodes;
    static Node::NodePtr deserialize2();

    static Node::NodePtr deserialize();
    static QStringList nodesParts;
    static int nodesCounter;
};

#endif // KEY_H
