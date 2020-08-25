@echo off

cd %1
git add %2
git commit -m %3

FINDSTR /v %2 "db.vss" > "db_copy.vss"
copy "db_copy.vss"  "db.vss"
del "db_copy.vss"


