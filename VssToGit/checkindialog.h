#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class checkInDialog;
}

class CheckInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckInDialog(QWidget *parent = nullptr);
    QString message;
    QString getMessage();
    ~CheckInDialog();

private:
    Ui::checkInDialog *ui;

public slots:
    void showHelp();

};

#endif // CHECKINDIALOG_H
