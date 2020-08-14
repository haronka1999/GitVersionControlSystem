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
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(showHelp()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

//it helps to keep track of the path where the added files are supposed to be uploaded
void AddDialog::setWorkingFolderPath(QString path)
{
    workingFolderPath = path;
}

void AddDialog::setTreeWidget(QTreeWidget* filesTree, QTreeWidgetItem *item)
{
    filesTreewidget = filesTree;
    parentFolder = item;
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

void AddDialog::add()
{
    //message
    bool ok;
    string checkinmsg = QInputDialog::getText(this, "Add Files Message", "Message:", QLineEdit::Normal, "", &ok, Qt::MSWindowsFixedSizeDialogHint|windowFlags() & ~Qt::WindowContextHelpButtonHint).toStdString();

    if (ok) { //dialog was closed with OK button
        if (checkinmsg!="") { //checkin message can't be empty

            if(ui->foldersTreeView->selectionModel()->selectedIndexes().size()==0){ //file or a group of files selected
                addFile(checkinmsg);

            } else { //folder
                addFolder(checkinmsg);
            }
        }
        else {
            QMessageBox::information(0, "Error", "Aborting check in due to empty message.");
        }
    }
}


//making sure that there's no file in the selected folder with the exact same name
bool AddDialog::fileReadyToBeUploaded(QString fileName)
{
    if (filesTreewidget->findItems(fileName, Qt::MatchExactly, 0).size()!=0) { //match for the name was found

        //consent to whether or not overwrite the file
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Error: "+ fileName, "A file named " + fileName + " already exists in in your project. Do you wish to overwrite it?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            return true;
        } else {
            return false;
        }

    } else {
        return true;
    }
}

void AddDialog::addFile(string checkinmsg)
{
    int uploadedFileNr = 0;     //number of uploeaded files without any bad result
    QModelIndexList fileind = ui->filesTreeView->selectionModel()->selectedIndexes();

    //looping through the selected files' list
    for (int i = 0; i < fileind.count(); i+=4){

        QString fileName = fileDirModel->fileName(fileind.at(i));

        if (fileReadyToBeUploaded(fileName)) {

            // upload file in the working directory
            //if the file already exists in the working folder, it needs to be deleted
            if(QFile::exists(workingFolderPath+"/"+fileName)) {
                QFile::remove(workingFolderPath+"/"+fileName);
            }

            if (!QFile::copy(fileDirModel->filePath(fileind.at(i)), workingFolderPath+"/"+fileName)) {
                QMessageBox::information(0, "Error", "Unsuccesful copy into working folder.");
            } else {
                //if it was successfully copied, it is ready to be checked in
                string errormsg = "";
                checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+fileName.toStdString()+ "\"", checkinmsg, errormsg);

                if (errormsg!="") {
                    QMessageBox::information(0, "Error", errormsg.c_str());
                } else {
                    uploadedFileNr++;
                }
            }
        }
    }

    //signal emitted for the mainwindow to refresh folders' and files' list
    if (uploadedFileNr>0) {
        emit newFileAdded();
    }
}

//making sure that there's no folder in the selected folder with the exact same name
bool AddDialog::folderReadyToBeUploaded(QString folderName)
{
    int n = parentFolder->childCount();

    for(int i=0; i<n; i++) {
        if(parentFolder->child(i)->text(0)==folderName) { //check if there's a child folder, in the parent item, with this name
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Error: "+ folderName, "A folder named " + folderName + " already exists in in your project. Do you wish to overwrite it?", QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                return true;
            } else {
                return false;
            }
        }
    }
    return true;
}

void AddDialog::addFolder(string checkinmsg)
{
    QString folderName = folderDirModel->fileName(ui->foldersTreeView->currentIndex());

    if(folderReadyToBeUploaded(folderName)) {

        //create folder in destination
        if(QFile::exists(workingFolderPath+"/"+folderName)) {
            QDir dir(workingFolderPath+"/"+folderName);
            dir.removeRecursively();
        }
        QDir().mkdir(workingFolderPath+"/"+folderName);

        //copy files from the source folder to the previously created one
        QString command = "Xcopy /E \""+folderDirModel->filePath(ui->foldersTreeView->currentIndex())+"\" \""+workingFolderPath+"/"+folderName+"\"";
        WinExec(command.toStdString().c_str(), SW_HIDE);

        string errormsg = "";
        checkIn("\""+workingFolderPath.toStdString()+"\"", "\""+workingFolderPath.toStdString()+"/"+folderName.toStdString()+"\"", checkinmsg, errormsg);

        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        } else {
            //signal emitted for the mainwindow to refresh folders' and files' list
            emit newFileAdded();
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
