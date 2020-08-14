#include "pch.h"
#include "Git_DLL.h"

void gitInit(string pathtoWorkingDirectory)
{
    string cmd = "batchfiles\\initrepo.bat " + pathtoWorkingDirectory;
	system(cmd.c_str());
}

void add(string pathtoWorkingDirectory, string fileName, string &errorMessage) {

	string str = pathtoWorkingDirectory + " " + fileName + " 2> out.txt";
	wstring widestr = wstring(str.begin(), str.end());
	const wchar_t* widecstr = widestr.c_str();
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = L"batchfiles\\add.bat";
	ShExecInfo.lpParameters = widecstr;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	ifstream out("out.txt");
	errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
	// Empty File
	if (errorMessage == "")
		cout << fileName << " added to repository" << endl;
	else
		cout << "errorMessage: " << errorMessage << endl;

	out.close();
	remove("out.txt");
}

bool isFileExisting(string pathtoWorkingDirectory, string fileName, string &errorMessage)
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
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());


    string emptyLine = "";
    if (errorMessage == emptyLine)
        fileExist = true;
    else
        fileExist = false;

    out.close();
    remove("out.txt");
    return fileExist;
}


void checkIn(string pathtoWorkingDirectory, string commitMessage, string &errorMessage) {

    string str = pathtoWorkingDirectory + " " + commitMessage + " 2> out.txt";
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
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    errorMessage = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    string emptyLine = "";
    if (errorMessage == emptyLine) {
        cout << "errorMessage: " << errorMessage << endl;
    }
    else {
        cout << "Commit was successful" << endl;
    }

    out.close();
    remove("out.txt");
}

bool checkoutFile(string pathtoWorkingDirectory, string fileName, string &message)
{
    bool checkedOut = false;
    string error = "";
    string str = pathtoWorkingDirectory + " " +  fileName + " 2> out.txt";
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    if (!isFileExisting(pathtoWorkingDirectory, fileName, error)) {
        add(pathtoWorkingDirectory, fileName, error);
    }

    cout << "Str: " << str << endl;

    SHELLEXECUTEINFO ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = L"batchfiles\\checkOut.bat";
    ShExecInfo.lpParameters = widecstr;
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream out("out.txt");
    message = string((istreambuf_iterator<char>(out)), istreambuf_iterator<char>());
    string fatal = message.substr(0, 5);
    // in case something goes wrong with the check out
    if (fatal == "fatal")
        checkedOut = false;
    else
        checkedOut = true;

    out.close();
    cout << "checkout-message: " << message << endl;
    remove("out.txt");

    return checkedOut;
}

void getFolder(string pathtoWorkingDirectory, string folderName, string &errorMessage)
{
    string str = pathtoWorkingDirectory + " " + folderName + " > outfoldr.txt 2> outerrf.txt";
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
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream outerrf("outerr.txt");
    errorMessage = string((istreambuf_iterator<char>(outerrf)), istreambuf_iterator<char>());
    outerrf.close();

    remove("outerrf.txt");
    ifstream outfoldr("outfoldr.txt");
    string line = "";
    int linenr = 0;
    if (errorMessage == "")
    {
        cout << endl << folderName << " contains the following:" << endl;
        while (getline(outfoldr, line)) {
            cout << line << endl;
            linenr++;
        }
        if (linenr == 0) {
            cout << "directory doesn't exist or it's empty" << endl;
        }
    }
    else {
        cout << "errorMessage: " << errorMessage << endl;
    }

    outfoldr.close();
    remove("outfoldr.txt");
}


void getFile(string pathtoWorkingDirectory, string fileName, string &errorMessage) {

    string str = pathtoWorkingDirectory + " " + fileName + " > outfile.txt 2> outerr.txt";
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
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    ifstream outerr("outerr.txt");
    errorMessage = string((istreambuf_iterator<char>(outerr)), istreambuf_iterator<char>());

    ifstream outfile("outfile.txt");
    string line = "";

    if (errorMessage == "")
    {
        while (getline(outfile, line)) {
            cout << line << endl;
        }
    }
    else {
        cout << errorMessage << endl;
    }

    outerr.close();
    remove("outerr.txt");
    outfile.close();
    remove("outfile.txt");
}
