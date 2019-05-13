#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "key.h"
#include "node.h"
#include "byte_istream.h"
#include "byte_ostream.h"

#include <vector>
#include <QMap>
#include <queue>

class Compressor {

private:

    typedef std::shared_ptr<Node> NodePtr;

    struct Comparator {

        bool operator () (NodePtr a, NodePtr b);

    };

    ByteIstream& in;

    ByteOstream& out;

    std::priority_queue<NodePtr, std::vector<NodePtr>, Comparator> heap;

    QMap<char, int> frequencies;

    QMap<char, QString> haffmanCode;

    void findFrequencies();

    Key createKey();

    void findCode(NodePtr node, const QString& code = "");

    void __compress(const Key& key);

    Data::SizeType findBitCount();

public:

    Compressor(ByteIstream& in, ByteOstream& out);

    Key compress();

};

#endif // COMPRESSOR_H
