rem $Date:   Sep 22 1997 11:56:14  $
rem $Revision:   1.1  $
rem $Author:   SJR  $

rem Builds the DEF file - and deletes the .DLL - forcing a relink next time
rem

rem DLLXPT is a sharewware _AFXDLL DEF file tool created by Paul Fonte (CIS:76500,3534)

SETLOCAL
set root=mrcext4

rem echo dragdock.obj framewnd.obj moverect.obj sizecont.obj sizedock.obj mrcanima.obj clrlabel.obj dib.obj > objs.lst
echo dragdock.obj > objs.lst
echo framewnd.obj >> objs.lst
echo sizecont.obj >> objs.lst
echo sizedock.obj >> objs.lst
echo mrcanima.obj >> objs.lst
echo clrlabel.obj >> objs.lst
echo dib.obj      >> objs.lst
echo bmpbtn.obj   >> objs.lst
echo sizedlg.obj  >> objs.lst
echo sztoolba.obj >> objs.lst
echo cfgtbar.obj  >> objs.lst

cd debug
DLLXPT /r..\%root%d.def /o..\%root%d.def @..\objs.lst
del ..\bin\mrcex42d.dll

CD ..\release
DLLXPT /r..\%root%.def /o..\%root%.def @..\objs.lst
del ..\bin\mrcex42.dll
