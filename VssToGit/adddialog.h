#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <string>
#include <iostream>
#include <QDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTextStream>
#include <QLineEdit>
#include <QInputDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <Git_DLL/Git_DLL/Git_DLL.h>

namespace Ui {
class adddialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    QString destinationPath;
    QTreeWidget* filesTreewidget;
    QTreeWidget* foldersTreewidget;
    QTreeWidgetItem *parentFolder;
    void setTreeWidget(QString, QTreeWidget*, QTreeWidgetItem*);
    int fileReadyToBeUploaded(QString);
    int folderReadyToBeUploaded(QString);
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

private:
    Ui::adddialog *ui;
    QFileSystemModel *folderDirModel;
    QFileSystemModel *fileDirModel;

public slots:
    void showFiles();
    void changeStateViewButton();
    void deselectFiles();
    void deselectFolder();
    void add();
    void addFile(string);
    void addFolder(string);
    void viewFile();
    void showHelp();
    void closeDialog();
};

#endif // ADDDIALOG_H
