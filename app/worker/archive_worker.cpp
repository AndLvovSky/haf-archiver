#include "archive_worker.h"
#include "archive/archiver.h"

ArchiveWorker::ArchiveWorker(QStringList filesToArchiveUris,
    QString destDir, QString destFileName) :
    filesToArchiveUris(filesToArchiveUris), destDir(destDir),
    destFileName(destFileName) {}

ArchiveWorker::~ArchiveWorker() {}

void ArchiveWorker::process() {
    try {
        Archiver archiver(filesToArchiveUris, destDir, destFileName);
        archiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what());
        emit finished(false);
        return;
    }
    emit finished(true);
}
