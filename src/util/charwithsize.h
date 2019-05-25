#ifndef CHARWITHSIZE_H
#define CHARWITHSIZE_H


class CharWithSize
{
public:
    char* c;
    int size = 0;

    CharWithSize(){}

    void push_back(CharWithSize o);
};

#endif // CHARWITHSIZE_H
