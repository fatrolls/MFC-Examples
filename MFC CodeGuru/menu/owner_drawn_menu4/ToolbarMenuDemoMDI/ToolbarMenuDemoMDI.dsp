# Microsoft Developer Studio Project File - Name="ToolbarMenuDemoMDI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ToolbarMenuDemoMDI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ToolbarMenuDemoMDI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ToolbarMenuDemoMDI.mak"\
 CFG="ToolbarMenuDemoMDI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ToolbarMenuDemoMDI - Win32 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "ToolbarMenuDemoMDI - Win32 Debug" (based on\
 "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ToolbarMenuDemoMDI - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ToolbarMenuDemoMDI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ToolbarMenuDemoMDI - Win32 Release"
# Name "ToolbarMenuDemoMDI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuSpawn.cpp
# End Source File
# Begin Source File

SOURCE=.\SpawnFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SpawnMDIChildWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SpawnMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDI.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDI.rc

!IF  "$(CFG)" == "ToolbarMenuDemoMDI - Win32 Release"

!ELSEIF  "$(CFG)" == "ToolbarMenuDemoMDI - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDIDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDIView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuSpawn.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SpawnFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\SpawnMDIChildWnd.h
# End Source File
# Begin Source File

SOURCE=.\SpawnMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDI.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDIDoc.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarMenuDemoMDIView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\angel1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\angel2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dolphin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dolphin2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menuchk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sysbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolbarMenuDemoMDI.ico
# End Source File
# Begin Source File

SOURCE=.\res\ToolbarMenuDemoMDI.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ToolbarMenuDemoMDIDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ToolbarMenuDemoMDI : {1F5C7247-9DBB-11D1-8BAD-0000B43382FE}
# 	2:17:CLASS: CMenuSpawn:CMenuSpawn
# 	2:11:MenuSpawn.h:MenuSpawn.h
# 	2:13:MenuSpawn.cpp:MenuSpawn.cpp
# 	2:19:Application Include:ToolbarMenuDemoMDI.h
# End Section
