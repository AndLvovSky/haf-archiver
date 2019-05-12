#include "compressed.h"

Compressed::Compressed(const Data& data, const Key& key) :
    data(data), key(key) {}

Compressed::Compressed(const Compressed& other) :
    data(other.data), key(other.key) {}

void Compressed::operator = (const Compressed& other) {
    this->data = other.data;
    this->key = other.key;
}
