/********************************************************************************
** Form generated from reading UI file 'checkindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKINDIALOG_H
#define UI_CHECKINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_checkInDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *helpButton;
    QTextEdit *commentTextEdit;
    QLabel *label;

    void setupUi(QDialog *checkInDialog)
    {
        if (checkInDialog->objectName().isEmpty())
            checkInDialog->setObjectName(QString::fromUtf8("checkInDialog"));
        checkInDialog->resize(400, 178);
        buttonBox = new QDialogButtonBox(checkInDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        helpButton = new QPushButton(checkInDialog);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(290, 90, 81, 29));
        commentTextEdit = new QTextEdit(checkInDialog);
        commentTextEdit->setObjectName(QString::fromUtf8("commentTextEdit"));
        commentTextEdit->setGeometry(QRect(20, 80, 241, 71));
        label = new QLabel(checkInDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 121, 20));

        retranslateUi(checkInDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), checkInDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), checkInDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(checkInDialog);
    } // setupUi

    void retranslateUi(QDialog *checkInDialog)
    {
        checkInDialog->setWindowTitle(QCoreApplication::translate("checkInDialog", "Check In", nullptr));
        helpButton->setText(QCoreApplication::translate("checkInDialog", "Help", nullptr));
        label->setText(QCoreApplication::translate("checkInDialog", "Comment:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class checkInDialog: public Ui_checkInDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKINDIALOG_H
