#include "data.h"

#include <stdexcept>

Data::Data() : size(0) {}

Data::Data(Data::SizeType size) : size(size) {
    chunks.resize(size);
}

Data::Data(Data::SizeType size, const Data::Chunks& chunks) :
    size(size), chunks(chunks) {}

Data::Data(const Data& other) :
     Data(other.size, other.chunks) {}

Data::Data(const std::string& text) {
    if (text == "") {
        throw std::runtime_error("Text can not be empty!");
    }
    size = text.size();
    chunks.resize(size);
    for (int i = 0; i < size; i++) {
        chunks[i] = text[i];
    }
}

char& Data::operator[](SizeType pos) {
    return chunks[pos];
}

void Data::operator = (const Data& other) {
    this->size = other.size;
    this->chunks = other.chunks;
}

Data::operator std::string () {
    if (!size) {
        return "";
    }
    std::string text(size, ' ');
    for (int i = 0; i < size; i++) {
        text[i] = chunks[i];
    }
    return text;
}
