#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddialog)
{
    ui->setupUi(this);

    //either a folder or a file/group of files can be selected
    ui->filesTreeView->setModel(new QFileSystemModel);
    ui->filesTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(ui->foldersTreeView, SIGNAL(expanded(const QModelIndex &)), this, SLOT(showFiles()));
    connect(ui->foldersTreeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFiles()));
    connect(ui->filesTreeView, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFolder()));

    //disabled by default until file is selected (or when folder is selected)
    ui->viewFileButton->setEnabled(false);
    connect(ui->filesTreeView, SIGNAL(pressed(QModelIndex)), this, SLOT(changeStateViewButton()));

    //loading folders in the treeview(right side)
    folderDirModel = new QFileSystemModel();
    folderDirModel->setRootPath("");
    folderDirModel->setFilter(QDir::Drives | QDir::AllDirs |   QDir::NoDotAndDotDot);
    ui->foldersTreeView->setModel(folderDirModel);

    for (int i = 1; i < folderDirModel->columnCount(); ++i) {
        ui->foldersTreeView->hideColumn(i);
        ui->filesTreeView->hideColumn(i);
    }

    ui->folderNameLabel->setText(folderDirModel->fileInfo(ui->foldersTreeView->currentIndex()).filePath());

    //buttons--------------------------------------------------------------------------------------
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addFiles()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));
}

//it helps to keep track of the path where the added files are supposed to be uploaded
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
}

//a folder was clicked
void AddDialog::deselectFiles()
{
    if (ui->foldersTreeView->selectionModel()->selectedIndexes().size()!=0 && ui->filesTreeView->selectionModel()->selectedIndexes().size()!=0){
        ui->filesTreeView->selectionModel()->clearSelection();
        ui->viewFileButton->setEnabled(false);
    }
}

//a file was clicked
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

    if (ok) { //dialog was closed with OK button
        if (checkinmsg!="") { //checkin message can't be empty
            if(fileind.count()!=0){ //file or a group of files selected

                for (int i = 0; i < fileind.count(); i+=4){  //looping through the selected files

                    QString fileName = fileDirModel->fileName(fileind.at(i));

                    //firstly, upload file in the working directory
                    //secondly, check the uploaded file in
                    if (!QFile::copy(fileDirModel->filePath(fileind.at(i)), workingFolderPath+"/"+fileName)) {
                        QMessageBox::information(0, "Error", "Unsuccesful copy into working folder.");
                    } else { //if it was succesfully copied, then it is ready to be checked in
                        string errormsg = "";
                        checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+fileName.toStdString()+ "\"", checkinmsg.toStdString(), errormsg);

                        if (errormsg!="") {
                            QMessageBox::information(0, "Error", errormsg.c_str());
                        }
                    }
                }

            } else { //folder

                QString folderName = folderDirModel->fileName(ui->foldersTreeView->currentIndex());

                //create folder in destination
                if(QDir().mkdir(workingFolderPath+"/"+folderName)){
                    //copy files from the source folder to the previously created one
                    QString command = "Xcopy /E \""+folderDirModel->filePath(ui->foldersTreeView->currentIndex())+"\" \""+workingFolderPath+"/"+folderName+"\"";
                    WinExec(command.toStdString().c_str(), SW_HIDE);

                    string errormsg = "";
                    checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+folderName.toStdString()+"\"", checkinmsg.toStdString(), errormsg);
                    if (errormsg!="") {
                        QMessageBox::information(0, "Error", errormsg.c_str());
                    }
                } else {
                    QMessageBox::information(0, "Error", "Unsuccesful copy of folder.");
                }
            }
            //signal emitted for the mainwindow to refresh folders' and files' list
            emit newFileAdded();
        }
        else {
            QMessageBox::information(0, "Error", "Aborting check in due to empty message.");
        }
    }
}

//the accesibility to view a file changes based on the number of files selected
void AddDialog::changeStateViewButton()
{
    if (ui->filesTreeView->selectionModel()->selectedIndexes().size()==4) { //only one file can be selected for view
        ui->viewFileButton->setEnabled(true);
    } else {
        ui->viewFileButton->setEnabled(false); // action not performed if there's more than one file selected
    }
}

void AddDialog::viewFile()
{
    QFile file(fileDirModel->fileInfo(ui->filesTreeView->currentIndex()).filePath());

    //check if file exists
    if (!file.exists()){
        QMessageBox::information(0, "error", file.errorString());
    } else {

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
