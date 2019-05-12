#ifndef COMPRESSED_H
#define COMPRESSED_H

#include "data.h"
#include "key.h"

struct Compressed {

    Data data;
    Key key;

    Compressed(const Data& data, const Key& key);

    Compressed(const Compressed& other);

    void operator = (const Compressed& other);

};

#endif // COMPRESSED_H
