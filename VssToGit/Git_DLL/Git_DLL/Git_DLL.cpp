#include "pch.h" 
#include <utility>
#include <limits.h>
#include "Git_DLL.h"


void exportProject(string pathtoWorkingDirectory, string projectName)
{
    string cmd = "batchfiles\\exportProject.bat \"" + pathtoWorkingDirectory + "\" \"" + projectName +"\"";
    WinExec(cmd.c_str(), SW_HIDE);
}

void exportFolder(string pathtoWorkingDirectory, string folderName)
{
    string cmd = "batchfiles\\exportFolder.bat \"" + pathtoWorkingDirectory + "\" \"" + folderName + "\"";
    WinExec(cmd.c_str(), SW_HIDE);
}


void gitInit(string pathtoWorkingDirectory)
{
    string cmd = "batchfiles\\initrepo.bat " + pathtoWorkingDirectory;
    WinExec(cmd.c_str(), SW_HIDE);
}

void deleteFile(string pathtoWorkingDirectory, string fileName, string& errorMessage)
{
    string str = "\"" + pathtoWorkingDirectory + "\" \"" + fileName + "\" 2> out.txt";
    wstring widestr = wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\delete.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    out.close();
    remove("out.txt");
}

void renameFile(string pathtoWorkingDirectory, string oldName, string newName, string& errorMessage)
{
    string str = "\"" + pathtoWorkingDirectory + "\" \"" + oldName + "\" \"" + newName + "\" 2> out.txt";
    wstring widestr = wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\rename.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    out.close();
    remove("out.txt");
}

bool isFileExisting(string pathtoWorkingDirectory, string fileName, string& errorMessage)
{
    bool fileExist = false;
    string str = pathtoWorkingDirectory + " " + fileName + " 2> out.txt";
    wstring widestr = wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\isFileExisting.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    out.close();
    remove("out.txt");
    return fileExist;
}


void checkInFile(string pathtoWorkingDirectory, string fileName, string commitMessage, string& errorMessage) {

    string str = "\"" + pathtoWorkingDirectory + "\" \"" + fileName + "\" \"" + commitMessage + "\" 2> out.txt";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\checkIn.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    out.close();
    remove("out.txt");
}

bool checkoutFile(string pathtoWorkingDirectory, string fileName, string& message)
{
    bool checkedOut = false;
    string str = "\"" + pathtoWorkingDirectory + "\" \"" + fileName + "\" 2> out.txt";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    
    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\checkOut.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    message = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    out.close();
    remove("out.txt");
    return checkedOut;
}

vector<string> getFolder(string pathtoWorkingDirectory, string folderName, bool onlyFiles, string& errorMessage)
{
    string str = "\"" + pathtoWorkingDirectory + "\" \"" + folderName + "\" > outfoldr.txt 2> outerrf.txt";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\getFolder.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream outerrf("outerr.txt");
    errorMessage = string((istreambuf_iterator<char>(outerrf)), istreambuf_iterator<char>());
    outerrf.close();

    remove("outerrf.txt");
    ifstream outfoldr("outfoldr.txt");
    string line = "";
    //the vector contains either file or folder names
    //difference: a folder name ends with an '/'
    vector <string> files;

    if (errorMessage == "")
    {
        int dirNameLength = 0;
        //the current folder's name needs to be removed from the lines in the result -> erase
        if (folderName != ".") { //check if it is the first level of the working folder
            dirNameLength = folderName.length()+1;
        }

        while (getline(outfoldr, line)) {
            line.erase(0, dirNameLength);

            //check if it is a file or a folder
            if (line.find("/") != std::string::npos) { //folder
                if (!onlyFiles) {
                    size_t found = line.find("/");
                    //first level depth names are to be shown->truncation
                    if (found != string::npos) {
                        line.erase(found + 1, line.length() - found - 1);
                    }
                    //if the folder's not already in the result vector, it shall be added
                    if (find(files.begin(), files.end(), line) == files.end()) {
                        files.push_back(line);
                    }
                }
            } else { //file
                files.push_back(line);
            }
        }
    }

    outfoldr.close();
    remove("outfoldr.txt");
    return files;
}

void getFile(string pathtoWorkingDirectory, string fileName, string& errorMessage) {

    ifstream outerr("outerr.txt"), outfile("outfile.txt");

    string str = "\"" + pathtoWorkingDirectory + "\" \"" + fileName + "\" > outfile.txt 2> outerr.txt";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\getFile.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    errorMessage = string((istreambuf_iterator<char>(outerr)), istreambuf_iterator<char>());

    outerr.close();
    outfile.close();
}