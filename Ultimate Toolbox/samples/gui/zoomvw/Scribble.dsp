# Microsoft Developer Studio Project File - Name="SCRIBBLE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SCRIBBLE - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Scribble.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scribble.mak" CFG="SCRIBBLE - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SCRIBBLE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SCRIBBLE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SCRIBBLE - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "SCRIBBLE - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "SCRIBBLE - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SCRIBBLE - Win32 Release"

# PROP BASE Use_MFC 1
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
# ADD BASE CPP /nologo /G3 /MT /W4 /GX /Og /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /G3 /MT /W4 /GX /Og /Ob1 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "GRAPHICS" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
# ADD LINK32 /nologo /stack:0x2800 /subsystem:windows /machine:IX86 /out:"Scribble.exe"

!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 Debug"

# PROP BASE Use_MFC 1
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
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86
# ADD LINK32 /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86 /out:"Scribble.exe"

!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 Release_Shared"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SCRIBBLE"
# PROP BASE Intermediate_Dir "SCRIBBLE"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G3 /MT /W4 /GX /Og /Ob1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "GRAPHICS" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G3 /MD /W4 /GX /Og /Ob1 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "GRAPHICS" /D "_MBCS" /D "_AFXDLL" /Yu"STDAFX.H" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /stack:0x2800 /subsystem:windows /machine:IX86 /out:"Scribble.exe"
# ADD LINK32 /nologo /stack:0x2800 /subsystem:windows /machine:IX86 /out:"Scribble.exe"

!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 Unicode_Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SCRIBBL0"
# PROP BASE Intermediate_Dir "SCRIBBL0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Yu"STDAFX.H" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /stack:0x2800 /subsystem:windows /debug /machine:IX86 /out:"Scribble.exe"
# ADD LINK32 /nologo /stack:0x2800 /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:IX86 /out:"Scribble.exe"

!ELSEIF  "$(CFG)" == "SCRIBBLE - Win32 Unicode_Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SCRIBBL1"
# PROP BASE Intermediate_Dir "SCRIBBL1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G3 /MT /W4 /GX /Og /Ob1 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "GRAPHICS" /D "_MBCS" /Yu"STDAFX.H" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G3 /MD /W4 /GX /Og /Ob1 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "GRAPHICS" /D "_MBCS" /D "_UNICODE" /D "_AFXDLL" /Yu"STDAFX.H" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /stack:0x2800 /subsystem:windows /machine:IX86 /out:"Scribble.exe"
# ADD LINK32 /nologo /stack:0x2800 /entry:"wWinMainCRTStartup" /subsystem:windows /machine:IX86 /out:"Scribble.exe"

!ENDIF 

# Begin Target

# Name "SCRIBBLE - Win32 Release"
# Name "SCRIBBLE - Win32 Debug"
# Name "SCRIBBLE - Win32 Release_Shared"
# Name "SCRIBBLE - Win32 Unicode_Debug"
# Name "SCRIBBLE - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Oxzoomvw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MAINFRM.CPP
# End Source File
# Begin Source File

SOURCE=.\PENDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\SCRIBBLE.CPP
# End Source File
# Begin Source File

SOURCE=.\SCRIBBLE.RC
# End Source File
# Begin Source File

SOURCE=.\SCRIBDOC.CPP
# End Source File
# Begin Source File

SOURCE=.\SCRIBVW.CPP
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\MAINFRM.H
# End Source File
# Begin Source File

SOURCE=.\PENDLG.H
# End Source File
# Begin Source File

SOURCE=.\SCRIBBLE.H
# End Source File
# Begin Source File

SOURCE=.\SCRIBDOC.H
# End Source File
# Begin Source File

SOURCE=.\SCRIBVW.H
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\SCRIBBLE.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\SCRIBBLE.RC2
# End Source File
# Begin Source File

SOURCE=.\RES\SCRIBDOC.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\TOOLBAR.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\Scribble.exe.manifest
# End Source File
# End Target
# End Project
