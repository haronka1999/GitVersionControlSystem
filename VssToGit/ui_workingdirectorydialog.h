/********************************************************************************
** Form generated from reading UI file 'workingdirectorydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKINGDIRECTORYDIALOG_H
#define UI_WORKINGDIRECTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_WorkingDirectoryDialog
{
public:
    QLabel *nameLabel;
    QPushButton *createFolderButton;
    QPushButton *okButton;
    QTreeView *treeView;
    QPushButton *helpButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *WorkingDirectoryDialog)
    {
        if (WorkingDirectoryDialog->objectName().isEmpty())
            WorkingDirectoryDialog->setObjectName(QString::fromUtf8("WorkingDirectoryDialog"));
        WorkingDirectoryDialog->resize(582, 427);
        nameLabel = new QLabel(WorkingDirectoryDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(10, 20, 161, 21));
        createFolderButton = new QPushButton(WorkingDirectoryDialog);
        createFolderButton->setObjectName(QString::fromUtf8("createFolderButton"));
        createFolderButton->setGeometry(QRect(450, 80, 101, 21));
        createFolderButton->setAutoDefault(false);
        okButton = new QPushButton(WorkingDirectoryDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(450, 50, 101, 21));
        treeView = new QTreeView(WorkingDirectoryDialog);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 50, 411, 361));
        helpButton = new QPushButton(WorkingDirectoryDialog);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(450, 110, 101, 21));
        cancelButton = new QPushButton(WorkingDirectoryDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(450, 140, 101, 21));

        retranslateUi(WorkingDirectoryDialog);

        QMetaObject::connectSlotsByName(WorkingDirectoryDialog);
    } // setupUi

    void retranslateUi(QDialog *WorkingDirectoryDialog)
    {
        WorkingDirectoryDialog->setWindowTitle(QCoreApplication::translate("WorkingDirectoryDialog", "Set Working Directory", nullptr));
        nameLabel->setText(QCoreApplication::translate("WorkingDirectoryDialog", "Please choose a folder :", nullptr));
        createFolderButton->setText(QCoreApplication::translate("WorkingDirectoryDialog", "Create Folder", nullptr));
        okButton->setText(QCoreApplication::translate("WorkingDirectoryDialog", "OK", nullptr));
        helpButton->setText(QCoreApplication::translate("WorkingDirectoryDialog", "Help", nullptr));
        cancelButton->setText(QCoreApplication::translate("WorkingDirectoryDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WorkingDirectoryDialog: public Ui_WorkingDirectoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKINGDIRECTORYDIALOG_H
