#include "unarchive_worker.h"
#include "archive/unarchiver.h"

int UnarchiveWorker::nextId = 0;

UnarchiveWorker::UnarchiveWorker(QString archivePath, QString outputDirPath) :
    id(nextId++), archivePath(archivePath), outputDirPath(outputDirPath) {}

UnarchiveWorker::~UnarchiveWorker() {}

void UnarchiveWorker::process() {
    try {
        Unarchiver unarchiver(archivePath, outputDirPath);
        connect(&unarchiver, SIGNAL(progress(QString)), this, SLOT(onProgress(QString)));
        connect(&unarchiver, SIGNAL(progressInLine(QString, int)),
            this, SLOT(onProgressInLine(QString, int)));
        unarchiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what(), id);
        emit finished(false, id);
        return;
    }
    emit finished(true, id);
}

void UnarchiveWorker::onProgress(QString prog) {
    emit progress(prog, id);
}

void UnarchiveWorker::onProgressInLine(QString msg, int line) {
    emit progressInLine(msg, id);
}

int UnarchiveWorker::getId() {
    return id;
}
