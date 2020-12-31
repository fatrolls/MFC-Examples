@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CSH.HPJ. >"hlp\CSH.hm"
echo. >>"hlp\CSH.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\CSH.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\CSH.hm"
echo. >>"hlp\CSH.hm"
echo // Prompts (IDP_*) >>"hlp\CSH.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\CSH.hm"
echo. >>"hlp\CSH.hm"
echo // Resources (IDR_*) >>"hlp\CSH.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\CSH.hm"
echo. >>"hlp\CSH.hm"
echo // Dialogs (IDD_*) >>"hlp\CSH.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\CSH.hm"
echo. >>"hlp\CSH.hm"
echo // Frame Controls (IDW_*) >>"hlp\CSH.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\CSH.hm"
REM -- Make help for Project CSH


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\CSH.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\CSH.hlp" goto :Error
if not exist "hlp\CSH.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\CSH.hlp" Debug
if exist Debug\nul copy "hlp\CSH.cnt" Debug
if exist Release\nul copy "hlp\CSH.hlp" Release
if exist Release\nul copy "hlp\CSH.cnt" Release
echo.
goto :done

:Error
echo hlp\CSH.hpj(1) : error: Problem encountered creating help file

:done
echo.
