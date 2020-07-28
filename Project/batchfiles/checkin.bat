@echo off

for %%x in (%*) do (
	git add %%x
)

git commit -m "Commit done"


