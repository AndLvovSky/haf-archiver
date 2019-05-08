#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:

    void updateReadyToArchive();

private slots:

    void on_actionArchiving_triggered();

    void on_chooseFilesToArchiveButton_clicked();

    void on_chooseSaveDirectoryButton_clicked();

    void on_archiveButton_clicked();

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:


    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
