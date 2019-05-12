#ifndef TEST_COMPRESSION_H
#define TEST_COMPRESSION_H

#include <QtTest>

#include "data.h"

class TestCompression : public QObject {

    Q_OBJECT

private:

    Data processData(const Data& data);

    std::string processData(const std::string& text);

public:

    TestCompression();

    ~TestCompression();

private slots:

    void test_small();

};

#endif // TEST_COMPRESSION_H
