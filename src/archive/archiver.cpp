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
        QString filePath = filesToArchiveUris[i];
        emit progress("start compressing: " + filePath);

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
        emit progress("start preparing " + filePath);
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.completeBaseName().append('.')
                .append(fileInfo.completeSuffix());
        QString fileBirthTime = fileInfo.birthTime().toString(Qt::ISODate);
        int fileSize = fileInfo.size();
        auto in = std::make_shared<ByteInputStream>(filePath);
        inputStreams.push_back(in);
        compressors.push_back(Compressor(*in, out));
        Key key = compressors.back().prepare();
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

void Archiver::compressAndWrite(Key key, Compressor compressor)
{
    int compressedSize = key.bitCount / 8;
    if (key.bitCount % 8 != 0) compressedSize++;
    out.writeInt(compressedSize);
    if(compressedSize != 0) compressor.compress();
}
