/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionView_File;
    QAction *actionEdit_File;
    QAction *actionSelect;
    QAction *actionSelect_All;
    QAction *actionRefresh_file_list;
    QAction *actionCheck_Out;
    QAction *actionCheck_In;
    QAction *actionName;
    QAction *actionType;
    QAction *actionSize;
    QAction *actionDate;
    QAction *actionAdd_files;
    QAction *actionSet_Working_Folder;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionHelp;
    QWidget *centralwidget;
    QPushButton *addFilesButton;
    QPushButton *helpButton;
    QPushButton *viewFileButton;
    QPushButton *editFileButton;
    QFrame *line;
    QFrame *line_2;
    QPushButton *setWorkingFolderButton;
    QPushButton *checkInButton;
    QPushButton *checkOutButton;
    QPushButton *refreshButton;
    QFrame *frame_2;
    QFrame *frame_3;
    QFrame *frame_4;
    QFrame *frame_5;
    QFrame *frame_6;
    QFrame *frame_7;
    QFrame *frame_8;
    QFrame *frame_9;
    QFrame *frame_10;
    QFrame *frame_11;
    QFrame *frame_12;
    QFrame *frame_13;
    QFrame *workingFolderLine;
    QFrame *line_3;
    QFrame *line_6;
    QLabel *workingDirLabel;
    QTreeWidget *foldersTreeWidget;
    QTreeWidget *filesTreeWidget;
    QFrame *line_4;
    QLabel *selectedFolderLabel;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuSort;
    QMenu *menuSourceSafe;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1099, 843);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        MainWindow->setFont(font);
        actionView_File = new QAction(MainWindow);
        actionView_File->setObjectName(QString::fromUtf8("actionView_File"));
        actionEdit_File = new QAction(MainWindow);
        actionEdit_File->setObjectName(QString::fromUtf8("actionEdit_File"));
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionRefresh_file_list = new QAction(MainWindow);
        actionRefresh_file_list->setObjectName(QString::fromUtf8("actionRefresh_file_list"));
        actionCheck_Out = new QAction(MainWindow);
        actionCheck_Out->setObjectName(QString::fromUtf8("actionCheck_Out"));
        actionCheck_In = new QAction(MainWindow);
        actionCheck_In->setObjectName(QString::fromUtf8("actionCheck_In"));
        actionName = new QAction(MainWindow);
        actionName->setObjectName(QString::fromUtf8("actionName"));
        actionType = new QAction(MainWindow);
        actionType->setObjectName(QString::fromUtf8("actionType"));
        actionSize = new QAction(MainWindow);
        actionSize->setObjectName(QString::fromUtf8("actionSize"));
        actionDate = new QAction(MainWindow);
        actionDate->setObjectName(QString::fromUtf8("actionDate"));
        actionAdd_files = new QAction(MainWindow);
        actionAdd_files->setObjectName(QString::fromUtf8("actionAdd_files"));
        actionSet_Working_Folder = new QAction(MainWindow);
        actionSet_Working_Folder->setObjectName(QString::fromUtf8("actionSet_Working_Folder"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        addFilesButton = new QPushButton(centralwidget);
        addFilesButton->setObjectName(QString::fromUtf8("addFilesButton"));
        addFilesButton->setGeometry(QRect(90, 20, 31, 31));
        addFilesButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/addfile3.png);"));
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(330, 20, 31, 31));
        helpButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/help3.png);"));
        viewFileButton = new QPushButton(centralwidget);
        viewFileButton->setObjectName(QString::fromUtf8("viewFileButton"));
        viewFileButton->setGeometry(QRect(210, 20, 31, 31));
        viewFileButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/viewfile1.png);"));
        editFileButton = new QPushButton(centralwidget);
        editFileButton->setObjectName(QString::fromUtf8("editFileButton"));
        editFileButton->setGeometry(QRect(250, 20, 31, 31));
        editFileButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/editfile1.png);"));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 0, 1101, 16));
        line->setFrameShadow(QFrame::Raised);
        line->setMidLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 50, 1101, 31));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setMidLineWidth(1);
        line_2->setFrameShape(QFrame::HLine);
        setWorkingFolderButton = new QPushButton(centralwidget);
        setWorkingFolderButton->setObjectName(QString::fromUtf8("setWorkingFolderButton"));
        setWorkingFolderButton->setGeometry(QRect(10, 20, 31, 31));
        setWorkingFolderButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/folders2.png);"));
        checkInButton = new QPushButton(centralwidget);
        checkInButton->setObjectName(QString::fromUtf8("checkInButton"));
        checkInButton->setGeometry(QRect(130, 20, 31, 31));
        checkInButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/checkin.png);"));
        checkOutButton = new QPushButton(centralwidget);
        checkOutButton->setObjectName(QString::fromUtf8("checkOutButton"));
        checkOutButton->setGeometry(QRect(170, 20, 31, 31));
        checkOutButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/checkout2.png);"));
        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(290, 20, 31, 31));
        refreshButton->setStyleSheet(QString::fromUtf8("image: url(:/buttonpics/ButtonImages/refresh.png);"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(90, 20, 31, 31));
        frame_2->setFrameShape(QFrame::WinPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(40, 0, 31, 31));
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(130, 20, 31, 31));
        frame_4->setFrameShape(QFrame::WinPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_5 = new QFrame(frame_4);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(30, 40, 120, 80));
        frame_5->setFrameShape(QFrame::WinPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        frame_6 = new QFrame(frame_5);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(60, 60, 120, 80));
        frame_6->setFrameShape(QFrame::WinPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        frame_7 = new QFrame(frame_6);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(0, 0, 120, 80));
        frame_7->setFrameShape(QFrame::WinPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        frame_8 = new QFrame(centralwidget);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(170, 20, 31, 31));
        frame_8->setFrameShape(QFrame::WinPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        frame_9 = new QFrame(centralwidget);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(210, 20, 31, 31));
        frame_9->setFrameShape(QFrame::WinPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        frame_10 = new QFrame(centralwidget);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(250, 20, 31, 31));
        frame_10->setFrameShape(QFrame::WinPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        frame_11 = new QFrame(centralwidget);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setGeometry(QRect(10, 20, 31, 31));
        frame_11->setFrameShape(QFrame::WinPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        frame_12 = new QFrame(centralwidget);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setGeometry(QRect(290, 20, 31, 31));
        frame_12->setFrameShape(QFrame::WinPanel);
        frame_12->setFrameShadow(QFrame::Raised);
        frame_13 = new QFrame(centralwidget);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setGeometry(QRect(330, 20, 31, 31));
        frame_13->setFrameShape(QFrame::WinPanel);
        frame_13->setFrameShadow(QFrame::Raised);
        workingFolderLine = new QFrame(centralwidget);
        workingFolderLine->setObjectName(QString::fromUtf8("workingFolderLine"));
        workingFolderLine->setGeometry(QRect(360, 80, 721, 16));
        workingFolderLine->setFrameShape(QFrame::HLine);
        workingFolderLine->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(350, 71, 20, 20));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(centralwidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(1070, 71, 20, 20));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        workingDirLabel = new QLabel(centralwidget);
        workingDirLabel->setObjectName(QString::fromUtf8("workingDirLabel"));
        workingDirLabel->setGeometry(QRect(700, 70, 371, 20));
        foldersTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        foldersTreeWidget->setHeaderItem(__qtreewidgetitem);
        foldersTreeWidget->setObjectName(QString::fromUtf8("foldersTreeWidget"));
        foldersTreeWidget->setGeometry(QRect(20, 90, 331, 711));
        foldersTreeWidget->setFrameShape(QFrame::WinPanel);
        foldersTreeWidget->setFrameShadow(QFrame::Sunken);
        filesTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        filesTreeWidget->setHeaderItem(__qtreewidgetitem1);
        filesTreeWidget->setObjectName(QString::fromUtf8("filesTreeWidget"));
        filesTreeWidget->setGeometry(QRect(360, 90, 721, 711));
        filesTreeWidget->setFrameShape(QFrame::WinPanel);
        filesTreeWidget->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(680, 69, 20, 21));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        selectedFolderLabel = new QLabel(centralwidget);
        selectedFolderLabel->setObjectName(QString::fromUtf8("selectedFolderLabel"));
        selectedFolderLabel->setGeometry(QRect(360, 70, 321, 20));
        MainWindow->setCentralWidget(centralwidget);
        frame_2->raise();
        frame_4->raise();
        frame_8->raise();
        frame_9->raise();
        frame_10->raise();
        frame_11->raise();
        frame_12->raise();
        frame_13->raise();
        addFilesButton->raise();
        helpButton->raise();
        viewFileButton->raise();
        editFileButton->raise();
        line->raise();
        line_2->raise();
        setWorkingFolderButton->raise();
        checkInButton->raise();
        checkOutButton->raise();
        refreshButton->raise();
        workingFolderLine->raise();
        line_3->raise();
        line_6->raise();
        workingDirLabel->raise();
        foldersTreeWidget->raise();
        filesTreeWidget->raise();
        line_4->raise();
        selectedFolderLabel->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1099, 26));
        menuBar->setAutoFillBackground(false);
        menuBar->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);\n"
"border-color: rgb(160, 160, 160);\n"
"gridline-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"selection-color: rgb(85, 85, 127);"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSort = new QMenu(menuView);
        menuSort->setObjectName(QString::fromUtf8("menuSort"));
        menuSourceSafe = new QMenu(menuBar);
        menuSourceSafe->setObjectName(QString::fromUtf8("menuSourceSafe"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSourceSafe->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionAdd_files);
        menuFile->addSeparator();
        menuFile->addAction(actionSet_Working_Folder);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionView_File);
        menuEdit->addAction(actionEdit_File);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect);
        menuEdit->addAction(actionSelect_All);
        menuView->addAction(menuSort->menuAction());
        menuView->addSeparator();
        menuView->addAction(actionRefresh_file_list);
        menuSort->addAction(actionName);
        menuSort->addAction(actionType);
        menuSort->addAction(actionSize);
        menuSort->addAction(actionDate);
        menuSourceSafe->addAction(actionCheck_Out);
        menuSourceSafe->addAction(actionCheck_In);
        menuHelp->addAction(actionHelp);

        retranslateUi(MainWindow);

        addFilesButton->setDefault(false);
        helpButton->setDefault(false);
        viewFileButton->setDefault(false);
        editFileButton->setDefault(false);
        setWorkingFolderButton->setDefault(false);
        checkInButton->setDefault(false);
        checkOutButton->setDefault(false);
        refreshButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "VSS -> Git API", nullptr));
        actionView_File->setText(QCoreApplication::translate("MainWindow", "View File...", nullptr));
        actionEdit_File->setText(QCoreApplication::translate("MainWindow", "Edit File...", nullptr));
        actionSelect->setText(QCoreApplication::translate("MainWindow", "Select... ", nullptr));
#if QT_CONFIG(shortcut)
        actionSelect->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelect_All->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
#if QT_CONFIG(shortcut)
        actionSelect_All->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRefresh_file_list->setText(QCoreApplication::translate("MainWindow", "Refresh file list", nullptr));
#if QT_CONFIG(shortcut)
        actionRefresh_file_list->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCheck_Out->setText(QCoreApplication::translate("MainWindow", "Check Out", nullptr));
#if QT_CONFIG(shortcut)
        actionCheck_Out->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+K", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCheck_In->setText(QCoreApplication::translate("MainWindow", "Check In... ", nullptr));
#if QT_CONFIG(shortcut)
        actionCheck_In->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        actionName->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        actionType->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        actionSize->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        actionDate->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        actionAdd_files->setText(QCoreApplication::translate("MainWindow", "Add Files...", nullptr));
#if QT_CONFIG(shortcut)
        actionAdd_files->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSet_Working_Folder->setText(QCoreApplication::translate("MainWindow", "Set Working Folder", nullptr));
#if QT_CONFIG(shortcut)
        actionSet_Working_Folder->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
#if QT_CONFIG(tooltip)
        addFilesButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Add Files</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        addFilesButton->setText(QString());
#if QT_CONFIG(tooltip)
        helpButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Help</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        helpButton->setText(QString());
#if QT_CONFIG(tooltip)
        viewFileButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>View File</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        viewFileButton->setText(QString());
#if QT_CONFIG(tooltip)
        editFileButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Edit File</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        editFileButton->setText(QString());
#if QT_CONFIG(tooltip)
        setWorkingFolderButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Set Working Folder</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        setWorkingFolderButton->setText(QString());
#if QT_CONFIG(tooltip)
        checkInButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Check In</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkInButton->setText(QString());
#if QT_CONFIG(tooltip)
        checkOutButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Check Out</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkOutButton->setText(QString());
#if QT_CONFIG(tooltip)
        refreshButton->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Refresh</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        refreshButton->setText(QString());
        workingDirLabel->setText(QString());
        selectedFolderLabel->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuSort->setTitle(QCoreApplication::translate("MainWindow", "Sort", nullptr));
        menuSourceSafe->setTitle(QCoreApplication::translate("MainWindow", "SourceSafe", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
