#ifndef UNARCHIVE_WORKER_H
#define UNARCHIVE_WORKER_H

#include <QObject>

class UnarchiveWorker : public QObject {

    Q_OBJECT

private:

    QString archivePath;

    QString outputDirPath;

public:

    UnarchiveWorker(QString archivePath, QString outputDirPath);

    ~UnarchiveWorker();

public slots:

    void process();

    void onProgress(QString prog);

    void onProgressInLine(QString msg, int line);

signals:

    void finished(bool good);

    void error(QString err);

    void progress(QString prog);

    void progressInLine(QString msg, int line);

};

#endif // UNARCHIVE_WORKER_H
