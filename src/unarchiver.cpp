#include "unarchiver.h"
#include "byteoutputstream.h"
#include <QDebug>
#include <QDateTime>
#include "compression/key.h"
#include "compression/decompressor.h"

using namespace std;

Unarchiver::Unarchiver(QString archivePath, QString outputDirPath)
    :outputDirPath(outputDirPath), in(archivePath)
{
    readInfo();
}

void Unarchiver::process(){
    for (auto fileInfo: info.filesInfo) {
        qInfo() << "Unarchiver: processing" << fileInfo.name;
        QByteArray keyS = readByteArrayLengthAndByteArray();
        qInfo() << QString::fromStdString(keyS.toStdString());
        Key key = Key::fromString(QString::fromStdString(keyS.toStdString()));
        // serialization and deserialization are seem to be correct
        qInfo() << key.toString();

        // reading compressed data size and setting up the archive stream
        int dataSize = in.readInt();
        bytesCounter += 4;
        in.setFileSize(dataSize);
        in.setResetOffset(bytesCounter);
        qInfo() << "dataSize: " << dataSize;

        QString filePath = outputDirPath;
        filePath.append('/').append(fileInfo.name);
        ByteOutputStream out(filePath, ByteOutputStream::WRITE_NEW);
        Decompressor decompressor(in, out, key);
        decompressor.decompress();
        qInfo() << "unarchived " + fileInfo.name + " successfully!";
        out.close();
    }
}

ArchiveInfo Unarchiver::getInfo()
{
    return info;
}

QString Unarchiver::readStringLengthAndString()
{
    int length = in.readInt();
    // 4 is the int's bytesize
    bytesCounter += length + 4;
    return QString::fromStdString(string(in.read(length))).mid(0, length);
}

QByteArray Unarchiver::readByteArrayLengthAndByteArray()
{
    int length = in.readInt();
    bytesCounter += length + 4;
    return in.readByteArray(length);
}

void Unarchiver::readInfo()
{
    int filesCount = in.readInt();
    bytesCounter += 4;

    for (int i = 0; i < filesCount; i++) {
        FileInfo fileInfo;
        fileInfo.name = readStringLengthAndString();
        fileInfo.birthTime = QDateTime::fromString(readStringLengthAndString());
        info.filesInfo.push_back(fileInfo);
    }
}

