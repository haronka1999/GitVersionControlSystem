#include "workingdirectorydialog.h"
#include "ui_workingdirectorydialog.h"

WorkingDirectoryDialog::WorkingDirectoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkingDirectoryDialog)
{
    ui->setupUi(this);
    showFolders();
}

WorkingDirectoryDialog::~WorkingDirectoryDialog()
{
    delete ui;
}

void WorkingDirectoryDialog::showFolders()
{
    dirModel = new QFileSystemModel();
    dirModel->setRootPath("");
    dirModel->setFilter(QDir::Drives | QDir::AllDirs |   QDir::NoDotAndDotDot);
    ui->treeView->setModel(dirModel);
    QModelIndex idx = dirModel->index(dirPath);
    ui->treeView->setRootIndex(idx);
    for (int i = 1; i < dirModel->columnCount(); ++i)
        ui->treeView->hideColumn(i);
}


void WorkingDirectoryDialog::on_okButton_clicked()
{
    pathToShow = "";
    dirModel = new QFileSystemModel(ui->treeView);
    std::string path = dirModel->fileInfo(ui->treeView->currentIndex()).filePath().toStdString();
    QString qPath = QString::fromStdString(path);
    if(qPath == ""){
        QMessageBox msgBox;
        msgBox.setText("Please select a path!");
        msgBox.exec();
        return;
    }
    pathToShow = path;
    gitInit(pathToShow);
    isOkClicked = true;
    this->close();
}

void WorkingDirectoryDialog::on_createFolderButton_clicked()
{
    dirModel = new QFileSystemModel(ui->treeView);
    std::string path = dirModel->fileInfo(ui->treeView->currentIndex()).filePath().toStdString();
    QString qPath = QString::fromStdString(path);

    bool ok;
    QInputDialog *dialog = new QInputDialog();
    QString folderName = dialog->getText(this, tr("Create Folder"),
                                         tr("Folder name:"), QLineEdit::Normal,
                                         tr("Name"), &ok);
    if(!ok){
        return;
    }

    if (folderName.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Please give a name!");
        //msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    qDebug() << qPath;
    if(qPath == ""){
        QMessageBox msgBox;
        msgBox.setText("Please select a path!");
        msgBox.exec();
        return;
    }

    QDir dir(qPath);
    if(!dir.mkdir(folderName)){
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
        return;
    }
}

void WorkingDirectoryDialog::on_helpButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("If you want to create a new\n repository,\n you need to select a folder\n"
                   "where a new repository will be initalized.\n"
                   "\n"
                   "In case you want to create\n a new folder,\n"
                   "please press the Create Folder button\n"
                   "and the new folder will be initialized\n"
                   "to the choosen folder.");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void WorkingDirectoryDialog::on_cancelButton_clicked()
{
    this->close();
}
