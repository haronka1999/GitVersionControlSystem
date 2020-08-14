@echo off

cd %1
git mv %2 %3
git commit -m "rename"