@echo off
REM $Revision: 1 $
REM $Modtime: 10/01/98 6:34a $
REM Make sure you use HTML.EXE Revision 7 or higher
REM Change D: to the drive letter where you installed WFC
D:
cd \html
cd publish
del *.* /f /q
copy ..\homepage.htm
copy ..\Release*.htm
copy ..\WTN*.htm
copy ..\pax.htm
copy ..\coding.htm
copy ..\classes.htm
copy ..\samples.htm
copy ..\technotes.htm
copy ..\timebeg.htm
copy ..\title.htm
copy ..\wfc.htm
F:
cd \
cd wfc
cd src
html.exe -d:\html\publish *.cpp
d:
cd \
cd html
cd publish
REM Make the filenames acceptable to Compuserve
echo Preparing website (file renaming)
F:\Projects\PrepareWebSite\Release\PrepareWebSite.exe
