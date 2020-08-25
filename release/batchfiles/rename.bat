@echo off

cd %1
git mv %2 %3
git commit -m "rename"

FINDSTR %2 "vss.zsu">NUL

if %ERRORLEVEL% EQU 0 (
	FINDSTR /v %2 "vss.zsu" > "vss_copy.zsu"
	copy "vss_copy.zsu"  "vss.zsu"
	del "vss_copy.zsu"
    echo %3>>"vss.zsu"
) 