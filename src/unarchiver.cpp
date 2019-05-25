#include "unarchiver.h"
#include "byteoutputstream.h"
#include <QDebug>
#include <QDateTime>
#include "compression/key.h"
#include "compression/decompressor.h"
#include "charwithsize.h"

using namespace std;

Unarchiver::Unarchiver(QString archivePath, QString outputDirPath)
    :outputDirPath(outputDirPath), in(archivePath)
{
    readInfo();
}

void Unarchiver::process(){
    for (auto fileInfo: info.filesInfo) {
        qInfo() << "Unarchiver: processing" << fileInfo.name;
        Key key = Key::deserialize(getKey(in));

        // reading compressed data size and setting up the archive stream
        int dataSize = in.readInt();
        bytesCounter += sizeof(int);
        in.setFileSize(dataSize);
        in.setResetOffset(bytesCounter);

        QString filePath = outputDirPath;
        filePath.append('/').append(fileInfo.name);
        ByteOutputStream out(filePath, ByteOutputStream::WRITE_NEW);
        Decompressor decompressor(in, out, key);
        decompressor.decompress();
        bytesCounter += dataSize;
        qInfo() << "unarchived " + fileInfo.name + " successfully!";
        out.close();
    }
    in.close();
}

ArchiveInfo Unarchiver::getInfo()
{
    return info;
}

QString Unarchiver::readStringLengthAndString()
{
    int length = in.readInt();
    bytesCounter += length + sizeof(int);
    return QString::fromStdString(string(in.read(length))).mid(0, length);
}

QByteArray Unarchiver::readByteArrayLengthAndByteArray()
{
    int length = in.readInt();
    bytesCounter += length + sizeof(int);
    return in.readByteArray(length);
}

void Unarchiver::readInfo()
{
    int filesCount = in.readInt();
    bytesCounter += sizeof(int);

    for (int i = 0; i < filesCount; i++) {
        FileInfo fileInfo;
        fileInfo.name = readStringLengthAndString();
        fileInfo.birthTime = QDateTime::fromString(readStringLengthAndString());
        fileInfo.originalSize = in.readInt();
        bytesCounter += sizeof(int);
        fileInfo.compressedSize = in.readInt();
        bytesCounter += sizeof(int);
        info.filesInfo.push_back(fileInfo);
    }
}

CharWithSize Unarchiver::getKey(ByteInputStream &in)
{
    int keyLength = in.readInt();
    bytesCounter += sizeof(int);
    CharWithSize keyC;
    keyC.size = keyLength;
    keyC.c = in.read(keyLength);
    bytesCounter += keyLength;
    return keyC;
}

