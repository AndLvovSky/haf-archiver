#include "decompressor.h"
#include <QDebug>

Decompressor::Decompressor(ByteIstream& in, ByteOstream& out,
    const Key& key) : in(in), out(out), key(key), bitReader(BitReader(in)) {}

void Decompressor::decompress() {
    in.reset();
    for (int i = 0; i < key.oldByteCount; i++) {
        char ch = getByte();
        out.putByte(ch);
    }
}

char Decompressor::getByte() {
    auto node = key.root;
    while (node && !node->isLeaf) {
        bool bit = bitReader.read();
        if (bit) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (!node) {
        throw std::runtime_error("Wrong key in Decompressor::getByte");
    }
    return node->character;
}
