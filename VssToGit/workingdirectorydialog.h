#ifndef WORKINGDIRECTORYDIALOG_H
#define WORKINGDIRECTORYDIALOG_H
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>
#include <QDir>
#include <QProcess>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QFileSystemModel>
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QModelIndex>
#include <string>
#include <QListWidget>
#include <QAction>
#include <QDesktopServices>
#include <QInputDialog>
#include <Git_DLL/Git_DLL/Git_DLL.h>

using namespace std;

namespace Ui {
class WorkingDirectoryDialog;
}

class WorkingDirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorkingDirectoryDialog(QWidget *parent = nullptr);
    ~WorkingDirectoryDialog();
    string pathToShow;
    bool isOkClicked = false;
    void showMessage(QString, QString, QString);
    void showFolders();

private slots:
    void on_okButton_clicked();
    void on_createFolderButton_clicked();
    void on_helpButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::WorkingDirectoryDialog *ui;
    QString dirPath;
    QFileSystemModel *dirModel;
};

#endif // WORKINGDIRECTORYDIALOG_H
