#include "checkindialog.h"
#include "ui_checkindialog.h"

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkInDialog)
{
    ui->setupUi(this);
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
}

QString CheckInDialog::getMessage()
{
    return ui->commentTextEdit->toPlainText();
}

void CheckInDialog::showHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("Saves the changes of the selected files or folder to the database, with comment.\n");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

CheckInDialog::~CheckInDialog()
{
    delete ui;
}
