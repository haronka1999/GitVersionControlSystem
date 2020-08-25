@echo off


set path = %1
set name = %2

set x = %path% and %name%

cd %1
git archive --format zip --output %x%.zip master