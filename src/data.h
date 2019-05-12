#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct Data {

    typedef unsigned int SizeType;

    typedef std::vector<char> Chunks;

    SizeType size;

    Chunks chunks;

    Data();

    Data(const Data& data);

    Data(const std::string& text);

    Data(SizeType size);

    Data(SizeType size, const Chunks& chunks);

    ~Data() = default;

    char& operator [] (SizeType pos);

    void operator = (const Data& data);

    operator std::string ();

};

#endif // DATA_H
