#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //first column-displayed basename
    //second column hidden-path from working folder to the selected folder
    ui->foldersTreeWidget->setColumnCount(2);
    ui->foldersTreeWidget->hideColumn(1);

    //disable or enable tabs on the menu when abou to show
    connect(ui->menuEdit, SIGNAL(aboutToShow()), this, SLOT(menuEditClicked()));
    connect(ui->menuSourceSafe, SIGNAL(aboutToShow()), this, SLOT(menuSourceSafeClicked()));

    connect(ui->foldersTreeWidget, SIGNAL(clicked(const QModelIndex &)),this,SLOT(showFiles()));
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(takeAction(QAction*)));

    //default settings for the treewidgets---------------------------------------------------
    ui->checkInButton->setEnabled(false);
    ui->actionCheck_In->setDisabled(true);
    ui->filesTreeWidget->setHeaderLabel("Name");
    ui->foldersTreeWidget->setHeaderLabel("Name");
    ui->filesTreeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->foldersTreeWidget->setSelectionMode(QAbstractItemView::SingleSelection);

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
    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(refreshFileList()));
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


    //activating actions------------------------------------------------------------------------

    //if there's no file to display->disable actions
    if (!ui->filesTreeWidget->currentItem()) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
        actionEdit.setDisabled(true);
        actionView.setDisabled(true);
    } else {
        //check whether or not only one file is selected, because can't open mutiple at the same time
        if (ui->filesTreeWidget->selectedItems().size()!=1) {
            actionEdit.setDisabled(true);
        }

        //check whether or not only one file is selected, because can't open mutiple at the same time
        if (ui->filesTreeWidget->selectedItems().size()!=1) {
            actionView.setDisabled(true);
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

    //if there's no content to display->disable actions
    if (!ui->filesTreeWidget->currentItem()) {
        actionCheckIn.setDisabled(true);
        actionCheckOut.setDisabled(true);
    }

    contextMenu.exec(mapToParent(ui->foldersTreeWidget->pos()+pos));
}

void MainWindow::showFiles()
{
    ui->filesTreeWidget->clear();
    string errormsg = "";


    QTreeWidgetItem *parentItem = ui->foldersTreeWidget->currentItem();
    ui->selectedFolderLabel->setText(workingDirPath.splitRef("/").last().toString()+"/"+parentItem->text(1));
    vector<string> files = getFolder("\""+workingDirPath.toStdString()+"/"+parentItem->text(1).toStdString()+"\"", "\".\"", errormsg);
    parentItem->setExpanded(true);

    if (errormsg!="") {
        QMessageBox::information(0, "Error", errormsg.c_str());
    } else {
        QString line;

        //fill first level of widgets
        for(int i = 0; i < files.size(); i++){

            line = QString::fromStdString(files[i]);
            QTreeWidgetItem *item = new QTreeWidgetItem();

            if(!line.contains('/')) { //check if it's a file or a folder
                item->setText(0, line);
                ui->filesTreeWidget->addTopLevelItem(item);
            } else { //handling possible folders
                QString name = line.splitRef("/").first().toString(); //directory name
                int n = parentItem->childCount();
                bool exists = false;

                //check if it has already been added
                for(int i=0; i<n; i++){
                    if (parentItem->child(i)->text(0)==name) {
                        exists = true;
                        break;
                    }

                }
                if(!exists) {
                    item->setExpanded(true);
                    item->setText(0, name);
                    item->setText(1, parentItem->text(1)+"/"+name);
                    parentItem->addChild(item);
                }
            }
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
        return refreshFileList();
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
//        ui->filesTreeWidget->setSortingEnabled(true);
//        ui->filesTreeWidget->sortByColumn(0, Qt::SortOrder::AscendingOrder);
//        ui->filesTreeWidget->setSortingEnabled(false);
        return;
    }

    if(action->objectName().toStdString()=="actionSize"){
//        ui->filesTreeWidget->setSortingEnabled(true);
//        ui->filesTreeWidget->sortByColumn(1, Qt::SortOrder::AscendingOrder);
//        ui->filesTreeWidget->setSortingEnabled(false);
        return;
    }

    if(action->objectName().toStdString()=="actionType"){
//        ui->filesTreeWidget->setSortingEnabled(true);
//        ui->filesTreeWidget->sortByColumn(2, Qt::SortOrder::AscendingOrder);
//        ui->filesTreeWidget->setSortingEnabled(false);
        return;
    }

    if(action->objectName().toStdString()=="actionDate"){
//        ui->filesTreeWidget->setSortingEnabled(true);
//        ui->filesTreeWidget->sortByColumn(3, Qt::SortOrder::AscendingOrder);
//        ui->filesTreeWidget->setSortingEnabled(false);
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
    ui->selectedFolderLabel->setText("Content of " + ui->foldersTreeWidget->currentItem()->text(0));
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
    AddDialog *dialog = new AddDialog;
    dialog->setWorkingFolderPath(workingDirPath);
    dialog->show();
}

void MainWindow::setWorkingFolder()
{
    WorkingDirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();

    ui->foldersTreeWidget->clear();
    ui->filesTreeWidget->clear();

    QString qstr = QString::fromStdString(dialog.pathToShow);
    string path = dialog.pathToShow;
    string errormsg = "";
    workingDirPath = qstr;

    // if ok was not pressed quit
    if (!dialog.isOkClicked)
        return;

    //add working folder name to folderswidget
    ui->workingDirLabel->setText("Working folder: "+qstr.splitRef("/").last().toString());
    ui->selectedFolderLabel->setText(qstr.splitRef("/").last().toString());

    QTreeWidget *tree = ui->foldersTreeWidget;
    QTreeWidgetItem * topLevel = new QTreeWidgetItem();
    topLevel->setText(0, qstr.splitRef("/").last().toString());
    topLevel->setText(1, qstr.splitRef("/").last().toString());
    tree->addTopLevelItem(topLevel);

    vector<string> files = getFolder("\""+path+"\"", "\".\"", errormsg);

    if (errormsg!="") {
        QMessageBox::information(0, "Error", errormsg.c_str());
    } else {
        QString line;
        topLevel->setExpanded(true);

        //fill first level of widgets
        for(int i = 0; i < files.size(); i++){

            line = QString::fromStdString(files[i]);
            QTreeWidgetItem *item = new QTreeWidgetItem();

            if(!line.contains('/')) { //check if it's a file or a folder
                item->setText(0, line);
                ui->filesTreeWidget->addTopLevelItem(item);
            } else { //handling possible folders
                QString name = line.splitRef("/").first().toString(); //directory name
                int n = topLevel->childCount();
                bool exists = false;

                //check if it has already been added
                for(int i=0; i<n; i++){
                    if (topLevel->child(i)->text(0)==name) {
                        exists = true;
                        break;
                    }

                }
                if(!exists) {
                    item->setText(0, name);
                    item->setText(1, name);
                    topLevel->addChild(item);
                }
            }
        }
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
    if ((ui->foldersTreeWidget->selectedItems()).size()!=0) {
        ui->filesTreeWidget->selectAll();
    }

    QList<QTreeWidgetItem *> fileList = ui->filesTreeWidget->selectedItems();
    QColor col(161, 169, 227);

    if (fileList.size()!=0) {
        foreach(QTreeWidgetItem *item, fileList)
        {
            for(int i=0; i<columncount; i++) {
                item->setBackgroundColor(i, col);
            }
        }
    }

    ui->filesTreeWidget->clearSelection();
    ui->checkInButton->setEnabled(true);
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
    dirModel = new QFileSystemModel(ui->filesTreeWidget);
    string path = dirModel->fileInfo(ui->filesTreeWidget->currentIndex()).filePath().toStdString();
    QString qstr = QString::fromStdString(path);
    QDesktopServices::openUrl(QUrl::fromLocalFile(qstr));
}

void MainWindow::viewFile()
{
    dirModel = new QFileSystemModel(ui->filesTreeWidget);
    string path = dirModel->fileInfo(ui->filesTreeWidget->currentIndex()).filePath().toStdString();
    QString qstr = QString::fromStdString(path);

    int pos=-1;
    for(int i =qstr.size()-1; i>= 0; i--){
        qDebug() << qstr[i];
        if (qstr[i] == '/'){
            pos = i;
            break;
        }
    }
    if (pos==-1){
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();
    }
    QString fileName = qstr.right(qstr.size()-pos-1);

    // if it's a direcotry
    if (!fileName.contains('.')){
        QMessageBox msgBox;
        msgBox.setText("It's a directory!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QFile file(qstr);
    if(!file.exists()){
        QMessageBox::information(0,"error", file.errorString());
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        QTextBrowser *browser = new QTextBrowser();
        browser->setText(stream.readAll());
        browser->setGeometry(700,180,500,700);
        browser->show();
        browser->setWindowFlags(Qt::Window
                       | Qt::WindowMinimizeButtonHint
                       | Qt::WindowMaximizeButtonHint
                       | Qt::WindowCloseButtonHint);
        browser->setWindowState(Qt::WindowState::WindowActive);
    }
    file.close();
}


void MainWindow::refreshFileList()
{
    showFiles();
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
