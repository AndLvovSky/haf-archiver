#include "archiver.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include "byteoutputstream.h"
#include "byteinputstream.h"
#include <QDir>
#include "compression/compressor.h"
#include "compression/key.h"

void Archiver::writeToArchiveStream(QString s)
{
    for (auto c: s) {
        archiveStream->putByte(c.toLatin1());
    }
}

Archiver::Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName)
    : filesToArchiveUris(filesToArchiveUris), destDir(destDir), destFileName(destFileName)
{

}

void Archiver::process()
{
    QByteArray byteArray;
    int numberOfFiles = filesToArchiveUris.size();
    byteArray.append(QString::number(numberOfFiles));
    byteArray.append('/');
    vector<unique_ptr<QFile>> files;
    for (QString filePath: filesToArchiveUris) {
        unique_ptr<QFile> file = make_unique<QFile>(filePath);
        files.push_back(move(file));
        QFileInfo info(filePath);
        byteArray.append(info.completeBaseName()).append('.').append(info.completeSuffix()).append('/');
        byteArray.append(info.birthTime().toString()).append('/');
    }

    QString archivePath = destDir.append('/').append(destFileName).append(".haf");
    //qInfo() << archivePath;
    archiveStream = make_unique<ByteOutputStream>(archivePath.toStdString(), ByteOutputStream::WRITE_NEW);
    writeToArchiveStream(QString(byteArray));


    for (QString filePath: filesToArchiveUris) {
        ByteInputStream fileStream(filePath.toStdString());
        Compressor compressor(fileStream, *archiveStream);

        Key key = (fileStream.byteCount() == 0) ? Key(nullptr, 0, 0) : compressor.prepare();
        //qInfo() << "compression prepared";
        QString keyS = key.toString();
        //qInfo() << keyS;
        writeToArchiveStream(QString::number(keyS.size()));
        archiveStream->putByte('/');
        writeToArchiveStream(keyS);
        //qInfo() << "Key: " << keyS;

        int compressedSize = key.bitCount / 8;
        if (key.bitCount % 8 != 0) compressedSize++;
        writeToArchiveStream(QString::number(compressedSize));
        archiveStream->putByte('/');

        if (fileStream.byteCount() != 0) {
            compressor.compress();
        }
    }

    archiveStream->close();
}
