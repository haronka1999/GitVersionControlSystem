@echo off

cd %1
git rm -r --cached %2
git commit -m "delete"
