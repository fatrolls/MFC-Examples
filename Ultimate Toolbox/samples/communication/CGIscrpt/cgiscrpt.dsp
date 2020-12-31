# Microsoft Developer Studio Project File - Name="cgiscrpt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=cgiscrpt - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cgiscrpt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cgiscrpt.mak" CFG="cgiscrpt - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cgiscrpt - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "cgiscrpt - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "cgiscrpt - Win32 Release_Shared" (based on "Win32 (x86) Console Application")
!MESSAGE "cgiscrpt - Win32 Unicode_Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "cgiscrpt - Win32 Unicode_Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cgiscrpt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"cgiscrpt.exe"

!ELSEIF  "$(CFG)" == "cgiscrpt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /out:"cgiscrpt.exe"

!ELSEIF  "$(CFG)" == "cgiscrpt - Win32 Release_Shared"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "cgiscrpt"
# PROP BASE Intermediate_Dir "cgiscrpt"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:I386 /out:"cgiscrpt.exe"
# ADD LINK32 /nologo /subsystem:console /machine:I386 /out:"cgiscrpt.exe"

!ELSEIF  "$(CFG)" == "cgiscrpt - Win32 Unicode_Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cgiscrp0"
# PROP BASE Intermediate_Dir "cgiscrp0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /debug /machine:I386 /out:"cgiscrpt.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:console /debug /machine:I386 /out:"cgiscrpt.exe"

!ELSEIF  "$(CFG)" == "cgiscrpt - Win32 Unicode_Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "cgiscrp1"
# PROP BASE Intermediate_Dir "cgiscrp1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "NOAUTOLIB" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:console /machine:I386 /out:"cgiscrpt.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:console /machine:I386 /out:"cgiscrpt.exe"

!ENDIF 

# Begin Target

# Name "cgiscrpt - Win32 Release"
# Name "cgiscrpt - Win32 Debug"
# Name "cgiscrpt - Win32 Release_Shared"
# Name "cgiscrpt - Win32 Unicode_Debug"
# Name "cgiscrpt - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXScript.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\helloscp.CPP
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\helloscp.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\Include\OXScript.h
# End Source File
# End Group
# End Target
# End Project
