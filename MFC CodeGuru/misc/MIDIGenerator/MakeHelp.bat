@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by MIDIGENERATOR.HPJ. >"hlp\MIDIGenerator.hm"
echo. >>"hlp\MIDIGenerator.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\MIDIGenerator.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\MIDIGenerator.hm"
echo. >>"hlp\MIDIGenerator.hm"
echo // Prompts (IDP_*) >>"hlp\MIDIGenerator.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\MIDIGenerator.hm"
echo. >>"hlp\MIDIGenerator.hm"
echo // Resources (IDR_*) >>"hlp\MIDIGenerator.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\MIDIGenerator.hm"
echo. >>"hlp\MIDIGenerator.hm"
echo // Dialogs (IDD_*) >>"hlp\MIDIGenerator.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\MIDIGenerator.hm"
echo. >>"hlp\MIDIGenerator.hm"
echo // Frame Controls (IDW_*) >>"hlp\MIDIGenerator.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\MIDIGenerator.hm"
REM -- Make help for Project MIDIGENERATOR


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\MIDIGenerator.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\MIDIGenerator.hlp" goto :Error
if not exist "hlp\MIDIGenerator.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\MIDIGenerator.hlp" Debug
if exist Debug\nul copy "hlp\MIDIGenerator.cnt" Debug
if exist Release\nul copy "hlp\MIDIGenerator.hlp" Release
if exist Release\nul copy "hlp\MIDIGenerator.cnt" Release
echo.
goto :done

:Error
echo hlp\MIDIGenerator.hpj(1) : error: Problem encountered creating help file

:done
echo.
