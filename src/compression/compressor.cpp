#include "compressor.h"
#include "bit_writer.h"

#include <QDebug>
#include <QMap>
#include <cmath>

Compressor::Compressor(ByteIstream& in, ByteOstream& out) :
    in(in), out(out) {
    qInfo() << "old bit count = " << in.byteCount() * 8;
    qInfo() << "old byte count = " << in.byteCount();
}

bool Compressor::Comparator::operator () (Node::NodePtr a, Node::NodePtr b) {
    return a->weight > b->weight;
}

void Compressor::findFrequencies() {
    in.reset();
    for (int i = 0; i < in.byteCount(); i++) {
        char ch = in.getByte();
        frequencies[ch]++;
    }
}

Key Compressor::prepare() {
    findFrequencies();
    if (frequencies.empty()) {
        return Key(nullptr, 0, 0);
    }
    for (const auto& it : frequencies.toStdMap()) {
        heap.push(std::make_shared<Node>(
            it.second, it.first, nullptr, nullptr, true));
    }
    if (heap.size() == 1) {
        NodePtr top = heap.top();
        heap.pop();
        heap.push(std::make_shared<Node>(
            top->weight, 0, top, nullptr));
    }
    while (heap.size() != 1) {
        NodePtr first, second;
        first = heap.top();
        heap.pop();
        second = heap.top();
        heap.pop();
        heap.push(std::make_shared<Node>(
            first->weight + second->weight, 0, first, second));
    }
    findCode(heap.top());
    key = std::make_shared<Key>(heap.top(), in.byteCount(), findBitCount());
    return *key;
}

void Compressor::findCode(Node::NodePtr node, const QString& code) {
    if (node == nullptr) {
        return;
    }
    if (node->isLeaf) {
        haffmanCode[node->character] = code;
        return;
    }
    findCode(node->left, code + "0");
    findCode(node->right, code + "1");
}

void Compressor::compress() {
    if (key == nullptr) {
        throw std::runtime_error("Compressing is not prepared!");
    }
    if (frequencies.empty()) {
        qInfo() << "new bit count = " << 0;
        qInfo() << "new byte count = " << 0;
        qInfo() << "compression ratio(%) = " << 0;
        return;
    }
    auto byteCount = key->bitCount / 8 +
        (key->bitCount % 8 ? 1 : 0);
    qInfo() << "new bit count = " << key->bitCount;
    qInfo() << "new byte count = " << byteCount;
    qInfo() << "compression ratio(%) = " <<
        std::round((in.byteCount() - byteCount) /
        (float)in.byteCount() * 10000) / 100;
    in.reset();
    BitWriter bitWriter(out);
    for (int i = 0; i < in.byteCount(); i++) {
        char ch = in.getByte();
        for (auto ch: haffmanCode[ch]) {
            bitWriter.write(ch == '1');
        }
    }
    bitWriter.flush();
}

Data::SizeType Compressor::findBitCount() {
    in.reset();
    auto res = 0;
    for (int i = 0; i < in.byteCount(); i++) {
        char ch = in.getByte();
        res += haffmanCode[ch].size();
    }
    return res;
}
