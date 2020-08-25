#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , checkedOutColor(255, 0, 0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //disable or enable tabs on the menu when abou to show
    connect(ui->menuEdit, SIGNAL(aboutToShow()), this, SLOT(menuEditClicked()));
    connect(ui->menuFile, SIGNAL(aboutToShow()), this, SLOT(menuFileClicked()));
    connect(ui->menuSourceSafe, SIGNAL(aboutToShow()), this, SLOT(menuSourceSafeClicked()));

    connect(ui->foldersTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(expandFolder(QTreeWidgetItem*)));
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(takeAction(QAction*)));

    //default settings for the treewidgets---------------------------------------------------
    ui->foldersTreeWidget->setColumnCount(2);
    ui->foldersTreeWidget->hideColumn(1);

    QStringList columnNames;
    columnNames.push_back("File Name");
    columnNames.push_back("Check Out Folder");
    ui->filesTreeWidget->setHeaderLabels(columnNames);
    ui->filesTreeWidget->setColumnWidth(0, 300);
    ui->foldersTreeWidget->setHeaderLabel("Folder Name");
    ui->filesTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->foldersTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //if renaming the file was finished, changes can be commited
    connect(ui->filesTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(renameFileFinished(QTreeWidgetItem*)));
    //if renaming the folder was finished, changes can be commited
    connect(ui->foldersTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(renameFolderFinished(QTreeWidgetItem*)));

    //either a folder or a file/group of files can be selected (for check in and check out)
    connect(ui->foldersTreeWidget, SIGNAL(pressed(const QModelIndex &)), this, SLOT(folderClicked()));
    connect(ui->filesTreeWidget, SIGNAL(pressed(const QModelIndex &)), this, SLOT(fileClicked()));

    //enabling context menu on right click(widgets)
    ui->foldersTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->filesTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    //right click context menu on Dirs
    connect(ui->foldersTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuDirs(const QPoint &)));

    //right click context menu on Files
    connect(ui->filesTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuFiles(const QPoint &)));

    //buttons----------------------------------------------------------------------------------
    //edit and view buttons disabled by default until file selected
    ui->viewFileButton->setDisabled(true);
    ui->editFileButton->setDisabled(true);
    ui->checkOutButton->setDisabled(true);
    ui->checkInButton->setDisabled(true);

    connect(ui->addFilesButton, SIGNAL(clicked(bool)), this, SLOT(addFiles()));
    connect(ui->setWorkingFolderButton, SIGNAL(clicked(bool)), this, SLOT(setWorkingFolder()));
    connect(ui->checkInButton, SIGNAL(clicked(bool)), this, SLOT(checkIn()));
    connect(ui->checkOutButton, SIGNAL(clicked(bool)), this, SLOT(checkOut()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));
    connect(ui->editFileButton, SIGNAL(clicked(bool)), this, SLOT(editFile()));
    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshWidgets()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(help()));

    //removes the whatisthis hint plugin
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

//context menu for files widget
void MainWindow::showContextMenuFiles(const QPoint &pos)
{
    ui->foldersTreeWidget->clearSelection();

    QMenu contextMenu(tr("menu"), this);
    contextMenu.pos() = pos;

    QAction actionCheckIn("Check In", this);
    connect(&actionCheckIn, SIGNAL(triggered()), this, SLOT(checkIn()));
    contextMenu.addAction(&actionCheckIn);

    QAction actionCheckOut("Check Out", this);
    connect(&actionCheckOut, SIGNAL(triggered()), this, SLOT(checkOut()));
    contextMenu.addAction(&actionCheckOut);

    contextMenu.addSeparator();

    QAction actionView("View", this);
    connect(&actionView, SIGNAL(triggered()), this, SLOT(viewFile()));
    contextMenu.addAction(&actionView);

    QAction actionEdit("Edit", this);
    connect(&actionEdit, SIGNAL(triggered()), this, SLOT(editFile()));
    contextMenu.addAction(&actionEdit);

    contextMenu.addSeparator();

    QAction actionDelete("Delete", this);
    connect(&actionDelete, SIGNAL(triggered()), this, SLOT(deleteSelected()));
    contextMenu.addAction(&actionDelete);

    QAction actionRename("Rename", this);
    connect(&actionRename, SIGNAL(triggered()), this, SLOT(renameSelected()));
    contextMenu.addAction(&actionRename);

    //activating actions------------------------------------------------------------------------

    //if there's no file to display->disable actions
    if (ui->filesTreeWidget->topLevelItemCount()==0) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
        actionEdit.setDisabled(true);
        actionView.setDisabled(true);
        actionDelete.setDisabled(true);
        actionRename.setDisabled(true);

    } else {
        //if no file was selected, the first one gets focus on

        int fileNr = ui->filesTreeWidget->selectedItems().size();
        //multiple files -> checkin, checkout enabled; rename, view, edit disabled
        if (fileNr==0) { //in case nothing is selected->first becomes current item
            ui->filesTreeWidget->itemAt(QPoint(0,0))->setSelected(true);
            ui->filesTreeWidget->setCurrentItem(ui->filesTreeWidget->itemAt(QPoint(0,0)));
            fileNr++;
        }
        if (fileNr!=1) {
            actionEdit.setDisabled(true);
            actionView.setDisabled(true);
            actionRename.setDisabled(true);
        } else {
            if(ui->filesTreeWidget->currentItem()->foreground(0).color().red()==255 && ui->filesTreeWidget->currentItem()->foreground(0).color().green()==0 && ui->filesTreeWidget->currentItem()->foreground(0).color().blue()==0) { //file is checked out
                actionCheckOut.setDisabled(true);
            } else {
                actionCheckIn.setDisabled(true);
                actionEdit.setDisabled(true);
            }
        }
    }
    contextMenu.exec(mapToParent(ui->filesTreeWidget->pos()+pos));
}


//context menu for folders widget
void MainWindow::showContextMenuDirs(const QPoint &pos)
{
    ui->filesTreeWidget->clearSelection();

    QMenu contextMenu(tr("menu"), this);
    contextMenu.pos() = pos;
    QAction action1("Create Project", this);

    QAction actionCheckIn("Check In", this);
    connect(&actionCheckIn, SIGNAL(triggered()), this, SLOT(checkIn()));
    contextMenu.addAction(&actionCheckIn);

    QAction actionCheckOut("Check Out", this);
    connect(&actionCheckOut, SIGNAL(triggered()), this, SLOT(checkOut()));
    contextMenu.addAction(&actionCheckOut);

    QAction actionExport("Export", this);
    connect(&actionExport, SIGNAL(triggered()), this, SLOT(exportFile()));
    contextMenu.addAction(&actionExport);

    contextMenu.addSeparator();

    QAction actionDelete("Delete", this);
    connect(&actionDelete, SIGNAL(triggered()), this, SLOT(deleteSelected()));
    contextMenu.addAction(&actionDelete);

    QAction actionRename("Rename", this);
    connect(&actionRename, SIGNAL(triggered()), this, SLOT(renameSelected()));
    contextMenu.addAction(&actionRename);

    //if there's no content to display->disable actions
    if (ui->foldersTreeWidget->topLevelItemCount()==0) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
        actionExport.setDisabled(true);
        actionDelete.setDisabled(true);
        actionRename.setDisabled(true);
    } else {
        if (ui->foldersTreeWidget->selectedItems().size()==0) {
            ui->foldersTreeWidget->itemAt(QPoint(0,0))->setSelected(true);
            ui->foldersTreeWidget->setCurrentItem(ui->foldersTreeWidget->itemAt(QPoint(0,0)));
        }
        expandFolder(ui->foldersTreeWidget->currentItem());

        //the working folder can't be renamed or deleted
        if (ui->selectedFolderLabel->text()==workingDirName) {
            actionRename.setDisabled(true);
            actionDelete.setDisabled(true);
        }
    }

    contextMenu.exec(mapToParent(ui->foldersTreeWidget->pos()+pos));
}


//updates the folders' and files' treewidget based on the clicked/ready to be expanded folder
void MainWindow::expandFolder(QTreeWidgetItem *parentItem)
{
    parentItem->setExpanded(true);

    QString oldName = ui->selectedFolderLabel->text();
    //setting the label text to the expanded folder's path
    if(parentItem->parent()) {
        ui->selectedFolderLabel->setText(workingDirName+"/"+parentItem->text(1));
    } else {
        ui->selectedFolderLabel->setText(workingDirName);
    }

    //if it was clicked on the current folder, there's no need for update
    if(oldName!=ui->selectedFolderLabel->text()) {

        string errorMessage = "";
        QString content;
        QString folderPath;
        //check if current folder is the working folder itself or not
        if (ui->selectedFolderLabel->text()!=workingDirName) {
            folderPath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString();
        } else {
            folderPath = ".";
        }

        if (vssFile.open(QIODevice::ReadOnly)) { //QFile::open - opens the file if that exists, else creates it
            content = vssFile.readAll();
        }
        vssFile.close();

        //if folder was already expanded, only the filestreewidget needs update
        if (parentItem->childCount()==0) {
            vector<string> files = getFolder(workingDirPath.toStdString(), folderPath.toStdString(), false, errorMessage); //vector containing the file and folder names

            if (errorMessage!="") {
                showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
            } else {
                displayFilesAndFolders(parentItem, content, files);
            }
        } else {
            vector<string> files = getFolder(workingDirPath.toStdString(), folderPath.toStdString(), true, errorMessage); //vector containing the file and folder names

            if (errorMessage!="") {
                showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
            } else {
                displayOnlyFiles(content, files);
            }
        }
    }
}

//files' treewidget refreshed
void MainWindow::displayOnlyFiles(QString content, vector<string> files)
{
    QString line, pathToDestination, filePath;
    ui->filesTreeWidget->clear();

    //only filestreewidget need to be reloaded
    for(unsigned int i = 0; i < files.size(); i++){

        line = QString::fromStdString(files[i]);
        QTreeWidgetItem *item = new QTreeWidgetItem();

        item->setText(0, line);
        ui->filesTreeWidget->addTopLevelItem(item);

        //check if current folder is the working folder itself or not
        if (ui->selectedFolderLabel->text()!=workingDirName) {
            pathToDestination = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/";
            filePath = pathToDestination+line;
        } else {
            pathToDestination = "";
            filePath = line;
        }

        if(content.contains("\"" + filePath + "\"")) {

            item->setText(1, workingDirPath+"/"+pathToDestination);
            for(int j=0; j<filesColumnCount; j++) {
                item->setForeground(j, checkedOutColor);
            }
        }

    }
}

void MainWindow::displayFilesAndFolders(QTreeWidgetItem *parentItem, QString content, vector<string> files)
{
    QString line, pathToDestination, filePath;
    ui->filesTreeWidget->clear();

    //looping through the vector of names
    for(unsigned int i = 0; i < files.size(); i++){

        line = QString::fromStdString(files[i]);
        QTreeWidgetItem *item = new QTreeWidgetItem();

        //check if it's a file or a folder
        if(!line.contains('/')) {

            item->setText(0, line);
            ui->filesTreeWidget->addTopLevelItem(item);
            //check if current folder is the working folder itself or not
            if (ui->selectedFolderLabel->text()!=workingDirName) {
                pathToDestination = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/";
                filePath = pathToDestination+line;
            } else {
                pathToDestination = "";
                filePath = line;
            }
            if(content.contains("\"" + filePath + "\"")) {
                item->setText(1, workingDirPath+"/"+pathToDestination);
                for(int j=0; j<filesColumnCount; j++) {
                    item->setForeground(j, checkedOutColor);
                }
            }

        } else {
            //handling possible folders
            QString name = line.splitRef("/").first().toString(); //directory name
            item->setText(0, name);
            //second hidden column helps keep track of the folder's path
            if(parentItem->parent()) {
                item->setText(1, parentItem->text(1)+"/"+name);
            } else {
                item->setText(1, name);
            }
            parentItem->addChild(item);

        }
    }
}


//disable/enable Edit and View based on the number of files selected and checked out status
void MainWindow::menuEditClicked()
{
    //multiple or nothing selected->disable
    //checked out->enable
    int fileNr = ui->filesTreeWidget->selectedItems().size();
    ui->actionEdit_File->setDisabled(true);
    ui->actionView_File->setDisabled(true);

    if (fileNr!=0) {
        if (fileNr==1) {
            ui->actionView_File->setDisabled(false);
            if(ui->filesTreeWidget->currentItem()->foreground(0).color().red()==255 && ui->filesTreeWidget->currentItem()->foreground(0).color().green()==0 && ui->filesTreeWidget->currentItem()->foreground(0).color().blue()==0) {
                ui->actionEdit_File->setDisabled(false);
            }
        }
    }
}

//disable Rename if there is more than one file selected
void MainWindow::menuFileClicked()
{
    int fileNr = ui->filesTreeWidget->selectedItems().size();
    ui->actionRename->setDisabled(true);
    ui->actionDelete->setDisabled(true);

    if (fileNr==0) {  //folders or nothing
        //working directory can't neither remained nor deleted
        if(ui->foldersTreeWidget->selectedItems().size()!=0) {
            if(ui->selectedFolderLabel->text()!=workingDirName) {
                ui->actionRename->setDisabled(false);
                ui->actionDelete->setDisabled(false);
            }
        }

    } else { //files
        ui->actionDelete->setDisabled(false);
        if (fileNr==1){ //one file selected
            ui->actionRename->setDisabled(false);
        }
    }
}

//disable/enable Check In based on the number of files checked out
void MainWindow::menuSourceSafeClicked()
{
    int fileNr = ui->filesTreeWidget->selectedItems().size();
    //default for nothing being selected
    ui->actionCheck_Out->setDisabled(true);
    ui->actionCheck_In->setDisabled(true);

    if (fileNr>1 || ui->foldersTreeWidget->selectedItems().size()!=0) { //group of files or folder
            ui->actionCheck_Out->setDisabled(false);
            ui->actionCheck_In->setDisabled(false);
    } else { //files
        if  (fileNr==1) {
            if(ui->filesTreeWidget->currentItem()->foreground(0).color().red()==255 && ui->filesTreeWidget->currentItem()->foreground(0).color().green()==0 && ui->filesTreeWidget->currentItem()->foreground(0).color().blue()==0) { //checked out
                ui->actionCheck_In->setDisabled(false);
            } else {
                ui->actionCheck_Out->setDisabled(false);
            }
        }
    }
}

void MainWindow::takeAction(QAction*action)
{
    if(action->objectName().toStdString()=="actionSelect"){
        return selectFile();
    }

    if(action->objectName().toStdString()=="actionSelect_All"){
        return selectAllFiles();
    }

    if(action->objectName().toStdString()=="actionRefresh_file_list"){
        return refreshWidgets();
    }

    if(action->objectName().toStdString()=="actionCheck_In"){
        return checkIn();
    }

    if(action->objectName().toStdString()=="actionCheck_Out"){
        return checkOut();
    }

    if(action->objectName().toStdString()=="actionEdit_File"){
        return editFile();
    }

    if(action->objectName().toStdString()=="actionView_File"){
        return viewFile();
    }

    if(action->objectName().toStdString()=="actionAdd_files"){
        return addFiles();
    }

    if(action->objectName().toStdString()=="actionSet_Working_Folder"){
        return setWorkingFolder();
    }

    if(action->objectName().toStdString()=="actionHelp"){
        return help();
    }

    if(action->objectName().toStdString()=="actionExit"){
        close();
    }

    if(action->objectName().toStdString()=="actionDelete"){
        return deleteSelected();
    }

    if(action->objectName().toStdString()=="actionRename"){
        return renameSelected();
    }

    if(action->objectName().toStdString()=="actionName"){
        ui->filesTreeWidget->setSortingEnabled(true);
        ui->filesTreeWidget->sortByColumn(0, Qt::SortOrder::AscendingOrder);
        ui->filesTreeWidget->setSortingEnabled(false);
        return;
    }
}

//get selected file name from Select Dialog(based on signal)
void MainWindow::getSelectedName(QString name)
{
    QModelIndexList indexes = ui->filesTreeWidget->model()->match(ui->filesTreeWidget->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(name), 1, Qt::MatchRecursive);

    if (indexes.size()!=0){
        ui->filesTreeWidget->selectionModel()->select(indexes[0],  QItemSelectionModel::Rows | QItemSelectionModel::Select);
    }
}

//get deselected file name from Select Dialog(based on signal)
void MainWindow::getDeselectedName(QString name)
{
    QModelIndexList indexes = ui->filesTreeWidget->model()->match(ui->filesTreeWidget->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(name), 1, Qt::MatchRecursive);

    if (indexes.size()!=0){
        ui->filesTreeWidget->setCurrentIndex(indexes[0]);
        ui->filesTreeWidget->selectionModel()->clearCurrentIndex();
    }
}

void MainWindow::folderClicked()
{
    ui->filesTreeWidget->selectionModel()->clearSelection();
    ui->viewFileButton->setDisabled(true);
    ui->editFileButton->setDisabled(true);

    if (ui->foldersTreeWidget->selectedItems().size()==0) {
        ui->checkInButton->setDisabled(true);
        ui->checkOutButton->setDisabled(true);
    } else {
        ui->checkInButton->setDisabled(false);
        ui->checkOutButton->setDisabled(false);
    }
}

void MainWindow::fileClicked()
{
    int fileNr  = ui->filesTreeWidget->selectedItems().size();
    ui->viewFileButton->setDisabled(false);
    ui->checkOutButton->setDisabled(false);
    ui->checkInButton->setDisabled(false);
    ui->editFileButton->setDisabled(false);

    if (fileNr!=0) {
        ui->foldersTreeWidget->selectionModel()->clearSelection();

        //check whether or not only one file is selected, because can't open, edit or rename mutiple at the same time
        if (fileNr==1) {
            //checked out->edit, check in enabled; check out disabled
            if(ui->filesTreeWidget->currentItem()->foreground(0).color().red()==255 && ui->filesTreeWidget->currentItem()->foreground(0).color().green()==0 && ui->filesTreeWidget->currentItem()->foreground(0).color().blue()==0) { //checked out
                ui->checkOutButton->setDisabled(true);
            } else {
                ui->checkInButton->setDisabled(true);
                ui->editFileButton->setDisabled(true);
            }
        } else {
            if (fileNr==0) {
                ui->checkOutButton->setDisabled(true);
                ui->checkInButton->setDisabled(true);
            }
            ui->editFileButton->setDisabled(true);
            ui->viewFileButton->setDisabled(true);
        }
    } else {
        ui->viewFileButton->setDisabled(true);
        ui->checkOutButton->setDisabled(true);
        ui->checkInButton->setDisabled(true);
        ui->editFileButton->setDisabled(true);
    }
}

//actions---------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::exportFile()
{

    // in case the selected folder is the top folder
    if ( ui->selectedFolderLabel->text() == workingDirName){
        exportProject(workingDirPath.toStdString() + "/", workingDirName.toStdString());
    }else{
        exportFolder(workingDirPath.toStdString() + "/", (ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()).last().toString()).toStdString().erase(0,1));
    }

    showMessage("ButtonImages/success.jpg", "Message", "Project was exported");
}

void MainWindow::addFiles()
{
    //first check if there's a working folder selected
    if (workingDirPath!="") {
        AddDialog *dialog = new AddDialog;
        QString destinationPath;

        //passing the widgets over to the dialog in order to examine whether or not a file or folder is already added to the project and to be able to upload the new items
        QTreeWidgetItem* parentItem;
        if (ui->foldersTreeWidget->selectedItems().size()==0) {
            if (!(parentItem = ui->foldersTreeWidget->findItems(ui->selectedFolderLabel->text(), Qt::MatchContains|Qt::MatchRecursive, 0)[0])) {
                parentItem = ui->foldersTreeWidget->itemAt(0, 0);
            }
        } else {
            parentItem = ui->foldersTreeWidget->selectedItems()[0];
        }

        //check if current folder is the working folder itself or not
        if (ui->selectedFolderLabel->text()!=workingDirName) {
            destinationPath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString();
        } else {
            destinationPath = "";
        }
        dialog->setTreeWidget(workingDirPath, destinationPath, ui->filesTreeWidget, parentItem);

        setDisabled(true);
        dialog->show();
        setDisabled(false);
    } else {
        showMessage("ButtonImages/error.png", "Error", "You need to select your working folder first.");
    }
}

void MainWindow::setWorkingFolder()
{
    WorkingDirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();

    QString path = QString::fromStdString(dialog.pathToShow);

    //folder was selected and OK was pressed
    if (path!="" && dialog.isOkClicked) {

        ui->foldersTreeWidget->clear();
        ui->checkInButton->setDisabled(false);
        ui->checkOutButton->setDisabled(false);

        workingDirPath = path;
        workingDirName = path.splitRef("/").last().toString();
        ui->workingDirLabel->setText(workingDirName);
        //setting the path to the vss db file
        vssFile.setFileName(workingDirPath+"/"+"db.vss");
        //creates file if it doesn't exist
        if (vssFile.open(QIODevice::ReadWrite) ){}
        vssFile.close();

        //adding the working folder to the widget
        QTreeWidget *tree = ui->foldersTreeWidget;
        QTreeWidgetItem * topLevel = new QTreeWidgetItem();
        topLevel->setText(0, workingDirName);
        topLevel->setText(1, "");
        tree->addTopLevelItem(topLevel);
        tree->setCurrentItem(topLevel);
        topLevel->setSelected(true);

        //loading first depth files and folders into the widgets
        expandFolder(topLevel);
    }
}

void MainWindow::checkIn()
{
    CheckInDialog dialog;
    dialog.setModal(true);
    string errorMessage = "", commitMessage;
    QString filePath;
    dialog.exec();

    if (dialog.isOkClicked){
        commitMessage = dialog.getMessage().toStdString();
        QList<QTreeWidgetItem *> fileList = ui->filesTreeWidget->selectedItems();
        int fileNr = fileList.size();

        // if one file is selected
        if(fileNr!=0){

            for (int i = 0; i < fileNr; i+=4){
                //check if current folder is the working folder itself or not
                if (ui->selectedFolderLabel->text()!=workingDirName) {
                    filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+fileList[i]->text(0);
                } else {
                    filePath = fileList[i]->text(0);
                }

                //textcolor set to black color
                fileList[i]->setForeground(0, QColor(0, 0, 0));
                //checkout folder removed
                fileList[i]->setText(1, "");

                checkInFile(workingDirPath.toStdString(), filePath.toStdString(), commitMessage, errorMessage);
                if (errorMessage != ""){
                    showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
                }
            }
        }

        //folder selected
        else {
            fileNr = ui->filesTreeWidget->topLevelItemCount();

            for(int i=0; i<fileNr; i++) {
                //check if current folder is the working folder itself or not
                if (ui->selectedFolderLabel->text()!=workingDirName) {
                    filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+ui->filesTreeWidget->topLevelItem(i)->text(0);
                } else {
                    filePath = ui->filesTreeWidget->topLevelItem(i)->text(0);
                }

                ui->filesTreeWidget->topLevelItem(i)->setForeground(0, QColor(0, 0, 0));
                ui->filesTreeWidget->topLevelItem(i)->setText(1, "");

                checkInFile(workingDirPath.toStdString(), filePath.toStdString(), commitMessage, errorMessage);
                if (errorMessage != ""){
                    showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
                }
            }
        }
    }
}

void MainWindow::checkOut()
{
    string errorMessage  = "";
    QString name, filePath;
    //a file with own mimetype, which keeps track of the checked out files

    //check if there's a whole folder to be checked out
    if (ui->foldersTreeWidget->selectedItems().size()!=0) {
        ui->filesTreeWidget->selectAll();
    }

    //check if current folder is the working folder itself or not
    if (ui->selectedFolderLabel->text()!=workingDirName) {
        filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/";
    } else {
        filePath = "";
    }
    QList<QTreeWidgetItem *> fileList = ui->filesTreeWidget->selectedItems();
    QTreeWidgetItem *item;

    //looping through the selected file names
    foreach(item, fileList){
        name = filePath + item->text(0);

        //calling the bat file to be executed
        checkoutFile(workingDirPath.toStdString(), name.toStdString(), errorMessage);
        item->setText(1, workingDirPath+"/"+filePath);
        for(int j=0; j<filesColumnCount; j++) {
            item->setForeground(j, checkedOutColor);
        }
    }
}

void MainWindow::selectFile()
{
    SelectDialog *dialog = new SelectDialog;
    connect(dialog, SIGNAL(sendSelectedName(QString)), this, SLOT(getSelectedName(QString)));
    connect(dialog, SIGNAL(sendDeselectedName(QString)), this, SLOT(getDeselectedName(QString)));
    dialog->show();
}

void MainWindow::selectAllFiles()
{
    ui->filesTreeWidget->selectAll();
}

void MainWindow::editFile()
{
    string errorMessage = "";
    QString filePath;
    //check if current folder is the working folder itself or not
    if (ui->selectedFolderLabel->text()!=workingDirName) {
        filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+ui->filesTreeWidget->currentItem()->text(0);
    } else {
        filePath = ui->filesTreeWidget->currentItem()->text(0);
    }

    //get the latest version which is in the git
    getFile(workingDirPath.toStdString(), filePath.toStdString(), errorMessage);

    if(errorMessage!="") {
        showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
    } else {
        QString pth = "outfile.txt";
        QFile file(pth);
        fileEditor = new QTextEdit();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
            QTextStream stream(&file);
            fileEditor->setText(stream.readAll());
            fileEditor->setWindowIcon(QIcon("ButtonImages/editfile1.png"));
            fileEditor->setWindowTitle(ui->filesTreeWidget->currentItem()->text(0));
            fileEditor->setGeometry(700,180,1000,700);
            fileEditor->show();
            fileEditor->setWindowState(Qt::WindowState::WindowActive);
            QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), fileEditor);
            connect(shortcut, SIGNAL(activated()), this, SLOT(savePressed()));
        }
        file.close();
        file.remove();
    }
}

void MainWindow::savePressed()
{
    QString fileName = ui->filesTreeWidget->currentItem()->text(0);
    QString filePath;
    string commitMessage, errorMessage = "";
    QMessageBox msgBox;
    //check if current folder is the working folder itself or not
    if (ui->selectedFolderLabel->text()!=workingDirName) {
        filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+fileName;
    } else {
        filePath = fileName;
    }

    msgBox.setWindowIcon(QIcon("ButtonImages/error.png"));
    msgBox.setWindowTitle("Confirm");
    msgBox.setText("Are you sure want to save and checkIn?\t");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);

    if (msgBox.exec() == QMessageBox::Yes){
        CheckInDialog dialog;
        dialog.setModal(true);
        string errorMessage = "", commitMessage;
        dialog.exec();
        if (dialog.isOkClicked){
            string commitMessage = dialog.getMessage().toStdString();
            // this fileName cannot be changed, it's generated by the DLL
            QString pth = "outfile.txt";
            QFile file(pth);
            if (file.open(QIODevice::ReadWrite | QIODevice::Text)){
                file.write(fileEditor->toPlainText().toStdString().c_str());
                file.rename(ui->filesTreeWidget->currentItem()->text(0));
                file.close();
            }
            QString currentPath = QDir::currentPath()+ "/" + (ui->filesTreeWidget->currentItem()->text(0));
            QString destinationPath = workingDirPath + "/" + ui->filesTreeWidget->currentItem()->text(0);
            QFile destinationFile(destinationPath);
            if (destinationFile.exists()){
                destinationFile.remove();
            }
            if (!QFile::copy(currentPath, destinationPath)){
                showMessage("ButtonImages/error.png", "Error", "Error - file copy");
            }
            checkInFile(workingDirPath.toStdString(), filePath.toStdString(), commitMessage, errorMessage);
            if (errorMessage != ""){
                showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
            }else{
                showMessage("ButtonImages/success.jpg", "Message", "Check In success");
            }
        }
    } else {
        msgBox.close();
    }
}

void MainWindow::viewFile()
{
    string errorMessage = "";
    QString filePath;
    //check if current folder is the working folder itself or not
    if (ui->selectedFolderLabel->text()!=workingDirName) {
        filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+ui->filesTreeWidget->currentItem()->text(0);
    } else {
        filePath = ui->filesTreeWidget->currentItem()->text(0);
    }

    //get the latest version which is in the git
    getFile(workingDirPath.toStdString(), filePath.toStdString(), errorMessage);

    if (errorMessage!="") {
        showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
    } else {

        QString pth = "outfile.txt";
        QFile file(pth);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream stream(&file);
            QTextBrowser *browser = new QTextBrowser();
            browser->setText(stream.readAll());
            browser->setWindowTitle(ui->filesTreeWidget->currentItem()->text(0));
            browser->setWindowIcon(QIcon("ButtonImages/viewfile1.png"));
            browser->setGeometry(700, 180, 1000, 700);
            browser->show();
            browser->setWindowState(Qt::WindowState::WindowActive);
        }
        file.close();
        file.remove();
    }
}

void MainWindow::deleteSelected()
{
    QList<QTreeWidgetItem *> fileList = ui->filesTreeWidget->selectedItems();
    QTreeWidgetItem *file;
    if(fileList.size()!=0) { //file or a group of files to be deleted
        foreach(file, fileList) {
            string errorMessage = "";
            QString filePath;
            //check if current folder is the working folder itself or not
            if (ui->selectedFolderLabel->text()!=workingDirName) {
                filePath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/"+file->text(0);
            } else {
                filePath = file->text(0);
            }

            deleteFile(workingDirPath.toStdString(), filePath.toStdString(), errorMessage);

            if (errorMessage!="") {
                showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
            } else {
                delete file;
            }
        }
        fileClicked();
    } else { //folder
        string errorMessage = "";
        QTreeWidgetItem *folder = ui->foldersTreeWidget->currentItem();

        deleteFile(workingDirPath.toStdString(), folder->text(1).toStdString(), errorMessage);
        if (errorMessage!="") {
            showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
        } else {
            QTreeWidgetItem *parent = folder->parent();
            //setting the label text to the expanded folder's path
            if(parent->parent()) {
                ui->selectedFolderLabel->setText(workingDirName+"/"+parent->text(1));
            } else {
                ui->selectedFolderLabel->setText(workingDirName);
            }
            delete folder;
            ui->foldersTreeWidget->setCurrentItem(parent);
            parent->setSelected(true);
            folderClicked();
            refreshWidgets();
        }

    }
}

void MainWindow::renameSelected()
{

    if(ui->filesTreeWidget->selectedItems().size()!=0) { //file
        ui->filesTreeWidget->blockSignals(true);
        QTreeWidgetItem *file = ui->filesTreeWidget->selectedItems()[0];
        oldName = file->text(0);
        file->setFlags(file->flags()|Qt::ItemIsEditable);
        ui->filesTreeWidget->editItem(file, 0);
        ui->filesTreeWidget->blockSignals(false);

    } else { //folder
        ui->foldersTreeWidget->blockSignals(true);
        QTreeWidgetItem *folder = ui->foldersTreeWidget->selectedItems()[0];
        folder->setFlags(folder->flags()|Qt::ItemIsEditable);
        ui->foldersTreeWidget->editItem(folder, 0);
        ui->foldersTreeWidget->blockSignals(false);
    }
}

void MainWindow::renameFileFinished(QTreeWidgetItem * item)
{
    if (oldName!="") {
        QString path = "";
        if (ui->selectedFolderLabel->text()!=workingDirName) {
            path = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString()+"/";
        } else {
            path = "";
        }

        string errorMessage = "";
        ui->filesTreeWidget->blockSignals(true);

        renameFile(workingDirPath.toStdString(), (path+oldName).toStdString(), (path+item->text(0)).toStdString(), errorMessage);
        if (errorMessage!="") {
            showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
        }
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->filesTreeWidget->blockSignals(false);
    }
    oldName = "";
}

void MainWindow::renameFolderFinished(QTreeWidgetItem * item)
{
    QString newName = item->text(0);
    string errorMessage = "";
    ui->foldersTreeWidget->blockSignals(true);

    QString pathStr;
    if(item->parent()) {
        if  (item->parent()->text(1)!="") {
            pathStr = item->parent()->text(1)+"/"+newName;
        } else {
            pathStr = newName;
        }
    }

    renameFile(workingDirPath.toStdString(), (item->text(1)).toStdString(), pathStr.toStdString(), errorMessage);
    if (errorMessage!="") {
        showMessage("ButtonImages/error.png", "Error", errorMessage.c_str());
    }
    ui->selectedFolderLabel->setText(workingDirName+"/"+pathStr);
    item->setText(1, pathStr);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->foldersTreeWidget->blockSignals(false);
}


void MainWindow::refreshWidgets()
{
    //there's a working folder selected
    if (workingDirName!="") {

        QTreeWidgetItem *parentItem;
        QString line, content, folderPath;
        string errorMessage = "";

        if (ui->foldersTreeWidget->selectedItems().size()==0) {
            if (ui->selectedFolderLabel->text()==workingDirName) {
                parentItem = ui->foldersTreeWidget->topLevelItem(0);
            } else {
                parentItem = ui->foldersTreeWidget->findItems(ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString(), Qt::MatchContains|Qt::MatchRecursive, 0)[0];
            }
        } else {
            parentItem = ui->foldersTreeWidget->selectedItems()[0];
        }

        //check if current folder is the working folder itself or not
        if (ui->selectedFolderLabel->text()!=workingDirName) {
            folderPath = ui->selectedFolderLabel->text().splitRef(workingDirPath.splitRef("/").last().toString()+"/").last().toString();
        } else {
            folderPath = ".";
        }
        vector<string> files = getFolder(workingDirPath.toStdString(), folderPath.toStdString(), false, errorMessage); //vector containing the file and folder names

        if (errorMessage!="") {
            QMessageBox::information(0, "Error", errorMessage.c_str());
        } else {
            //remove subfolders
            foreach(auto i, parentItem->takeChildren()) delete i;

            if (vssFile.open(QIODevice::ReadOnly)) { //QFile::open - opens the file if that exists, else creates it
                content = vssFile.readAll();
            }

            vssFile.close();
            displayFilesAndFolders(parentItem, content, files);
        }
    }
}

void MainWindow::help()
{
    showMessage("ButtonImages/help3.png", "Help", "\t Software Description"
                                                  "\n"
                                                  "\n"
                                                  "This QUI provides the same functionalities\n"
                                                  "as the old Visual Source Safe version\n"
                                                  "control system but it works under Git."
                                                  "\n\n"
                                                  "......................................\n\n"
                                                  "Credits: Accenture\n"
                                                  "Date: 2020.08.28\n\n"
                                                  "Creators: Magyari Zsuzsanna\n"
                                                  "\tHorvath Aron\n\n");
}

void MainWindow::showMessage(QString iconPath, QString title, QString text)
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(iconPath));
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
