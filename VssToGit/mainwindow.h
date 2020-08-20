#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include <string.h>
#include <string>
#include <QListWidget>
#include <QAction>
#include <QDesktopServices>
#include <QTextBrowser>
#include "workingdirectorydialog.h"
#include "selectdialog.h"
#include <QPainter>
#include "adddialog.h"
#include <Git_DLL/Git_DLL/Git_DLL.h>
#include <QStandardItemModel>
#include <QStandardItem>
#include <qstyleditemdelegate.h>
#include <qdirmodel.h>
#include <QtCore>
#include "checkindialog.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int columncount = 1;
    QColor *col = new QColor(113, 44, 165);
    QString workingDirPath = "";
    QString workingDirName = "";
    QString oldName = "";
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;

public slots:
    void ShowContextMenuFiles(const QPoint &pos);
    void ShowContextMenuDirs(const QPoint &pos);
    void expandFolder(QTreeWidgetItem *);
    void menuEditClicked();
    void menuFileClicked();
    void menuSourceSafeClicked();
    void takeAction(QAction *);
    void changeButtons();
    void getSelectedName(QString);
    void getDeselectedName(QString);
    void deselectFiles();
    void deselectFolder();
    void askForCheckIn();

    //action-----------------------------------
    void exportFile();
    void createProject();
    void addFiles();
    void setWorkingFolder();
    void checkIn();
    void checkOut();
    void selectFile();
    void selectAllFiles();
    void editFile();
    void viewFile();
    void deleteSelected();
    void renameSelected();
    void renameFileFinished(QTreeWidgetItem *);
    void renameFolderFinished(QTreeWidgetItem *);
    void refreshWidgets();
    void help();
    void savePressed();

};

#endif // MAINWINDOW_H

