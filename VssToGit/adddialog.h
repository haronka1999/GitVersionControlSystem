#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTextBrowser>
#include <iostream>
#include <string>
#include <QTextStream>
#include <Git_DLL/Git_DLL/Git_DLL.h>
#include <QLineEdit>
#include <QInputDialog>

namespace Ui {
class adddialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    QString workingFolderPath;
    void setWorkingFolderPath(QString);
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private:
    Ui::adddialog *ui;
    QFileSystemModel *folderDirModel;
    QFileSystemModel *fileDirModel;

public slots:
    void showFiles();
    void deselectFiles();
    void deselectFolder();
    void addFiles();
    void changeStateViewButton();
    void showHelp();
    void viewFile();
    void closeDialog();
};

#endif // ADDDIALOG_H
