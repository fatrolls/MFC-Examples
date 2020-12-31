@echo off
zip -r -p wfc *.txt *.c *.h *.cpp *.hpp *.mak *.rc *.mc *.ver *.cmd
copy wfc.zip b:\
