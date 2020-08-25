@echo off

cd %1
git add %2
git commit -m %3

FINDSTR /v %2 "vss.zsu" > "vss_copy.zsu"
copy "vss_copy.zsu"  "vss.zsu"
del "vss_copy.zsu"


