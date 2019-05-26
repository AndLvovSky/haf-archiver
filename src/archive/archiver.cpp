#include "archiver.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include "stream/std/byteoutputstream.h"
#include "stream/std/byteinputstream.h"
#include <QDir>
#include "compression/compressor.h"
#include "compression/key.h"

Archiver::Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName)
    : filesToArchiveUris(filesToArchiveUris),
      out(destDir.append('/').append(destFileName).append(".haf"),
          ByteOutputStream::WRITE_NEW)
{

}

void Archiver::process()
{
    emit progress("preparing archiving");
    writeFilesInfo();
    emit progress("process archiving");

    for (int i = 0; i < filesToArchiveUris.size(); i++) {
        filePath = filesToArchiveUris[i];
        fileSize = savedFileSizes[i];
        emit progress("compressing: " + filePath);

        writeKey(savedKeys[i]);
        compressAndWrite(savedKeys[i], compressors[i]);

        inputStreams[i]->close();
        emit progress("finish compressing: " + filePath);
    }

    out.close();
    emit progress("finish archiving");
}

void Archiver::writeFilesInfo()
{
    out.writeInt(filesToArchiveUris.size());

    for (QString filePath: filesToArchiveUris) {
        this->filePath = filePath;
        emit progress("preparing " + filePath);
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.completeBaseName().append('.')
                .append(fileInfo.completeSuffix());
        QString fileBirthTime = fileInfo.birthTime().toString(Qt::ISODate);
        fileSize = fileInfo.size();
        savedFileSizes.push_back(fileSize);
        auto in = std::make_shared<ByteInputStream>(filePath);
        inputStreams.push_back(in);
        auto compressor = std::make_shared<Compressor>(*in, out);
        compressors.push_back(compressor);
        connect(compressor.get(), SIGNAL(prepared(long long)), this, SLOT(onPreparedChange(long long)));
        connect(compressor.get(), SIGNAL(compressed(long long)), this, SLOT(onCompressedChange(long long)));
        Key key = compressor->prepare();
        savedKeys.push_back(key);
        int compressedSize = key.bitCount / 8;

        writeStringSizeAndString(fileName);
        writeStringSizeAndString(fileBirthTime);
        out.writeInt(fileSize);
        out.writeInt(compressedSize);
        emit progress("finish preparing " + filePath);
    }
}

void Archiver::writeStringSizeAndString(QString s)
{
    out.writeInt(s.size());
    out.writeString(s);
}

void Archiver::writeKey(Key key)
{
    CharWithSize keyS = key.serialize();
    out.writeInt(keyS.size);
    out.writeData(keyS.c, keyS.size);
    delete [] keyS.c;
}

void Archiver::compressAndWrite(Key key, std::shared_ptr<Compressor> compressor)
{
    int compressedSize = key.bitCount / 8;
    if (key.bitCount % 8 != 0) compressedSize++;
    out.writeInt(compressedSize);
    if(compressedSize != 0) compressor->compress();
}

void Archiver::onPreparedChange(long long bytes) {
    emit progressInLine("preparing " +
        QString::number(bytes) + "/" + QString::number(fileSize) +
        " " + filePath, 0);
}

void Archiver::onCompressedChange(long long bytes) {
    emit progressInLine("compressing " +
        QString::number(bytes) + "/" + QString::number(fileSize) +
        " " + filePath, 0);
}
