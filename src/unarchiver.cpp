#include "unarchiver.h"
#include "byteoutputstream.h"
#include <QDebug>
#include <QDateTime>
#include "compression/key.h"
#include "compression/decompressor.h"

using namespace std;

Unarchiver::Unarchiver(QString archivePath, QString outputDirPath)
    :archivePath(archivePath), outputDirPath(outputDirPath),
     archiveStream(make_unique<ByteInputStream>(archivePath.toStdString()))
{
    QByteArray byteArray;

    char c;
    while((c = archiveStream->getByte()) != '/') {
        byteArray.append(c);
        bytesCounter++;
    }
    bytesCounter++;
    int filesNumber = byteArray.toInt();
    byteArray.clear();

    for (int i = 0; i < filesNumber; i++) {
        FileInfo fileInfo;

        while((c = archiveStream->getByte()) != '/') {
            byteArray.append(c);
            bytesCounter++;
        }
        bytesCounter++;
        fileInfo.name = byteArray;
        byteArray.clear();

        while((c = archiveStream->getByte()) != '/') {
            byteArray.append(c);
            bytesCounter++;
        }
        bytesCounter++;
        fileInfo.birthTime = QDateTime::fromString(byteArray);
        byteArray.clear();

        info.filesInfo.push_back(fileInfo);
    }
}

void Unarchiver::process(){
    for (auto fileInfo: info.filesInfo) {
        qInfo() << "Unarchiver: processing" << fileInfo.name;
        QString fileName = fileInfo.name;

        // read key size
        QByteArray byteArray;
        char c;
        while((c = archiveStream->getByte()) != '/') {
            byteArray.append(c);
            bytesCounter++;
        }
        bytesCounter++;
        int keySize = byteArray.toInt();
        byteArray.clear();

        //read key
        for (int i = 0; i < keySize; i++) {
            byteArray.append(archiveStream->getByte());
            bytesCounter++;
        }
        //qInfo() <<"Key: "<< byteArray;
        //qInfo() << byteArray.size();
        Key key = Key::fromString(QString::fromStdString(byteArray.toStdString()));
//        qInfo() << byteArray;
//        qInfo() << key.toString();

        // read data size
        byteArray.clear();
        while((c = archiveStream->getByte()) != '/') {
            byteArray.append(c);
            bytesCounter++;
        }
        bytesCounter++;
        int dataSize = byteArray.toInt();
        byteArray.clear();

        //decompress data
        QString filePath = outputDirPath;
        filePath.append('/').append(fileName);
        ByteOutputStream ostream(filePath.toStdString(), ByteOutputStream::WRITE_NEW);

        archiveStream->setFileSize(dataSize);
        archiveStream->setResetOffset(bytesCounter);
        QByteArray testBytes;
        /*qInfo() << "Compressed data size: " << dataSize;
        for (int i = 0; i < dataSize; i++) {
            char c = archiveStream->getByte();
            testBytes.append(c);
        }
        qInfo() << "Compressed data: " << testBytes;*/
        archiveStream->reset();



        Decompressor decompressor(*archiveStream.get(), ostream, key);
        decompressor.decompress();
        //qInfo() << "unarchived " + fileName + " successfully!";
        ostream.close();
        bytesCounter += dataSize;
    }
}

ArchiveInfo Unarchiver::getInfo()
{
    return info;
}

