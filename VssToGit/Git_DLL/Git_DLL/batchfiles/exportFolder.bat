@echo off


cd %1
git checkout-index -a -f --prefix=%1
tar.exe -a -c -f %2.zip %2
RMDIR /Q/S %2
