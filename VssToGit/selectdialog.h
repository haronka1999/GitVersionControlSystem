#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = nullptr);
    ~SelectDialog();
public slots:
    void enableButtons();
    void select();
    void deselect();
    void showHelp();

signals:
    void sendSelectedName(QString);
    void sendDeselectedName(QString);

private:
    Ui::SelectDialog *ui;
};

#endif // SELECTDIALOG_H
