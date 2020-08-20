@echo off 

cd %1
git fetch
git checkout -m %2
git add %2


FINDSTR %2 "vss.zsu">NUL

if %ERRORLEVEL% EQU 1 (
	echo %2>>"vss.zsu"
) 
