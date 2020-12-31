@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by HELP.HPJ. >"hlp\Help.hm"
echo. >>"hlp\Help.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Help.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Help.hm"
echo. >>"hlp\Help.hm"
echo // Prompts (IDP_*) >>"hlp\Help.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Help.hm"
echo. >>"hlp\Help.hm"
echo // Resources (IDR_*) >>"hlp\Help.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Help.hm"
echo. >>"hlp\Help.hm"
echo // Dialogs (IDD_*) >>"hlp\Help.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Help.hm"
echo. >>"hlp\Help.hm"
echo // Frame Controls (IDW_*) >>"hlp\Help.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Help.hm"
echo // Common Controls (IDC_*) >>"hlp\Help.hm"
makehm IDC_,HIDC_,0x10000 resource.h >>"hlp\Help.hm"
REM -- Make help for Project HELP


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Help.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Help.hlp" goto :Error
if not exist "hlp\Help.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Help.hlp" Debug
if exist Debug\nul copy "hlp\Help.cnt" Debug
if exist Release\nul copy "hlp\Help.hlp" Release
if exist Release\nul copy "hlp\Help.cnt" Release
echo.
goto :done

:Error
echo hlp\Help.hpj(1) : error: Problem encountered creating help file

:done
echo.
