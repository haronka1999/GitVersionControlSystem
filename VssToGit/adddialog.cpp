#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddialog)
{
    ui->setupUi(this);
    ui->filesTreeView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->filesTreeView->setModel(new QFileSystemModel);

    //either a folder or a file/group of files can be selected (for check in and check out)
    connect(ui->foldersTreeView, SIGNAL(expanded(const QModelIndex &)), this, SLOT(showFiles()));
    connect(ui->foldersTreeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFiles()));
    connect(ui->filesTreeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFolder()));

    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addFiles()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));

    //disabled by default until file is selected (or when folder is selected)
    ui->viewFileButton->setEnabled(false);
    connect(ui->filesTreeView, SIGNAL(pressed(QModelIndex)), this, SLOT(changeStateViewButton()));

    //loading folders in the treeview(right side)
    folderDirModel = new QFileSystemModel();
    folderDirModel->setRootPath("");
    folderDirModel->setFilter(QDir::Drives | QDir::AllDirs |   QDir::NoDotAndDotDot);
    ui->foldersTreeView->setModel(folderDirModel);

    for (int i = 1; i < folderDirModel->columnCount(); ++i)
        ui->foldersTreeView->hideColumn(i);

    ui->folderNameLabel->setText(folderDirModel->fileInfo(ui->foldersTreeView->currentIndex()).filePath());
}

void AddDialog::setWorkingFolderPath(QString path)
{
    workingFolderPath = path;
}

//loading files in the treeview(left side)
void AddDialog::showFiles()
{
    //disabled by default until file is selected (or when folder is selected)
    ui->viewFileButton->setEnabled(false);

    fileDirModel = new QFileSystemModel();
    QString path = folderDirModel->fileInfo(ui->foldersTreeView->currentIndex()).filePath();
    ui->folderNameLabel->setText(folderDirModel->fileInfo(ui->foldersTreeView->currentIndex()).filePath());

    fileDirModel->setRootPath(path);
    fileDirModel->setFilter( QDir::Files |  QDir::NoDotAndDotDot);
    ui->filesTreeView->setModel(fileDirModel);
    QModelIndex idx = fileDirModel->index(path);
    ui->filesTreeView->setRootIndex(idx);

    for (int i = 1; i <  fileDirModel->columnCount(); ++i)
        ui->filesTreeView->hideColumn(i);
}

void AddDialog::deselectFiles()
{
    if (ui->foldersTreeView->selectionModel()->selectedIndexes().size()!=0 && ui->filesTreeView->selectionModel()->selectedIndexes().size()!=0){
        ui->filesTreeView->selectionModel()->clearSelection();
        ui->viewFileButton->setEnabled(false);
    }
}

void AddDialog::deselectFolder()
{
    if (ui->filesTreeView->selectionModel()->selectedIndexes().size()!=0 && ui->foldersTreeView->selectionModel()->selectedIndexes().size()!=0){
        ui->foldersTreeView->selectionModel()->clearSelection();
    }
}

void AddDialog::addFiles()
{
    QModelIndexList fileind = ui->filesTreeView->selectionModel()->selectedIndexes();

    //message
    bool ok;
    QString checkinmsg = QInputDialog::getText(this, "Add Files Message", "Message:", QLineEdit::Normal, "", &ok, Qt::MSWindowsFixedSizeDialogHint);

    if (ok) {
        if(fileind.count()!=0){ //file or a group of files selected

            for (int i = 0; i < fileind.count(); i+=4){
                if (!QFile::copy(fileDirModel->filePath(fileind.at(i)), workingFolderPath+"/"+fileDirModel->fileName(fileind.at(i)))) {
                    QMessageBox::information(0, "Error", "Unsuccesful copy into working folder.");
                } else {
                    string errormsg = "";
                    checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+(fileDirModel->fileName(fileind.at(i))).toStdString()+ "\"", checkinmsg.toStdString(), errormsg);

                    if (errormsg!="") {
                        QMessageBox::information(0, "Error", errormsg.c_str());
                    }
                }
            }
        } else { //folder
            string errormsg = "";
            checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+(folderDirModel->fileName(ui->foldersTreeView->currentIndex())).toStdString()+ "\"", checkinmsg.toStdString(), errormsg);
            if (errormsg!="") {
                QMessageBox::information(0, "Error", errormsg.c_str());
            }
        }
    }
}

//check it there's a selected file
void AddDialog::changeStateViewButton()
{
    QModelIndexList indexes = ui->filesTreeView->selectionModel()->selectedIndexes();

    if (indexes.size()==4) { //only one file can be selected
        ui->viewFileButton->setEnabled(true);
    } else {
        ui->viewFileButton->setEnabled(false);
    }
}

void AddDialog::viewFile()
{
    // action not performed if there's more than one file selected
    if (ui->filesTreeView->selectionModel()->selectedIndexes().size()==4) {

        QFile file(fileDirModel->fileInfo(ui->filesTreeView->currentIndex()).filePath());
        //if the file doesn't exist
        if (!file.exists()){
            QMessageBox::information(0, "error", file.errorString());
        }

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)!=0){
            QTextStream stream(&file);
            QTextBrowser *browser = new QTextBrowser();
            browser->setText(stream.readAll());
            browser->setGeometry(700, 180, 500, 700);
            browser->show();
        } else {
            QMessageBox::information(0, "Error", file.errorString());
        }

        file.close();

    } else {
        QMessageBox::information(0, "Error", "Multiple files selected.");
    }
}

void AddDialog::showHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("The Add files dialog box provides you the opportunity\n"
                   "to copy a selected file, a group of files or a directory\n"
                   "into the previously selected folder of your project.\n");
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void AddDialog::closeDialog()
{
    close();
}

AddDialog::~AddDialog()
{
    delete ui;
}
