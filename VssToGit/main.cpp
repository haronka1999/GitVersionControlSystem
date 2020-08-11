#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


//    string path = "C:/Users/zsuzsanna.magyari/Pictures/Saved Pictures";
//    string workdir = "\"" + path + "\"";
//    gitInit(workdir);

//    string filename = "C:/Users/zsuzsanna.magyari/Pictures/Saved Pictures/text.txt";
//    string file = "\"" + filename + "\"";
//    string errormsg = "";
//    add(workdir, file, errormsg);
//    std::cout << "error: " << errormsg << std::endl;


//    string foldername = "C:/Users/zsuzsanna.magyari/Pictures/Saved Pictures/fold";
//    string folder = "\"" + foldername + "\"";
//    errormsg = "";
//    add(workdir, folder, errormsg);
//    std::cout << "error: " << errormsg << std::endl;

//    errormsg = "";
//    checkIn(workdir, "work done", errormsg);
//    std::cout << "error: " << errormsg << std::endl;

//    errormsg = "";
//    checkoutFile(workdir, file, errormsg);
//    std::cout << "error: " << errormsg << std::endl;

//    filename = "text.txt";
//    file = "\"" + filename + "\"";
//    errormsg = "";
//    getFile(workdir, file, errormsg);
//    std::cout << "error: " << errormsg << std::endl;

//    errormsg = "";
//    getFolder(workdir, folder, errormsg);
//    std::cout << "error: " << errormsg << std::endl;
