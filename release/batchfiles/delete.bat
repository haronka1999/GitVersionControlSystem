@echo off

cd %1
git rm -r --cached %2
git commit -m "delete"

FINDSTR /v %2 "db.vss" > "db_copy.vss"
copy "db_copy.vss"  "db.vss"
del "db_copy.vss"
