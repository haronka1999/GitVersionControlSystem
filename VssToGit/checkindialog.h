#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui {
class checkInDialog;
}

class CheckInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInDialog(QWidget *parent = nullptr);
    QString message;
    bool isOkClicked = false;
    void showMessage(QString, QString, QString);
    QString getMessage();
    ~CheckInDialog();

private:
    Ui::checkInDialog *ui;

public slots:
    void showHelp();

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // CHECKINDIALOG_H
