#include "test_compression.h"
#include "compression/compressor.h"
#include "compression/decompressor.h"
#include "ram_byte_istream.h"
#include "ram_byte_ostream.h"

TestCompression::TestCompression() {}

TestCompression::~TestCompression() {}

std::string TestCompression::processString(const std::string& text) {
    if (text.size() > 80) {
        qInfo((text.substr(0, 80) + "...").c_str());
    } else {
        qInfo(text.c_str());
    }

    RamByteIstream in1(text);
    RamByteOstream out1;
    Compressor compressor(in1, out1);
    Key key = compressor.prepare();
    compressor.compress();
    Data compressedData = out1.getData();

    RamByteIstream in2(compressedData);
    RamByteOstream out2;
    Decompressor decompressor(in2, out2, key);
    decompressor.decompress();
    Data decompressedData = out2.getData();

    return decompressedData;
}

bool TestCompression::checkFile(QString fileName) {
    qInfo() << fileName;
    RamByteIstream in1((":/files/" + fileName).toStdString(), true);
    RamByteOstream out1;
    Compressor compressor(in1, out1);
    Key key = compressor.prepare();
    compressor.compress();
    Data compressedData = out1.getData();

    RamByteIstream in2(compressedData);
    RamByteOstream out2;
    Decompressor decompressor(in2, out2, key);
    decompressor.decompress();
    Data decompressedData = out2.getData();

    if (in1.byteCount() != decompressedData.size) {
        return false;
    }
    in1.reset();
    for (int i = 0; i < in1.byteCount(); i++) {
        char in1Char = in1.getByte();
        if (in1Char != decompressedData[i]) {
            return false;
        }
    }
    return true;
}

void TestCompression::test_small() {
    try {
        QVERIFY(processString("f") == "f");
        QVERIFY(processString("4") == "4");
        QVERIFY(processString("*") == "*");
        QVERIFY(processString(" ") == " ");

        QVERIFY(processString("bc") == "bc");
        QVERIFY(processString("jj") == "jj");
        QVERIFY(processString("3t") == "3t");
        QVERIFY(processString("*h") == "*h");

        QVERIFY(processString("bc ") == "bc ");
        QVERIFY(processString("5g&") == "5g&");
        QVERIFY(processString("krk") == "krk");
    } catch(std::runtime_error err) {
        qInfo(err.what());
    }
}

void TestCompression::test_medium() {
    std::string s;
    try {
        s = "beep boop beer!";
        QVERIFY(processString(s) == s);
        s = "Lorem ipsum dolor sit amet";
        QVERIFY(processString(s) == s);
        s = "Cras sit amet cursus mauris";
        QVERIFY(processString(s) == s);
        s = " Nunc sodales, ex vel congue aliquam";
        QVERIFY(processString(s) == s);
        s = "Integer elementum mattis neque, eu hendrerit purus congue pharetra.";
        QVERIFY(processString(s) == s);
    } catch (std::runtime_error err) {
        qInfo(err.what());
    }
}

void TestCompression::test_big() {
    const QVector<QString> fileNames = {
        "text/common_words.txt",
        "text/english_text.txt",
        "text/log_ssh.log",
        "text/google.html",
        "bin/console_app.exe",
        "bin/qt_lib.dll",
        "images/black-white.jpg",
        "images/nature.jpg",
        "images/sample.BMP",
        "other/laboratory.pdf",
        "other/sociology.docx"
    };
    std::string s;
    try {
        for (const auto& fileName : fileNames) {
            QVERIFY(checkFile(fileName));
        }
    } catch (std::runtime_error err) {
        qInfo(err.what());
    }
}
