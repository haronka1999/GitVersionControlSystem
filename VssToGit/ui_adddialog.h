/********************************************************************************
** Form generated from reading UI file 'adddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDIALOG_H
#define UI_ADDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_adddialog
{
public:
    QPushButton *viewFileButton;
    QPushButton *helpButton;
    QLabel *label;
    QTreeView *filesTreeView;
    QLabel *label_2;
    QTreeView *foldersTreeView;
    QLabel *folderNameLabel;
    QPushButton *addButton;
    QPushButton *closeButton;

    void setupUi(QDialog *adddialog)
    {
        if (adddialog->objectName().isEmpty())
            adddialog->setObjectName(QString::fromUtf8("adddialog"));
        adddialog->resize(839, 458);
        viewFileButton = new QPushButton(adddialog);
        viewFileButton->setObjectName(QString::fromUtf8("viewFileButton"));
        viewFileButton->setGeometry(QRect(720, 110, 81, 29));
        helpButton = new QPushButton(adddialog);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(720, 150, 81, 29));
        label = new QLabel(adddialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 91, 20));
        filesTreeView = new QTreeView(adddialog);
        filesTreeView->setObjectName(QString::fromUtf8("filesTreeView"));
        filesTreeView->setGeometry(QRect(20, 70, 261, 351));
        label_2 = new QLabel(adddialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 20, 54, 20));
        foldersTreeView = new QTreeView(adddialog);
        foldersTreeView->setObjectName(QString::fromUtf8("foldersTreeView"));
        foldersTreeView->setGeometry(QRect(300, 70, 401, 351));
        folderNameLabel = new QLabel(adddialog);
        folderNameLabel->setObjectName(QString::fromUtf8("folderNameLabel"));
        folderNameLabel->setGeometry(QRect(300, 40, 401, 31));
        addButton = new QPushButton(adddialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(720, 30, 81, 29));
        closeButton = new QPushButton(adddialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(720, 70, 81, 29));

        retranslateUi(adddialog);

        QMetaObject::connectSlotsByName(adddialog);
    } // setupUi

    void retranslateUi(QDialog *adddialog)
    {
        adddialog->setWindowTitle(QCoreApplication::translate("adddialog", "Dialog", nullptr));
        viewFileButton->setText(QCoreApplication::translate("adddialog", "View", nullptr));
        helpButton->setText(QCoreApplication::translate("adddialog", "Help", nullptr));
        label->setText(QCoreApplication::translate("adddialog", "Files:", nullptr));
        label_2->setText(QCoreApplication::translate("adddialog", "Folders:", nullptr));
        folderNameLabel->setText(QString());
        addButton->setText(QCoreApplication::translate("adddialog", "Add", nullptr));
        closeButton->setText(QCoreApplication::translate("adddialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adddialog: public Ui_adddialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDIALOG_H
