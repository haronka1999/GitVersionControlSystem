@echo off 

cd %1
git fetch
git checkout -m %2
git add %2