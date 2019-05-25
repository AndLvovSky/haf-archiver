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

Archiver::Archiver(QStringList filesToArchiveUris, QString destDir, QString destFileName)
    : filesToArchiveUris(filesToArchiveUris),
      out(destDir.append('/').append(destFileName).append(".haf"),
          ByteOutputStream::WRITE_NEW)
{

}

void Archiver::process()
{
    writeFilesInfo();

    for (QString filePath: filesToArchiveUris) {
        ByteInputStream in(filePath);
        Compressor compressor(in, out);

        // compressor crashes if file size is 0
        Key key = (in.byteCount() == 0) ? Key(nullptr, 0, 0) : compressor.prepare();
        writeKey(key);
        compressAndWrite(key, compressor);

        in.close();
    }

    out.close();
}

void Archiver::writeFilesInfo()
{
    out.writeInt(filesToArchiveUris.size());

    for (QString filePath: filesToArchiveUris) {
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.completeBaseName().append('.')
                .append(fileInfo.completeSuffix());
        QString fileBirthTime = fileInfo.birthTime().toString();

        writeStringSizeAndString(fileName);
        writeStringSizeAndString(fileBirthTime);
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
}

void Archiver::compressAndWrite(Key key, Compressor compressor)
{
    int compressedSize = key.bitCount / 8;
    if (key.bitCount % 8 != 0) compressedSize++;
    out.writeInt(compressedSize);
    if(compressedSize != 0) compressor.compress();
}
