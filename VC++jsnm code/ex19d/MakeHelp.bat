@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by EX19D.HPJ. >"hlp\ex19d.hm"
echo. >>"hlp\ex19d.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ex19d.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ex19d.hm"
echo. >>"hlp\ex19d.hm"
echo // Prompts (IDP_*) >>"hlp\ex19d.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ex19d.hm"
echo. >>"hlp\ex19d.hm"
echo // Resources (IDR_*) >>"hlp\ex19d.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ex19d.hm"
echo. >>"hlp\ex19d.hm"
echo // Dialogs (IDD_*) >>"hlp\ex19d.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ex19d.hm"
echo. >>"hlp\ex19d.hm"
echo // Frame Controls (IDW_*) >>"hlp\ex19d.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ex19d.hm"
REM -- Make help for Project EX19D


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ex19d.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ex19d.hlp" goto :Error
if not exist "hlp\ex19d.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ex19d.hlp" Debug
if exist Debug\nul copy "hlp\ex19d.cnt" Debug
if exist Release\nul copy "hlp\ex19d.hlp" Release
if exist Release\nul copy "hlp\ex19d.cnt" Release
echo.
goto :done

:Error
echo hlp\ex19d.hpj(1) : error: Problem encountered creating help file

:done
echo.
