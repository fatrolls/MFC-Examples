# Microsoft Developer Studio Project File - Name="hideprocess" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=hideprocess - Win32 Checked
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "hideprocess.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "hideprocess.mak" CFG="hideprocess - Win32 Checked"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "hideprocess - Win32 Checked" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "hideprocess - Win32 Free" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "hideprocess - Win32 Checked"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\objchk\i386"
# PROP Intermediate_Dir ".\objchk\i386"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP
# ADD CPP /nologo /ML /Zel -cbstring /Gy /GF /c /FI"warning.h" /Zi /Oi /Gz
# ADD CPP /W3
# ADD CPP /D _X86_=1 /D i386=1 /D STD_CALL /D CONDITION_HANDLING=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D FPO=0 /D NDEBUG /D _DLL=1 /D DBG=1 /D DEPRECATE_DDK_FUNCTIONS /D _WIN32_WINNT=$(_WIN32_WINNT) /D WINVER=$(WINVER) /D _WIN32_IE=$(_WIN32_IE) /D NTDDI_VERSION=$(NTDDI_VERSION)
# ADD CPP /I "." /I "$(TARGET_INC_PATH)" /I "$(CRT_INC_PATH)" /I "$(DDK_INC_PATH)" /I "$(WDM_INC_PATH)"
# ADD CPP /Fd".\objchk\i386\hideprocess.pdb"
# ADD BASE MTL /nologo /mktyplib203 /o NUL /win32 /d "_DEBUG"
# ADD MTL /nologo /mktyplib203 /o NUL /win32 /d "_DEBUG"
# ADD BASE RSC /l 0x409 /I "$(CRT_INC_PATH)" /d "_DEBUG"
# ADD RSC /l 0x409 /I "$(CRT_INC_PATH)" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo /o".\objchk\i386/hideprocess.bsc"
LINK32=link.exe
# ADD BASE LINK32
# ADD LINK32 /nologo /base:"0x10000" /version:5.0 /stack:0x40000,0x1000 /entry:"DriverEntry" /machine:IX86 /nodefaultlib /INCREMENTAL:NO
# ADD LINK32 /libpath:"$(TARGET_LIB_PATH)" /driver /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text
# ADD LINK32 /FULLBUILD /RELEASE /OPT:REF /OPT:ICF /align:0x80 /osversion:5.00 /subsystem:native,1.10
# ADD LINK32 /debug:FULL /debugtype:cv /out:".\objchk\i386\hideprocess.sys"
# ADD LINK32 /ignore:4010,4037,4039,4065,4070,4078,4087,4089,4221,4210
# ADD LINK32 ntoskrnl.lib hal.lib wmilib.lib

# Begin Special Build Tool
PostBuild_Cmds=$(DRIVERWORKS)\bin\nmsym /trans:source,package,always .\objchk\i386\hideprocess.sys
# End Special Build Tool

!ELSEIF  "$(CFG)" == "hideprocess - Win32 Free"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\objfre\i386"
# PROP Intermediate_Dir ".\objfre\i386"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP
# ADD CPP /nologo /ML /Zel -cbstring /Gy /GF /c /FI"warning.h" /Oxs /Oy /Gz
# ADD CPP /W3
# ADD CPP /D _X86_=1 /D i386=1 /D STD_CALL /D CONDITION_HANDLING=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D FPO=0 /D NDEBUG /D _DLL=1 /D _WIN32_WINNT=$(_WIN32_WINNT) /D WINVER=$(WINVER) /D _WIN32_IE=$(_WIN32_IE) /D NTDDI_VERSION=$(NTDDI_VERSION)
# ADD CPP /I "." /I "$(TARGET_INC_PATH)" /I "$(CRT_INC_PATH)" /I "$(DDK_INC_PATH)" /I "$(WDM_INC_PATH)"
# ADD BASE MTL /nologo /mktyplib203 /o NUL /win32 /d "NDEBUG"
# ADD MTL /nologo /mktyplib203 /o NUL /win32 /d "NDEBUG"
# ADD BASE RSC /l 0x409 /I "$(CRT_INC_PATH)" /d "NDEBUG"
# ADD RSC /l 0x409 /I "$(CRT_INC_PATH)" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo /o".\objfre\i386/hideprocess.bsc"
LINK32=link.exe
# ADD BASE LINK32
# ADD LINK32 /nologo /base:"0x10000" /version:5.0 /stack:0x40000,0x1000 /entry:"DriverEntry" /machine:IX86 /nodefaultlib /INCREMENTAL:NO
# ADD LINK32 /libpath:"$(TARGET_LIB_PATH)" /driver /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text
# ADD LINK32 /FULLBUILD /RELEASE /OPT:REF /OPT:ICF /align:0x80 /osversion:5.00 /subsystem:native,1.10
# ADD LINK32 /debug:MINIMAL /out:"objfre\i386\hideprocess.sys"
# ADD LINK32 /ignore:4010,4037,4039,4065,4070,4078,4087,4089,4221,4210
# ADD LINK32 ntoskrnl.lib hal.lib wmilib.lib



!ENDIF

# Begin Target

# Name "hideprocess - Win32 Checked"
# Name "hideprocess - Win32 Free"

# Begin Group "Source Files"

# PROP Default_Filter ".c;.cpp"

# Begin Source File

SOURCE=.\HideProcess.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ".h"

# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ".rc;.mc;.mof"



# End Group
# Begin Source File

SOURCE=.\sources
# End Source File
# End Target
# End Project
