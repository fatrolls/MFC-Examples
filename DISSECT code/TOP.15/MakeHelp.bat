@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TOP STUDIO.HPJ. >"hlp\Top Studio.hm"
echo. >>"hlp\Top Studio.hm"
echo // Dialogs (IDD_*) >>"hlp\Top Studio.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Top Studio.hm"
echo. >>"hlp\Top Studio.hm"

REM -- Make help for Project TOP STUDIO

start /wait hcw /C /E /M "Top Studio.hpj"
if %errorlevel% == 1 goto :Error
if exist Debug\nul copy "Top Studio.hlp" Debug
if exist Release\nul copy "Top Studio.hlp" Release
goto :done

:Error
echo Top Studio.hpj(1) : error: Problem encountered creating help file

:done
echo.
