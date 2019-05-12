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

std::string TestCompression::processData(
    const std::string& text, bool print) {
    if (print) {
        if (text.size() > 80) {
            qInfo((text.substr(0, 80) + "...").c_str());
        } else {
            qInfo(text.c_str());
        }
    }
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

void TestCompression::test_medium() {
    std::string s;
    try {
        s = "beep boop beer!";
        QVERIFY(processData(s) == s);
        s = "Lorem ipsum dolor sit amet";
        QVERIFY(processData(s) == s);
        s = "Cras sit amet cursus mauris";
        QVERIFY(processData(s) == s);
        s = " Nunc sodales, ex vel congue aliquam";
        QVERIFY(processData(s) == s);
        s = "Integer elementum mattis neque, eu hendrerit purus congue pharetra.";
        QVERIFY(processData(s) == s);
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
            s = readFromFile(fileName);
            qInfo() << fileName;
            QVERIFY(processData(s, false) == s);
        }
    } catch (std::runtime_error err) {
        qInfo(err.what());
    }
}

std::string TestCompression::readFromFile(QString testFileName, bool binMode) {
    QFile inputFile(":/files/" + testFileName);
    if (inputFile.open(QIODevice::ReadOnly)) {
        std::string res = "";
        if (binMode) {
             QByteArray byteArray = inputFile.readAll();
             for (int i = 0; i < byteArray.size(); i++) {
                 res += byteArray[i];
             }
        } else {
            QTextStream fin(&inputFile);
            while (!fin.atEnd())
            {
              QString line = fin.readLine();
              res += line.toStdString() + '\n';
            }
        }
        inputFile.close();
        return res;
    } else {
        return "";
    }
}
