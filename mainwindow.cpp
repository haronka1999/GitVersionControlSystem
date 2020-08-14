#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //first column-displayed basename
    //second column-path from working folder to the selected folder(hidden)
    //list of checked out files(hidden)
    ui->foldersTreeWidget->setColumnCount(3);
    ui->foldersTreeWidget->hideColumn(1);
    ui->foldersTreeWidget->hideColumn(2);

    //disable or enable tabs on the menu when abou to show
    connect(ui->menuEdit, SIGNAL(aboutToShow()), this, SLOT(menuEditClicked()));
    connect(ui->menuFile, SIGNAL(aboutToShow()), this, SLOT(menuFileClicked()));
    connect(ui->menuSourceSafe, SIGNAL(aboutToShow()), this, SLOT(menuSourceSafeClicked()));

    connect(ui->foldersTreeWidget, SIGNAL(itemClicked (QTreeWidgetItem*, int)), this, SLOT(expandFolder(QTreeWidgetItem*)));
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(takeAction(QAction*)));

    //default settings for the treewidgets---------------------------------------------------
    ui->checkInButton->setEnabled(false);
    ui->actionCheck_In->setDisabled(true);
    ui->filesTreeWidget->setHeaderLabel("Name");
    ui->foldersTreeWidget->setHeaderLabel("Name");
    ui->filesTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->foldersTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //if renaming the file was finished, changes can be commited
    connect(ui->filesTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(renameFileFinished(QTreeWidgetItem*)));
    //if renaming the folder was finished, changes can be commited
    connect(ui->foldersTreeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(renameFolderFinished(QTreeWidgetItem*)));

    //either a folder or a file/group of files can be selected (for check in and check out)
    connect(ui->foldersTreeWidget, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFiles()));
    connect(ui->filesTreeWidget, SIGNAL(pressed(const QModelIndex &)), this, SLOT(deselectFolder()));

    //enabling context menu on right click(widgets)
    ui->foldersTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->filesTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    //right click context menu on Dirs
    connect(ui->foldersTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(ShowContextMenuDirs(const QPoint &)));

    //right click context menu on Files
    connect(ui->filesTreeWidget, SIGNAL(customContextMenuRequested(const QPoint &)),this, SLOT(ShowContextMenuFiles(const QPoint &)));

    //buttons----------------------------------------------------------------------------------
    //edit and view buttons disabled by default until file selected
    ui->viewFileButton->setEnabled(false);
    ui->editFileButton->setEnabled(false);

    connect(ui->addFilesButton, SIGNAL(clicked(bool)), this, SLOT(addFiles()));
    connect(ui->setWorkingFolderButton, SIGNAL(clicked(bool)), this, SLOT(setWorkingFolder()));
    connect(ui->checkInButton, SIGNAL(clicked(bool)), this, SLOT(checkIn()));
    connect(ui->checkOutButton, SIGNAL(clicked(bool)), this, SLOT(checkOut()));
    connect(ui->viewFileButton, SIGNAL(clicked(bool)), this, SLOT(viewFile()));
    connect(ui->editFileButton, SIGNAL(clicked(bool)), this, SLOT(editFile()));
    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshWidgets()));
    connect(ui->helpButton, SIGNAL(clicked(bool)), this, SLOT(help()));

    connect(ui->filesTreeWidget, SIGNAL(pressed(QModelIndex)), this, SLOT(changeButtons()));
}


//enable/disable Edit and View buttons based on the number of files selected
void MainWindow::changeButtons()
{
    if (ui->filesTreeWidget->selectedItems().size()==1){
        ui->viewFileButton->setEnabled(true);
        ui->editFileButton->setEnabled(true);
    } else {
        ui->viewFileButton->setEnabled(false);
        ui->editFileButton->setEnabled(false);
    }
}


//context menu for files widget
void MainWindow::ShowContextMenuFiles(const QPoint &pos)
{
    //if no file was selected, the first one gets focus on
    if (ui->filesTreeWidget->selectedItems().size()==0) {
        ui->filesTreeWidget->setItemSelected(ui->filesTreeWidget->itemAt(QPoint(0,0)), true);
    }

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
    if (!ui->filesTreeWidget->currentItem()) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
        actionEdit.setDisabled(true);
        actionView.setDisabled(true);
        actionDelete.setDisabled(true);
        actionRename.setDisabled(true);
    } else {
        //check whether or not only one file is selected, because can't open, edit or rename mutiple at the same time
        if (ui->filesTreeWidget->selectedItems().size()!=1) {
            actionEdit.setDisabled(true);
            actionView.setDisabled(true);
            actionRename.setDisabled(true);
        }
    }
    contextMenu.exec(mapToParent(ui->filesTreeWidget->pos()+pos));
}


//context menu for folders widget
void MainWindow::ShowContextMenuDirs(const QPoint &pos)
{
    QMenu contextMenu(tr("menu"), this);
    contextMenu.pos() = pos;
    QAction action1("Create Project", this);

    QAction actionCheckIn("Check In", this);
    connect(&actionCheckIn, SIGNAL(triggered()), this, SLOT(checkIn()));
    contextMenu.addAction(&actionCheckIn);

    QAction actionCheckOut("Check Out", this);
    connect(&actionCheckOut, SIGNAL(triggered()), this, SLOT(checkOut()));
    contextMenu.addAction(&actionCheckOut);

    contextMenu.addSeparator();

    QAction actionDelete("Delete", this);
    connect(&actionDelete, SIGNAL(triggered()), this, SLOT(deleteSelected()));
    contextMenu.addAction(&actionDelete);

    QAction actionRename("Rename", this);
    connect(&actionRename, SIGNAL(triggered()), this, SLOT(renameSelected()));
    contextMenu.addAction(&actionRename);

    //if there's no content to display->disable actions
    if (ui->foldersTreeWidget->selectedItems().size()==0) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
        actionDelete.setDisabled(true);
        actionRename.setDisabled(true);
    }

    contextMenu.exec(mapToParent(ui->foldersTreeWidget->pos()+pos));
}


//updates the folders' and files' treewidget based on the clicked/ready to be expanded folder
void MainWindow::expandFolder(QTreeWidgetItem *parentItem)
{
    //if it was clicked on the current folder, there's no need for update
    if(workingDirName+"/"+parentItem->text(1)!=ui->selectedFolderLabel->text() || (parentItem->text(1)=="" && ui->selectedFolderLabel->text()==workingDirName)) {

        ui->filesTreeWidget->clear();
        QString line;
        string errormsg = "";
        vector<string> files = getFolder("\""+workingDirPath.toStdString()+"/"+parentItem->text(1).toStdString()+"\"", "\".\"", errormsg); //vector containing the file and folder names

        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        } else {
            //setting the label text to the expanded folder's path
            if(parentItem->parent()) {
                ui->selectedFolderLabel->setText(workingDirName+"/"+parentItem->text(1));
            } else {
                ui->selectedFolderLabel->setText(workingDirName);
            }


            //if folder was already expanded, only the filestreewidget needs update
            if (!parentItem->isExpanded()) {

                //looping through the vector of names
                for(int i = 0; i < files.size(); i++){

                    line = QString::fromStdString(files[i]);
                    QTreeWidgetItem *item = new QTreeWidgetItem();

                    //check if it's a file or a folder
                    if(!line.contains('/')) {

                        item->setText(0, line);
                        ui->filesTreeWidget->addTopLevelItem(item);

                    } else {
                        //handling possible folders
                        QString name = line.splitRef("/").first().toString(); //directory name

                        //check if it has already been added
                        int n = parentItem->childCount();
                        bool exists = false;
                        for(int i=0; i<n; i++){
                            if (parentItem->child(i)->text(0)==name) {
                                exists = true;
                                break;
                            }

                        }
                        if(!exists) {
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
            } else {
                //only filestreewidget need to be reloaded
                for(int i = 0; i < files.size(); i++){

                    line = QString::fromStdString(files[i]);
                    QTreeWidgetItem *item = new QTreeWidgetItem();

                    if(!line.contains('/')) { //check if it's a file
                        item->setText(0, line);
                        ui->filesTreeWidget->addTopLevelItem(item);
                    }
                }
            }
            parentItem->setExpanded(true);
        }
    }
}


//disable/enable Edit and View based on the number of files selected
void MainWindow::menuEditClicked()
{
    if (ui->filesTreeWidget->selectedItems().size()!=1){
        ui->actionEdit_File->setDisabled(true);
        ui->actionView_File->setDisabled(true);
    } else {
        ui->actionEdit_File->setDisabled(false);
        ui->actionView_File->setDisabled(false);
    }
}

//disable Rename if there is more than one file selected
void MainWindow::menuFileClicked()
{
    if (ui->filesTreeWidget->selectedItems().size()>1){
        ui->actionRename->setDisabled(true);
    } else {
        ui->actionRename->setDisabled(false);
    }
}

//disable/enable Check In based on the number of files checked out
void MainWindow::menuSourceSafeClicked()
{
    if (ui->filesTreeWidget->selectedItems().size()!=1){
        ui->actionCheck_In->setDisabled(true);
    } else {
        ui->actionCheck_In->setDisabled(false);
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
        menuEditClicked();
    }
}

//get deselected file name from Select Dialog(based on signal)
void MainWindow::getDeselectedName(QString name)
{
    QModelIndexList indexes = ui->filesTreeWidget->model()->match(ui->filesTreeWidget->model()->index(0, 0), Qt::DisplayRole, QVariant::fromValue(name), 1, Qt::MatchRecursive);

    if (indexes.size()!=0){
        ui->filesTreeWidget->setCurrentIndex(indexes[0]);
        ui->filesTreeWidget->selectionModel()->clearCurrentIndex();
        changeButtons();
        deselectFolder();
    }
}

void MainWindow::deselectFiles()
{
    if (ui->foldersTreeWidget->selectedItems().size()!=0 && ui->filesTreeWidget->selectedItems().size()!=0){
        ui->filesTreeWidget->selectionModel()->clearSelection();
    }
}

void MainWindow::deselectFolder()
{
    if (ui->filesTreeWidget->selectedItems().size()!=0 && ui->foldersTreeWidget->selectedItems().size()!=0){
        ui->foldersTreeWidget->selectionModel()->clearSelection();
    }
}

//actions---------------------------------------------------------------------------------------------------------------------------------------------

void MainWindow::createProject()
{
    cout <<"halo";
}

void MainWindow::addFiles()
{
    //first check if there's a working folder selected
    if (workingDirPath!="") {
        AddDialog *dialog = new AddDialog;

        //in order to help adding files to the selected destination, we pass the needed path
        dialog->setWorkingFolderPath(workingDirPath+"/"+ui->selectedFolderLabel->text().splitRef(workingDirName).last().toString());
        //passing the widgets over to the dialog in order to examine whether or not a file or folder is already added to the project
        QTreeWidgetItem* parentItem;
        if (ui->foldersTreeWidget->selectedItems().size()==0) {
            if (!(parentItem = ui->foldersTreeWidget->findItems(ui->selectedFolderLabel->text(), Qt::MatchContains|Qt::MatchRecursive, 0)[0])) {
                parentItem = ui->foldersTreeWidget->itemAt(0, 0);
            }
        } else {
            parentItem = ui->foldersTreeWidget->selectedItems()[0];
        }
        dialog->setTreeWidget(ui->filesTreeWidget, parentItem);

        //refreshing widgets after new files and folders have been added
        connect(dialog, SIGNAL(newFileAdded()), this, SLOT(refreshWidgets()));
        setEnabled(false);
        dialog->show();
        setEnabled(true);
    } else {
        QMessageBox::information(0, "Error", "You need to select your working folder first.");
    }
}

void MainWindow::setWorkingFolder()
{
    WorkingDirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();

    QString path = QString::fromStdString(dialog.pathToShow);

    //check if folder was selected and OK was pressed
    if (path!="" && dialog.isOkClicked) {
        ui->foldersTreeWidget->clear();
        ui->filesTreeWidget->clear();

        workingDirPath = path;
        workingDirName = path.splitRef("/").last().toString();
        ui->workingDirLabel->setText(workingDirName);
        ui->selectedFolderLabel->setText(workingDirName);

        //adding the working folder to the widget
        QTreeWidget *tree = ui->foldersTreeWidget;
        QTreeWidgetItem * topLevel = new QTreeWidgetItem();
        topLevel->setText(0, workingDirName);
        topLevel->setText(1, "");
        tree->addTopLevelItem(topLevel);
        topLevel->setSelected(true);

        //loading first depth files and folders into the widgets
        expandFolder(topLevel);
    }
}

void MainWindow::checkIn()
{
    CheckInDialog dialog;
    dialog.setModal(true);
    dialog.exec();

    string msg = dialog.getMessage().toStdString();

    QList<QTreeWidgetItem *> itemList = ui->filesTreeWidget->selectedItems();
    int filenr = itemList.size();

    if(filenr!=0){ //file or a group of files selected

        for (int i = 0; i < filenr; i+=4){
            string errormsg = "";

            if (errormsg!="") {
                QMessageBox::information(0, "Error", errormsg.c_str());
            }
        }

    } else { //folder
        string errormsg = "";

        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        }
    }
}

void MainWindow::checkOut()
{

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
    QString filePath = workingDirPath + '/' +  ui->filesTreeWidget->currentItem()->text(0);
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::viewFile()
{
    QString filePath = workingDirPath + '/' +  ui->filesTreeWidget->currentItem()->text(0);

    // if it's a direcotry
    if (!filePath.contains('.')){
        QMessageBox msgBox;
        msgBox.setText("It's a directory!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    QFile file(filePath);
    if(!file.exists()){
        QMessageBox::information(0,"error", file.errorString());
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        QTextBrowser *browser = new QTextBrowser();
        browser->setText(stream.readAll());
        browser->setGeometry(700,180,500,700);
        browser->show();
        browser->setWindowState(Qt::WindowState::WindowActive);
    }

    file.close();
}

void MainWindow::deleteSelected()
{
    QList<QTreeWidgetItem *> fileList = ui->filesTreeWidget->selectedItems();
    QTreeWidgetItem *file;
    if(fileList.size()!=0) { //file or a group of files to be deleted
        foreach(file, fileList) {
            string errormsg = "";
            deleteFile("\""+workingDirPath.toStdString()+"\"", "\""+(workingDirPath+"/"+ui->selectedFolderLabel->text().splitRef(workingDirName).last()+"/"+file->text(0)).toStdString()+"\"", errormsg);

            if (errormsg!="") {
                QMessageBox::information(0, "Error", errormsg.c_str());
            } else {
                delete file;
            }
        }
    } else { //folder
        string errormsg = "";
        QTreeWidgetItem *folder = +ui->foldersTreeWidget->currentItem();

        deleteFile("\""+workingDirPath.toStdString()+"\"", "\""+(workingDirPath+"/"+folder->text(1)).toStdString()+"\"", errormsg);
        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        } else {
            delete folder;
        }
        ui->filesTreeWidget->clear();
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
        if (ui->selectedFolderLabel->text()==workingDirName+"/") {
            path = "";
        } else {
            path = ui->foldersTreeWidget->findItems(ui->selectedFolderLabel->text(), Qt::MatchContains|Qt::MatchRecursive, 0)[0]->text(1)+"/";
        }

        string errormsg = "";
        ui->filesTreeWidget->blockSignals(true);

        renameFile("\""+workingDirPath.toStdString()+"\"", "\""+(path+oldName).toStdString()+"\"", "\""+(path+item->text(0)).toStdString()+"\"", errormsg);
        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        }
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui->filesTreeWidget->blockSignals(false);
    }
    oldName = "";
}

void MainWindow::renameFolderFinished(QTreeWidgetItem * item)
{
    QString newName = item->text(0);
    string errormsg = "";
    ui->foldersTreeWidget->blockSignals(true);

    QString pathStr = item->text(1).remove(item->text(1).length()-item->text(0).length(),item->text(0).length())+newName;
    renameFile("\""+workingDirPath.toStdString()+"\"", "\""+(item->text(1)).toStdString()+"\"", "\""+pathStr.toStdString()+"\"", errormsg);
    if (errormsg!="") {
        QMessageBox::information(0, "Error", errormsg.c_str());
    }
    item->setText(1, pathStr);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->foldersTreeWidget->blockSignals(false);

}


void MainWindow::refreshWidgets()
{

    //there's a working folder selected
    if (workingDirName!="") {

        QTreeWidgetItem *parentItem;
        if (ui->foldersTreeWidget->selectedItems().size()==0) {
            if (ui->selectedFolderLabel->text()==workingDirName+"/") {
                parentItem = ui->foldersTreeWidget->itemAt(0, 0);
            } else {
                parentItem = ui->foldersTreeWidget->findItems(ui->selectedFolderLabel->text(), Qt::MatchContains|Qt::MatchRecursive, 0)[0];
            }
        } else {
            parentItem = ui->foldersTreeWidget->selectedItems()[0];
        }

        ui->filesTreeWidget->clear();
        QString line;
        string errormsg = "";
        vector<string> files = getFolder("\""+workingDirPath.toStdString()+"/"+parentItem->text(1).toStdString()+"\"", "\".\"", errormsg); //vector containing the file and folder names

        if (errormsg!="") {
            QMessageBox::information(0, "Error", errormsg.c_str());
        } else {
            //looping through the vector of names
            for(int i = 0; i < files.size(); i++){

                line = QString::fromStdString(files[i]);
                QTreeWidgetItem *item = new QTreeWidgetItem();

                //check if it's a file or a folder
                if(!line.contains('/')) {

                    item->setText(0, line);
                    ui->filesTreeWidget->addTopLevelItem(item);

                } else {
                    //handling possible folders
                    QString name = line.splitRef("/").first().toString(); //directory name

                    //check if it has already been added
                    int n = parentItem->childCount();
                    bool exists = false;
                    for(int i=0; i<n; i++){
                        if (parentItem->child(i)->text(0)==name) {
                            exists = true;
                            break;
                        }

                    }
                    if(!exists) {
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
        }
    }
}

void MainWindow::help()
{
    QMessageBox msgBox;
        msgBox.setWindowTitle("Help");
        msgBox.setText("\t Software Description"
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

    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}