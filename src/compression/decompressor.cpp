#include "decompressor.h"

Decompressor::Decompressor(const Compressed& compressed) :
    bitReader(compressed.data), key(compressed.key) {}

Data Decompressor::decompress() {
    Data decompressed(key.oldByteCount);
    for (int i = 0; i < key.oldByteCount; i++) {
        decompressed[i] = getByte();
    }
    return decompressed;
}

char Decompressor::getByte() {
    auto node = key.root;
    while (!node->isLeaf) {
        bool bit = bitReader.read();
        if (bit) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return node->character;
}
