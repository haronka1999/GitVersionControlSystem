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

    //loading folders into the treeview(right side)--------------------------------------------------------
    folderDirModel = new QFileSystemModel();
    folderDirModel->setRootPath("");
    folderDirModel->setFilter(QDir::Drives | QDir::AllDirs |   QDir::NoDotAndDotDot);
    ui->foldersTreeView->setModel(folderDirModel);

    for (int i = 1; i < folderDirModel->columnCount(); ++i) {
        ui->foldersTreeView->hideColumn(i);
        ui->filesTreeView->hideColumn(i);
    }

    ui->folderNameLabel->setText(folderDirModel->fileInfo(ui->foldersTreeView->currentIndex()).filePath());

    //buttons----------------------------------------------------------------------------------------------
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));

    //disabled by default until file is selected (or when folder is selected)
    ui->viewFileButton->setEnabled(false);
    connect(ui->filesTreeView, SIGNAL(pressed(QModelIndex)), this, SLOT(changeStateViewButton()));

    //removes the whatisthis hint plugin
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void AddDialog::setTreeWidget(QString path, QTreeWidget* filesTree, QTreeWidgetItem *item)
{
    destinationPath = path;
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

//the accesibility to view a file changes based on the number of files selected
void AddDialog::changeStateViewButton()
{
    if (ui->filesTreeView->selectionModel()->selectedIndexes().size()==4) { //only one file can be selected for view
        ui->viewFileButton->setEnabled(true);
    } else {
        ui->viewFileButton->setEnabled(false); // action not performed if there's more than one file selected
    }
}

//a folder was clicked
void AddDialog::deselectFiles()
{
    if (ui->foldersTreeView->selectionModel()->selectedIndexes().size()!=0){
        ui->filesTreeView->selectionModel()->clearSelection();
        ui->viewFileButton->setEnabled(false);
    }
}

//a file was clicked
void AddDialog::deselectFolder()
{
    if (ui->filesTreeView->selectionModel()->selectedIndexes().size()!=0){
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
//0-file is not in the repo
//1-file is in the repo, but it can be overwritten
//2-file is in the repo, but it can't be overwritten
int AddDialog::fileReadyToBeUploaded(QString fileName)
{
    if (filesTreewidget->findItems(fileName, Qt::MatchExactly, 0).size()!=0) { //match for the name was found

        //consent to whether or not overwrite the file
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Error: "+ fileName, "A file named " + fileName + " already exists in in your project. Do you wish to overwrite it?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            return 1;
        } else {
            return 2;
        }

    } else {
        return 0;
    }
}

void AddDialog::addFile(string checkinmsg)
{
    //list of file names to be uploaded into the files' treewidget(at the top)
    QList<QTreeWidgetItem *> newFileList;

    QModelIndexList fileind = ui->filesTreeView->selectionModel()->selectedIndexes();

    //looping through the selected files' list
    for (int i = 0; i < fileind.count(); i+=4){

        QString fileName = fileDirModel->fileName(fileind.at(i));
        int result = fileReadyToBeUploaded(fileName);
        if (result<2) {

            // upload file in the working directory
            //if the file already exists in the working folder, it needs to be deleted
            QString pathToFile = destinationPath+"/"+fileName;
            if(QFile::exists(pathToFile)) {
                QFile::remove(pathToFile);
            }

            if (!QFile::copy(fileName, pathToFile)) {
                QMessageBox::information(0, "Error", "Unsuccesful copy into working folder.");
            } else {
                //if it was successfully copied, it is ready to be checked in
                string errormsg = "";
                checkIn("\""+destinationPath.toStdString()+"\"", ("\""+destinationPath+"/"+fileName+ "\"").toStdString(), checkinmsg, errormsg);

                if (errormsg!="") {
                    QMessageBox::information(0, "Error", errormsg.c_str());
                } else {
                    //file is not present in the widget, so it can be added
                    if(result==0) {
                        QTreeWidgetItem *item = new QTreeWidgetItem;
                        item->setText(0, fileName);
                        newFileList.push_back(item);
                    }
                }
            }
        }
    }

    //upload new files into the mainwindow's widget
    if (newFileList.size()!=0) {
        filesTreewidget->insertTopLevelItems(0, newFileList);
    }
}

//making sure that there's no folder in the selected folder with the exact same name
//0-folder is not in the repo
//1-folder is in the repo, but it can be overwritten
//2-folder is in the repo, but it can't be overwritten
int AddDialog::folderReadyToBeUploaded(QString folderName)
{
    int childnr = parentFolder->childCount();

    for(int i=0; i<childnr; i++) {
        if(parentFolder->child(i)->text(0)==folderName) { //check if there's a child folder, in the parent item, with this name
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Error: "+ folderName, "A folder named " + folderName + " already exists in in your project. Do you wish to overwrite it?", QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;
}

void AddDialog::addFolder(string checkinmsg)
{
    QString folderName = folderDirModel->fileName(ui->foldersTreeView->currentIndex());
    int result = folderReadyToBeUploaded(folderName);
    if(result<2) {

        //create folder in destination
        QString pathToFolder = destinationPath+"/"+folderName;
        if(QFile::exists(pathToFolder)) {
            QDir dir(pathToFolder);
            dir.removeRecursively();
        }
        QDir().mkdir(pathToFolder);

        //copy files from the source folder to the previously created one
        WinExec(("Xcopy /E \""+folderName+"\" \""+pathToFolder+"\"").toStdString().c_str(), SW_HIDE);

        string errormsg = "";
        checkIn("\""+destinationPath.toStdString()+"\"", ("\""+destinationPath+"/"+folderName+"\"").toStdString(), checkinmsg, errormsg);

        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        } else {
            //upload new folder into the folders' treewidget
            QTreeWidgetItem *item = new QTreeWidgetItem;
            item->setText(0, folderName);
            if(parentFolder->parent()) { //check if topLevelItem(in that case is "")
                item->setText(1, parentFolder->text(1)+"/"+folderName);
            } else {
                item->setText(1, folderName);
            }
            //if folder's already in the widget, no need to added twice
            if(result==0) {
                parentFolder->addChild(item);
            }
        }
    }
}

void AddDialog::viewFile()
{
    QFile file(fileDirModel->fileInfo(ui->filesTreeView->currentIndex()).filePath());

    //check if file exists
    if (!file.exists()){
        QMessageBox::information(0, "Error", file.errorString());
    } else {

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)!=0){
            QTextStream stream(&file);
            QTextBrowser *browser = new QTextBrowser();
            browser->setText(stream.readAll());
            browser->setGeometry(600, 180, 1000, 700);
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
