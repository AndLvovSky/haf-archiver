#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionArchiving_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(Page::ARCHIVING);
}

void MainWindow::on_chooseFilesToArchiveButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        ui->filesToArchiveText->setText(fileNames.join(";"));
        updateReadyToArchive();
    }
}

void MainWindow::on_chooseSaveDirectoryButton_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directoryName;
    if (dialog.exec()) {
        directoryName = dialog.selectedFiles()[0];
        ui->saveDirectoryText->setText(directoryName);
        updateReadyToArchive();
    }
}

void MainWindow::on_archiveButton_clicked() {
    // do archiving
    ui->archiveButton->setEnabled(false);
    QMessageLogger().debug("Start archiving");
}

void MainWindow::updateReadyToArchive() {
    if (ui->filesToArchiveText->text() != "" &&
        ui->saveDirectoryText->text() != "" &&
        isFolderNameValid(ui->archiveNameLineEdit->text())) {
        ui->archiveButton->setEnabled(true);
    } else {
        ui->archiveButton->setEnabled(false);
    }
}

void MainWindow::updateReadyToUnarchive() {
    if (ui->archiveText->text() != "" &&
        ui->saveDirectoryText_2->text() != "") {
        ui->unarchiveButton->setEnabled(true);
    } else {
        ui->unarchiveButton->setEnabled(false);
    }
}

void MainWindow::on_chooseArchiveButton_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Archive"), "C:/", tr("Archive Files (*.haf)"));
    if (fileName == "") return;
    ui->archiveText->setText(fileName);
    updateReadyToUnarchive();
}

void MainWindow::on_archiveNameLineEdit_textChanged(const QString& text) {
    updateReadyToArchive();
}

bool MainWindow::isFolderNameValid(const QString& folderName) {
    // TODO
    return folderName != "";
}

void MainWindow::on_chooseSaveDirectoryButton_2_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString directoryName;
    if (dialog.exec()) {
        directoryName = dialog.selectedFiles()[0];
        ui->saveDirectoryText_2->setText(directoryName);
        updateReadyToUnarchive();
    }
}

void MainWindow::on_actionUnarchiving_triggered() {
    auto stw = ui->stackedWidget;
    stw->setCurrentIndex(Page::UNARCHIVING);
}

void MainWindow::on_unarchiveButton_clicked() {
    // do unarchiving
    ui->unarchiveButton->setEnabled(false);
    QMessageLogger().debug("Start unarchiving");
}
