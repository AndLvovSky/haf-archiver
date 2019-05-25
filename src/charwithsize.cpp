#include "charwithsize.h"
#include <QDebug>
void CharWithSize::push_back(CharWithSize o)
{
    char* c2 = new char[size + o.size];
    memcpy(c2, c, size);
    memcpy(c2 + size, o.c, o.size);
    size += o.size;
    c = c2;
}
