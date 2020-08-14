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
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
class adddialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    QString workingFolderPath;
    QTreeWidget* filesTreewidget;
    QTreeWidget* foldersTreewidget;
    QTreeWidgetItem *parentFolder;
    void setWorkingFolderPath(QString);
    void setTreeWidget(QTreeWidget*, QTreeWidgetItem*);
    bool fileReadyToBeUploaded(QString);
    bool folderReadyToBeUploaded(QString);
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
    void add();
    void addFile(string);
    void addFolder(string);
    void changeStateViewButton();
    void showHelp();
    void viewFile();
    void closeDialog();

signals:
    void newFileAdded();
};

#endif // ADDDIALOG_H
