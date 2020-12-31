# Microsoft Developer Studio Project File - Name="CPPTooltip_demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CPPTooltip_demo - Win32 DebugUnicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CPPTooltip_demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CPPTooltip_demo.mak" CFG="CPPTooltip_demo - Win32 DebugUnicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CPPTooltip_demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CPPTooltip_demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CPPTooltip_demo - Win32 DebugUnicode" (based on "Win32 (x86) Application")
!MESSAGE "CPPTooltip_demo - Win32 ReleaseUnicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CPPTooltip_demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CPPTooltip_demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile /pdb:none

!ELSEIF  "$(CFG)" == "CPPTooltip_demo - Win32 DebugUnicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CPPTooltip_demo___Win32_DebugUnicode"
# PROP BASE Intermediate_Dir "CPPTooltip_demo___Win32_DebugUnicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUnicode"
# PROP Intermediate_Dir "DebugUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /profile /pdb:none
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /profile /pdb:none

!ELSEIF  "$(CFG)" == "CPPTooltip_demo - Win32 ReleaseUnicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CPPTooltip_demo___Win32_ReleaseUnicode"
# PROP BASE Intermediate_Dir "CPPTooltip_demo___Win32_ReleaseUnicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUnicode"
# PROP Intermediate_Dir "ReleaseUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "CPPTooltip_demo - Win32 Release"
# Name "CPPTooltip_demo - Win32 Debug"
# Name "CPPTooltip_demo - Win32 DebugUnicode"
# Name "CPPTooltip_demo - Win32 ReleaseUnicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demo.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demo.rc
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demoView.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PageBehaviours.cpp
# End Source File
# Begin Source File

SOURCE=.\PageColors.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCssStyles.cpp
# End Source File
# Begin Source File

SOURCE=.\PageShadow.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSizes.cpp
# End Source File
# Begin Source File

SOURCE=.\PageStyles.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTestHyperlinks.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTestImages.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTestListTree.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTestMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTestTable.cpp
# End Source File
# Begin Source File

SOURCE=.\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestPageGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayIconPosition.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demo.h
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demoDoc.h
# End Source File
# Begin Source File

SOURCE=.\CPPTooltip_demoView.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeTooltip.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PageBehaviours.h
# End Source File
# Begin Source File

SOURCE=.\PageColors.h
# End Source File
# Begin Source File

SOURCE=.\PageCssStyles.h
# End Source File
# Begin Source File

SOURCE=.\PageShadow.h
# End Source File
# Begin Source File

SOURCE=.\PageSizes.h
# End Source File
# Begin Source File

SOURCE=.\PageStyles.h
# End Source File
# Begin Source File

SOURCE=.\PageTestHyperlinks.h
# End Source File
# Begin Source File

SOURCE=.\PageTestImages.h
# End Source File
# Begin Source File

SOURCE=.\PageTestListTree.h
# End Source File
# Begin Source File

SOURCE=.\PageTestMisc.h
# End Source File
# Begin Source File

SOURCE=.\PageTestTable.h
# End Source File
# Begin Source File

SOURCE=.\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=.\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StdString.h
# End Source File
# Begin Source File

SOURCE=.\TestPageGeneral.h
# End Source File
# Begin Source File

SOURCE=.\TrayIconPosition.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\0095 - Mail.ico"
# End Source File
# Begin Source File

SOURCE=.\res\1.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.ico
# End Source File
# Begin Source File

SOURCE=.\res\58.ico
# End Source File
# Begin Source File

SOURCE=.\res\59.ico
# End Source File
# Begin Source File

SOURCE=.\res\blank1.ico
# End Source File
# Begin Source File

SOURCE=.\res\close_app.ico
# End Source File
# Begin Source File

SOURCE=.\res\codeproject.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CPPTooltip_demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\CPPTooltip_demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CPPTooltip_demoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\globe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\map.BMP
# End Source File
# Begin Source File

SOURCE=.\res\smiles.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
