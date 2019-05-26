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

public:

    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

public slots:

    void archivingError(QString err);

    void archivingFinished(bool good);

    void unarchivingError(QString err);

    void unarchivingFinished();

private:

    Ui::MainWindow* ui;

};

#endif // MAIN_WINDOW_H
