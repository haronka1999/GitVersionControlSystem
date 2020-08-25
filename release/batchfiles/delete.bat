@echo off

cd %1
git rm -r --cached %2
git commit -m "delete"

FINDSTR /v %2 "vss.zsu" > "vss_copy.zsu"
copy "vss_copy.zsu"  "vss.zsu"
del "vss_copy.zsu"
