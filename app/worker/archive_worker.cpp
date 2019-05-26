#include "archive_worker.h"
#include "archive/archiver.h"

#include <QDebug>

ArchiveWorker::ArchiveWorker(QStringList filesToArchiveUris,
    QString destDir, QString destFileName) :
    filesToArchiveUris(filesToArchiveUris), destDir(destDir),
    destFileName(destFileName) {}

ArchiveWorker::~ArchiveWorker() {}

void ArchiveWorker::process() {
    try {
        Archiver archiver(filesToArchiveUris, destDir, destFileName);
        connect(&archiver, SIGNAL(progress(QString)), this, SLOT(onProgress(QString)));
        archiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what());
        emit finished(false);
        return;
    }
    emit finished(true);
}

void ArchiveWorker::onProgress(QString prog) {
    emit progress(prog);
}
