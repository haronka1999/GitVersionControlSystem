#pragma once

#ifdef GIT_DLL_EXPORTS
#define GIT_DLL_API __declspec(dllexport)
#else
#define GIT_DLL_API __declspec(dllimport)
#endif

#include <iostream>
#include "windows.h"
#include <stdexcept>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <shellapi.h>
#include <vector>

using namespace std;


GIT_DLL_API void gitInit(string pathtoWorkingDirectory);
GIT_DLL_API void add(string pathtoWorkingDirectory, string fileName, string& errorMessage);
GIT_DLL_API void deleteFile(string pathtoWorkingDirectory, string fileName, string& errorMessage);
GIT_DLL_API void renameFile(string pathtoWorkingDirectory, string oldName, string newName, string& errorMessage);
GIT_DLL_API bool isFileExisting(string pathtoWorkingDirectory, string fileName, string& errorMessage);
GIT_DLL_API bool checkoutFile(string pathtoWorkingDirectory, string fileName, string& message);
GIT_DLL_API void checkIn(string pathtoWorkingDirectory, string fileName, string commitMessage, string& errorMessage);
GIT_DLL_API vector<string> getFolder(string pathtoWorkingDirectory, string folderName, string& errorMessage);
GIT_DLL_API void getFile(string pathtoWorkingDirectory, string fileName, string& errorMessage);