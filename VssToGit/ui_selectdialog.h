/********************************************************************************
** Form generated from reading UI file 'selectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDIALOG_H
#define UI_SELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_SelectDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QPushButton *selectButton;
    QPushButton *deselectButton;
    QTextEdit *textEdit;
    QPushButton *helpButton;

    void setupUi(QDialog *SelectDialog)
    {
        if (SelectDialog->objectName().isEmpty())
            SelectDialog->setObjectName(QString::fromUtf8("SelectDialog"));
        SelectDialog->resize(422, 139);
        buttonBox = new QDialogButtonBox(SelectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(320, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(SelectDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 54, 20));
        selectButton = new QPushButton(SelectDialog);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setGeometry(QRect(80, 80, 91, 29));
        deselectButton = new QPushButton(SelectDialog);
        deselectButton->setObjectName(QString::fromUtf8("deselectButton"));
        deselectButton->setGeometry(QRect(180, 80, 91, 29));
        textEdit = new QTextEdit(SelectDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(80, 30, 191, 31));
        helpButton = new QPushButton(SelectDialog);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(320, 90, 81, 29));

        retranslateUi(SelectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SelectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SelectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDialog)
    {
        SelectDialog->setWindowTitle(QCoreApplication::translate("SelectDialog", "Select File", nullptr));
        label->setText(QCoreApplication::translate("SelectDialog", "Item:", nullptr));
        selectButton->setText(QCoreApplication::translate("SelectDialog", "Select", nullptr));
        deselectButton->setText(QCoreApplication::translate("SelectDialog", "Deselect", nullptr));
        helpButton->setText(QCoreApplication::translate("SelectDialog", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectDialog: public Ui_SelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDIALOG_H
