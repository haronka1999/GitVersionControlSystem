#include "checkindialog.h"
#include "ui_checkindialog.h"

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkInDialog)
{
    ui->setupUi(this);
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
}

void CheckInDialog::on_okButton_clicked()
{
    QString message = getMessage();

    // if the checkin commit is empty
    if (message == "" ){
        QMessageBox msgBox;
        msgBox.setText("Please add a comment!\t");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    okClicked = true;
    this->close();
}

QString CheckInDialog::getMessage()
{
    return ui->commentTextEdit->toPlainText();
}


void CheckInDialog::on_cancelButton_clicked()
{
    this->close();
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
