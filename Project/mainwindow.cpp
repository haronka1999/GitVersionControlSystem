#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->browseButton, SIGNAL(clicked(bool)), this, SLOT(browseFiles()));
    connect(ui->removeButton, SIGNAL(clicked(bool)), this, SLOT(removeFileFromList()));
    connect(ui->removeAllButton, SIGNAL(clicked(bool)), this, SLOT(clearFilesList()));
    connect(ui->checkInButton, SIGNAL(clicked(bool)), this, SLOT(checkInFiles()));

}

void MainWindow::browseFiles()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Add files"), "",
                                                    tr("All Files (*)"));
    if(fileName!="")
    {
        ui->addFilesListWidget->addItem(fileName);
    }
}

void MainWindow::checkInFiles()
{
    QProcess process;
    int n = ui->addFilesListWidget->count();
    QStringList args;

    for(int i = 0; i < n; ++i)
    {
        args.append(ui->addFilesListWidget->item(i)->text());
    }
    process.execute("batchfiles/checkin.bat ", args);
    process.waitForFinished();
}

void MainWindow::removeFileFromList()
{
    delete ui->addFilesListWidget->takeItem(ui->addFilesListWidget->currentRow());
}

void MainWindow::clearFilesList()
{
    ui->addFilesListWidget->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

