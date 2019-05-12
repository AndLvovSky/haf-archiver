#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "data.h"
#include "node.h"
#include "compressed.h"

#include <vector>
#include <QMap>
#include <queue>

class Compressor {

private:

    typedef std::shared_ptr<Node> NodePtr;

    struct Comparator {

        bool operator () (NodePtr a, NodePtr b);

    };

    Data data;

    bool isEmpty;

    std::priority_queue<NodePtr, std::vector<NodePtr>, Comparator> heap;

    QMap<char, int> frequencies;

    QMap<char, QString> haffmanCode;

    void findFrequencies();

    Key createKey();

    void findCode(NodePtr node, const QString& code = "");

    Data __compress(const Key& key);

    Data::SizeType findBitCount();

public:

    Compressor(const Data& data);

    Compressed compress();

};

#endif // COMPRESSOR_H
