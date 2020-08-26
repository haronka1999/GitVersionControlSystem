@echo off

cd %1
git mv %2 %3
git commit -m "rename"

FINDSTR %2 "db.vss">NUL

if %ERRORLEVEL% EQU 0 (
	FINDSTR /v %2 "db.vss" > "db_copy.vss"
	copy "db_copy.vss"  "db.vss"
	del "db_copy.vss"
    echo %3>>"db.vss"
) 