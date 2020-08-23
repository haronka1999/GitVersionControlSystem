#include "checkindialog.h"
#include "ui_checkindialog.h"

CheckInDialog::CheckInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkInDialog)
{
    ui->setupUi(this);
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));

    //removes the whatisthis hint plugin
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void CheckInDialog::on_okButton_clicked()
{
    QString message = getMessage();

    // if the checkin commit is empty
    if (message == "" ){
        showMessage("ButtonImages/error.png", "Error", "Aborting check in due to empty message.");
    }

    isOkClicked = true;
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
    showMessage("ButtonImages/help3.png", "Help", "Saves the changes of the selected files or folder to the database, with comment.\n");
}

void CheckInDialog::showMessage(QString iconPath, QString title, QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(iconPath));
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

CheckInDialog::~CheckInDialog()
{
    delete ui;
}
