@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX10D.HPJ. >"hlp\ex10d.hm"
echo. >>"hlp\ex10d.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ex10d.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ex10d.hm"
echo. >>"hlp\ex10d.hm"
echo // Prompts (IDP_*) >>"hlp\ex10d.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ex10d.hm"
echo. >>"hlp\ex10d.hm"
echo // Resources (IDR_*) >>"hlp\ex10d.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ex10d.hm"
echo. >>"hlp\ex10d.hm"
echo // Dialogs (IDD_*) >>"hlp\ex10d.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ex10d.hm"
echo. >>"hlp\ex10d.hm"
echo // Frame Controls (IDW_*) >>"hlp\ex10d.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ex10d.hm"
REM -- Make help for Project EX10D


echo Building Win32 Help files
hcw /C /E /M "hlp\ex10d.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ex10d.hlp" goto :Error
if not exist "hlp\ex10d.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ex10d.hlp" Debug
if exist Debug\nul copy "hlp\ex10d.cnt" Debug
if exist Release\nul copy "hlp\ex10d.hlp" Release
if exist Release\nul copy "hlp\ex10d.cnt" Release
echo.
goto :done

:Error
echo hlp\ex10d.hpj(1) : error: Problem encountered creating help file

:done
echo.
