#include "unarchive_worker.h"
#include "archive/unarchiver.h"

UnarchiveWorker::UnarchiveWorker(QString archivePath, QString outputDirPath) :
    archivePath(archivePath), outputDirPath(outputDirPath) {}

UnarchiveWorker::~UnarchiveWorker() {}

void UnarchiveWorker::process() {
    try {
        Unarchiver unarchiver(archivePath, outputDirPath);
        connect(&unarchiver, SIGNAL(progress(QString)), this, SLOT(onProgress(QString)));
        connect(&unarchiver, SIGNAL(progressInLine(QString, int)),
            this, SLOT(onProgressInLine(QString, int)));
        unarchiver.process();
    } catch(std::runtime_error err) {
        emit error(err.what());
        emit finished(false);
        return;
    }
    emit finished(true);
}

void UnarchiveWorker::onProgress(QString prog) {
    emit progress(prog);
}

void UnarchiveWorker::onProgressInLine(QString msg, int line) {
    emit progressInLine(msg, line);
}
