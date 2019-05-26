#include "archive_worker.h"
#include "archive/archiver.h"

#include <QDebug>

int ArchiveWorker::nextId = 0;

ArchiveWorker::ArchiveWorker(QStringList filesToArchiveUris,
    QString destDir, QString destFileName) :
    id(nextId++), filesToArchiveUris(filesToArchiveUris), destDir(destDir),
    destFileName(destFileName) {}

ArchiveWorker::~ArchiveWorker() {}

void ArchiveWorker::process() {
    try {
        Archiver archiver(filesToArchiveUris, destDir, destFileName);
        connect(&archiver, SIGNAL(progress(QString)), this, SLOT(onProgress(QString)));
        connect(&archiver, SIGNAL(progressInLine(QString, int)),
            this, SLOT(onProgressInLine(QString, int)));
        archiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what(), id);
        emit finished(false, id);
        return;
    }
    emit finished(true, id);
}

void ArchiveWorker::onProgress(QString prog) {
    emit progress(prog, id);
}

void ArchiveWorker::onProgressInLine(QString msg, int line) {
    emit progressInLine(msg, id);
}

int ArchiveWorker::getId() {
    return id;
}
