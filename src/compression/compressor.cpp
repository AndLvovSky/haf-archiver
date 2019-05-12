#include "compressor.h"
#include "bit_writer.h"

#include <QDebug>
#include <QMap>

Compressor::Compressor(const Data& data) :
    data(data), isEmpty(false) {
    qInfo() << "old bit count = " << data.size * 8;
    qInfo() << "old byte count = " << data.size;
}

bool Compressor::Comparator::operator () (Node::NodePtr a, Node::NodePtr b) {
    return a->weight > b->weight;
}

Compressed Compressor::compress() {
    if (isEmpty) {
        throw std::runtime_error("Compress can be used only once!");
    }
    Key key = createKey();
    Data data = __compress(key);
    isEmpty = true;
    return Compressed(data, key);
}

void Compressor::findFrequencies() {
    for (int i = 0; i < data.size; i++) {
        frequencies[data[i]]++;
    }
}

Key Compressor::createKey() {
    findFrequencies();
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
    return Key(heap.top(), data.size, findBitCount());
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

Data Compressor::__compress(const Key& key) {
    auto byteCount = key.bitCount / 8 +
        (key.bitCount % 8 ? 1 : 0);
    qInfo() << "new bit count = " << key.bitCount;
    qInfo() << "new byte count = " << byteCount;
    auto compressedData = Data(byteCount);
    BitWriter bitWriter(compressedData);
    for (int i = 0; i < data.size; i++) {
        for (auto ch: haffmanCode[data[i]]) {
            bitWriter.write(ch == '1');
        }
    }
    return compressedData;
}

Data::SizeType Compressor::findBitCount() {
    auto res = 0;
    for (int i = 0; i < data.size; i++) {
        res += haffmanCode[data[i]].size();
    }
    return res;
}
