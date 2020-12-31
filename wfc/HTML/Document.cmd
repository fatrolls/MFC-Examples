@echo off
REM $Revision: 1 $
REM $Modtime: 10/01/98 6:34a $
REM Make sure you use HTML.EXE Revision 7 or higher
REM Change E: to the drive letter where you installed WFC
E:
cd \
cd wfc
cd html
copy web\*.*
cd ..
cd src
html.exe -\wfc\html *.cpp
