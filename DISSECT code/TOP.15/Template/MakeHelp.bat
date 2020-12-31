@echo off
$$IF(MULTIPLE_LANGS || TARGET_MAC)

if "%1" == "?" goto :Error
if "%1" == "/?" goto :Error
if "%1" == "-?" goto :Error
if "%1" == "help" goto :Error
if "%1" == "-help" goto :Error
if "%1" == "/help" goto :Error
$$IF(MULTIPLE_LANGS)
if "%1" == "MAC" goto :Error
if "%1" == "" goto :Error
$$ENDIF //MULTIPLE_LANGS

$$ENDIF //MULTIPLE_LANGS||TARGET_MAC
$$IF(HM_NOTE)

REM -- PLEASE NOTE: OEM VS. ANSI CHARACTER SET DIFFERENCES
REM -- Many of the file names below look wierd in most editors because they need to be 
REM -- in the OEM character set, not the ANSI character set, in order to make batch  
REM -- files work right. The output and editor windows work with the ANSI character set.  
REM -- Where names are seen only in the output window, they have been left in the 
REM -- ANSI character set.

$$ENDIF	//HM_NOTE
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by $$ROOT$$.HPJ. >"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Prompts (IDP_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Resources (IDR_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Dialogs (IDD_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
echo. >>"hlp\$$HM_FILE_OEM$$.hm"
echo // Frame Controls (IDW_*) >>"hlp\$$HM_FILE_OEM$$.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$$HM_FILE_OEM$$.hm"
REM -- Make help for Project $$ROOT$$

$$IF(TARGET_INTEL || TARGET_MIPS || TARGET_ALPHA)
$$IF(TARGET_MAC)

if "%$$HLPARG_MAC$$" == "MAC" goto Mac

:Intel
if not "%$$HLPARG_MAC$$" == "" goto :Error
if not "%$$HLPARG_MACPATH$$" == "" goto :Error
$$ENDIF //TARGET_MAC

echo Building Win32 Help files
$$IF(MULTIPLE_LANGS)
start /wait hcw /C /E /M "hlp\%1\$$root_oem$$.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\%1\$$root_oem$$.hlp" goto :Error
if not exist "hlp\%1\$$root_oem$$.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\%1\$$root_oem$$.hlp" Debug
if exist Debug\nul copy "hlp\%1\$$root_oem$$.cnt" Debug
if exist Release\nul copy "hlp\%1\$$root_oem$$.hlp" Release
if exist Release\nul copy "hlp\%1\$$root_oem$$.cnt" Release
$$ELSE //!MULTIPLE_LANGS
start /wait hcw /C /E /M "hlp\$$root_oem$$.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\$$root_oem$$.hlp" goto :Error
if not exist "hlp\$$root_oem$$.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\$$root_oem$$.hlp" Debug
if exist Debug\nul copy "hlp\$$root_oem$$.cnt" Debug
if exist Release\nul copy "hlp\$$root_oem$$.hlp" Release
if exist Release\nul copy "hlp\$$root_oem$$.cnt" Release
$$ENDIF //MULTIPLE_LANGS
$$IF(TARGET_MAC)
goto :done
$$ELSE //!TARGET_MAC
echo.
$$ENDIF //TARGET_MAC
$$ENDIF //INTEL/MIPS/ALPHA
$$IF(TARGET_MAC)

$$IF(TARGET_INTEL || TARGET_MIPS || TARGET_ALPHA)
:Mac
$$ENDIF //INTEL,MIPS,ALPHA
echo Building Macintosh Help files
$$IF(MULTIPLE_LANGS)
call hc35 "hlp\%1\$$mac_hpj$$.hpj"
$$ELSE //!MULTIPLE_LANGS
cd hlp
call hc35 "$$mac_hpj$$.hpj"
cd ..
$$ENDIF //MULTIPLE_LANGS

if %$$HLPARG_MACPATH$$x == x goto :done
echo Copying to remote machine
mfile copy -c MSH2 -t HELP "hlp\$$mac_hpj$$.hlp" %$$HLPARG_MACPATH$$
$$ENDIF //TARGET_MAC
goto :done

$$// Depending on Mac-targeting and multiple-languages, makehelp takes different args
$$IF(MULTIPLE_LANGS)
$$IF(TARGET_MAC)
$$// Both Mac-targeting & multiple languages
:Error
echo Usage MAKEHELP LanguageAbbreviation [MAC [macintosh-path]]
echo       Where macintosh-path is of the form:
echo       ":<MacintoshName>:...:<MacintoshHelpFile>"
echo       And LanguageAbbreviation is one of $$LANG_LIST_SUFFIXES$$
$$ELSE //!TARGET_MAC
$$// Multiple languages, NO Mac targeting
:Error
echo Usage MAKEHELP LanguageAbbreviation
echo       Where LanguageAbbreviation is one of $$LANG_LIST_SUFFIXES$$
$$ENDIF //TARGET_MAC
$$ELSE //!MULTIPLE_LANGS
:Error
$$IF(TARGET_MAC)
$$// Mac targeting, and NO multiple languages
echo Usage MAKEHELP [MAC [macintosh-path]]
echo       Where macintosh-path is of the form:
echo       ":<MacintoshName>:...:<MacintoshHelpFile>"
$$ELSE	//!TARGET_MAC
echo hlp\$$root$$.hpj(1) : error: Problem encountered creating help file
$$ENDIF //TARGET_MAC
$$ENDIF //MULTIPLE_LANGS

:done
echo.
