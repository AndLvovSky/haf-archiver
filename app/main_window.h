#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    enum Page {
        MAIN,
        ARCHIVING,
        UNARCHIVING,
        ARCHIVE_VIEW
    };

private:

    static const int SHORT_STATUS_TIME = 1500;

    static const int LONG_STATUS_TIME = 4000;

    std::map<int, int> archiveWorkerLine;

    std::map<int, int> unarchiveWorkerLine;

    int runningArchiveWorkers = 0;

    int runningUnarchiveWorkers = 0;

    void updateReadyToArchive();

    void updateReadyToUnarchive();

    bool isFolderNameValid(const QString& folderName);

private slots:

    void on_actionArchiving_triggered();

    void on_chooseFilesToArchiveButton_clicked();

    void on_chooseSaveDirectoryButton_clicked();

    void on_archiveButton_clicked();

    void on_chooseArchiveButton_clicked();

    void on_archiveNameLineEdit_textChanged(const QString& text);

    void on_chooseSaveDirectoryButton_2_clicked();

    void on_actionUnarchiving_triggered();

    void on_unarchiveButton_clicked();

    void on_actionViewArchive_triggered();

    void on_chooseArchiveButtonView_clicked();

    void updateReadyToView();

    void on_viewArchiveButton_clicked();

    void on_clearArchivingButton_clicked();

    void on_clearUnarchivingButton_clicked();

public:

    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

public slots:

    void archivingError(QString err, int workerId);

    void archivingFinished(bool good, int workerId);

    void unarchivingError(QString err, int workerId);

    void unarchivingFinished(bool good, int workerId);

    void archivingProgress(QString prog, int workerId);

    void archivingProgressInLine(QString msg, int workerId);

    void unarchivingProgress(QString prog, int workerId);

    void unarchivingProgressInLine(QString msg, int workerId);

private:

    Ui::MainWindow* ui;

};

#endif // MAIN_WINDOW_H
