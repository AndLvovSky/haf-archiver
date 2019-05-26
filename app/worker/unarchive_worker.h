#ifndef UNARCHIVE_WORKER_H
#define UNARCHIVE_WORKER_H

#include <QObject>

class UnarchiveWorker : public QObject {

    Q_OBJECT

private:

    static int nextId;

    int id;

    QString archivePath;

    QString outputDirPath;

public:

    UnarchiveWorker(QString archivePath, QString outputDirPath);

    ~UnarchiveWorker();

    int getId();

public slots:

    void process();

    void onProgress(QString prog);

    void onProgressInLine(QString msg, int line);

signals:

    void finished(bool good, int workerId);

    void error(QString err, int workerId);

    void progress(QString prog, int workerId);

    void progressInLine(QString msg, int workerId);

};

#endif // UNARCHIVE_WORKER_H
