@echo off
set WFC_PATH=F:\WFC
cd %WFC_PATH%
cd html
REM Delete everything in the HTML directory
del *.h*
REM Now copy over the files we need to let the user navigate on their home machine
cd web
copy d:\html\classes.htm
copy d:\html\coding.htm
copy d:\html\pax.htm
copy d:\html\release*.htm
copy d:\html\samples.htm
copy d:\html\timebeg.htm
copy d:\html\title.htm
copy d:\html\wfc.htm
copy d:\html\homepage.htm
copy d:\html\wtn*.htm
copy d:\html\TechNotes.htm
REM Go back up to the HTML directory
cd ..
REM Go back up to the WFC directory
cd ..
REM Make the temporary directory
REM WARNING! This probably won't work on your machine. Mine has
REM lots of room free on the C: drive but very little on D: (where
REM WFC resides)
f:
cd \
mkdir pax
cd pax
mkdir wfc
cd wfc
REM Copy all of the files for distribution.
REM C++ source code
xcopy d:*.cpp /s /e
REM Header Files
xcopy d:*.h* /s /e
REM CMD files
xcopy d:*.cmd /s /e
REM Message string resource files
xcopy d:*.mc /s /e
REM Resource scripts
xcopy d:*.rc /s /e
REM Release notes
xcopy d:*.txt /s /e
REM Make files
xcopy d:*.mak /s /e
REM Visual C++ make files
xcopy d:*.mdp /s /e
REM Visual C++ 5.0 Workspace files
xcopy d:*.dsw /s /e
REM Visual C++ 5.0 Project files
xcopy d:*.dsp /s /e
REM Icons
xcopy d:*.ico /s /e
REM other resource scipts
xcopy d:*.rc2 /s /e
REM Bitmaps
xcopy d:*.bmp /s /e
REM Version Information Resources
xcopy d:*.ver /s /e
REM XML sample files
xcopy d:*.xml /s /e
cd ..
REM Now pax the stuff. Although they don't tell you, the path specified by
REM the -f parameter to pax MUST BE IN ALL UPPERCASE LETTERS!!!!!
pax -w -f //C/TEMP/WFC.TAR .
REM now get rid of the directory tree
cd ..
rem deltree /Y pax
cd temp
