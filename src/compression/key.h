#ifndef KEY_H
#define KEY_H

#include "data.h"
#include "node.h"

class Key {

    friend class Compressor;

    friend class Decompressor;

    Node::NodePtr root;

    Data::SizeType oldByteCount;

    Data::SizeType bitCount;

    Key(Node::NodePtr root,
        Data::SizeType oldByteCount, Data::SizeType bitCount);

};

#endif // KEY_H
