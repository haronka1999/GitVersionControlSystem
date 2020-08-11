#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    ui->selectButton->setDisabled(true);
    ui->deselectButton->setDisabled(true);

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(enableButtons()));
    connect(ui->selectButton, SIGNAL(clicked(bool)), this, SLOT(select()));
    connect(ui->deselectButton, SIGNAL(clicked(bool)), this, SLOT(deselect()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
}

void SelectDialog::select()
{
    emit sendSelectedName(ui->textEdit->toPlainText());
}

void SelectDialog::deselect()
{
    emit sendDeselectedName(ui->textEdit->toPlainText());
}

void SelectDialog::enableButtons()
{
    if (ui->textEdit->toPlainText()=="") {
        ui->selectButton->setDisabled(true);
        ui->deselectButton->setDisabled(true);
    } else {
        ui->selectButton->setDisabled(false);
        ui->deselectButton->setDisabled(false);
    }
}

void SelectDialog::showHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("The Select File dialog box makes available the selection of a file by name.\n");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

SelectDialog::~SelectDialog()
{
    delete ui;
}
