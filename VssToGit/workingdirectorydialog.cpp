#include "workingdirectorydialog.h"
#include "ui_workingdirectorydialog.h"

WorkingDirectoryDialog::WorkingDirectoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkingDirectoryDialog)
{
    ui->setupUi(this);
    showFolders();

    //removes the whatisthis hint plugin
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
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
        showMessage("ButtonImages/error.png", "Error", "Please select a path.");
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
                                         tr("Name"), &ok, dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        if(!ok){
        return;
    }

    if (folderName.isEmpty()){
        showMessage("ButtonImages/error.png", "Error", "Please give a name.");
        return;
    }

    qDebug() << qPath;
    if(qPath == ""){
        showMessage("ButtonImages/error.png", "Error", "Please select a path.");
        return;
    }

    QDir dir(qPath);
    if(!dir.mkdir(folderName)){
        showMessage("ButtonImages/error.png", "Error", "Error.");
        return;
    }
}

void WorkingDirectoryDialog::on_helpButton_clicked()
{
    showMessage("ButtonImages/help3.png","Help", "If you want to create a new repository, you need to select a folder where"
                                                  "a new repository will be initalized.\n"
                                                  "\n"
                                                  "In case you want to create a new folder,please press the Create Folder button"
                                                  "and the new folder will be initialized to the choosen folder.");
}

void WorkingDirectoryDialog::showMessage(QString iconPath, QString title, QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(iconPath));
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void WorkingDirectoryDialog::on_cancelButton_clicked()
{
    this->close();
}
