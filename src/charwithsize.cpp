#include "charwithsize.h"
#include <QDebug>
void CharWithSize::push_back(CharWithSize o)
{
    char* c2 = new char[size + o.size];

    //copy c into c2
    for (int i = 0; i < size; i++) {
        c2[i] = c[i];
    }

    //copy o.c into c2
    for (int i = 0; i < o.size; i++) {
        c2[i + size] = o.c[i];
    }

    size += o.size;
    c = c2;
}
