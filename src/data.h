#ifndef DATA_H
#define DATA_H

#include <memory>

struct Data {

    std::unique_ptr<char[]> chunks;

    Data(std::unique_ptr<char[]> chunks);

};

#endif // DATA_H
