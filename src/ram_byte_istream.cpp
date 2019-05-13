#include "ram_byte_istream.h"

#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <stdexcept>

RamByteIstream::RamByteIstream(std::string s, bool isFile) :
    byteNumber(0) {
    if (isFile) {
        QFile inputFile(QString::fromStdString(s));
        if (inputFile.open(QIODevice::ReadOnly)) {
            QByteArray byteArray = inputFile.readAll();
            data = Data(byteArray.size());
            for (int i = 0; i < byteArray.size(); i++) {
                data[i] = byteArray[i];
            }
            inputFile.close();
        } else {
            throw std::runtime_error("Can not open file!");
        }
    } else {
        data = Data(s);
    }
}

void RamByteIstream::reset() {
    this->byteNumber =  0;
}

char RamByteIstream::getByte() {
    if (byteNumber >= data.size) {
        throw std::runtime_error("File is empty!");
    }
    auto res = data[byteNumber];
    byteNumber++;
    return res;
}

Data::SizeType RamByteIstream::byteCount() const {
    return this->data.size;
}
