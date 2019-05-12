#include "test_compression.h"
#include "compression/compressor.h"
#include "compression/decompressor.h"

TestCompression::TestCompression() {}

TestCompression::~TestCompression() {}

Data TestCompression::processData(const Data& data) {
    //qInfo("begin processing");
    Compressor compressor(data);
    //qInfo("created compressor");
    Compressed compressed = compressor.compress();
    //qInfo("compressed");
    Decompressor decompressor(compressed);
    //qInfo("created decompressor");
    Data processedData = decompressor.decompress();
    //qInfo("decompressed");
    //qInfo("finish processing");
    return processedData;
}

std::string TestCompression::processData(const std::string& text) {
    qInfo(text.c_str());
    return processData(Data(text));
}

void TestCompression::test_small() {
    try {
        QVERIFY(processData("f") == "f");
        QVERIFY(processData("4") == "4");
        QVERIFY(processData("*") == "*");
        QVERIFY(processData(" ") == " ");

        QVERIFY(processData("bc") == "bc");
        QVERIFY(processData("jj") == "jj");
        QVERIFY(processData("3t") == "3t");
        QVERIFY(processData("*h") == "*h");

        QVERIFY(processData("bc ") == "bc ");
        QVERIFY(processData("5g&") == "5g&");
        QVERIFY(processData("krk") == "krk");
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}
