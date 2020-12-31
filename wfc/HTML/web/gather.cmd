@echo off
REM $Revision: $
REM $Modtime: 3/26/98 7:50p $
REM This CMD file is used by Sam Blackburn to create releases
REM of WFC. You should ignore this file.
REM Make sure you use HTML.EXE Revision 7 or higher
e:
cd \
cd wfc
cd html
cd web
del *.h*
copy d:\html\classes.htm
copy d:\html\coding.htm
copy d:\html\pax.htm
copy d:\html\release*.htm
copy d:\html\samples.htm
copy d:\html\timebeg.htm
copy d:\html\title.htm
copy d:\html\wfc.htm
copy d:\html\homepage.htm
copy d:\html\WTN*.htm
copy d:\html\TechNotes.htm
