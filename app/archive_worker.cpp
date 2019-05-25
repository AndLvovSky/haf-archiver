#include "archive_worker.h"
#include "archiver.h"

ArchiveWorker::ArchiveWorker(QStringList filesToArchiveUris,
    QString destDir, QString destFileName) :
    filesToArchiveUris(filesToArchiveUris), destDir(destDir),
    destFileName(destFileName) {}

ArchiveWorker::~ArchiveWorker() {}

void ArchiveWorker::process() {
    Archiver archiver(filesToArchiveUris, destDir, destFileName);
    archiver.process();
    emit finished();
}
