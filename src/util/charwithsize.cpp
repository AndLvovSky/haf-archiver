#include "charwithsize.h"
#include <QDebug>
void CharWithSize::push_back(CharWithSize o)
{
    if (o.c == nullptr) {
        throw std::runtime_error("CharWithSize c is null in push_back");
    }
    char* c2 = new char[size + o.size];
    memcpy(c2, c, size);
    memcpy(c2 + size, o.c, o.size);
    size += o.size;
    delete[] c;
    delete[] o.c;
    c = c2;
}
