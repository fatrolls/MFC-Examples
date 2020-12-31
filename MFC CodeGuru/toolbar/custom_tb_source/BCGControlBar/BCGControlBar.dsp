# Microsoft Developer Studio Project File - Name="BCGControlBar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BCGControlBar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGControlBar.mak" CFG="BCGControlBar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGControlBar - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BCGControlBar - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/BCG/BCGControlBar", TWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGControlBar - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\output\Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "BCGControlBar - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\output\debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BCGControlBar - Win32 Release"
# Name "BCGControlBar - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGControlBar.def
# End Source File
# Begin Source File

SOURCE=.\BCGControlBar.rc
# End Source File
# Begin Source File

SOURCE=.\BCGToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarComboBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropSource.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolBarImages.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonsList.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonsTextList.cpp
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomize.cpp
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomizePages.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.CPP
# End Source File
# Begin Source File

SOURCE=.\ImageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImagePaintArea.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarComboBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropSource.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolBarImages.h
# End Source File
# Begin Source File

SOURCE=.\BCGToolbarMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\ButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\ButtonsList.h
# End Source File
# Begin Source File

SOURCE=.\ButtonsTextList.h
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomize.h
# End Source File
# Begin Source File

SOURCE=.\CBCGToolbarCustomizePages.h
# End Source File
# Begin Source File

SOURCE=.\ColorSelector.h
# End Source File
# Begin Source File

SOURCE=.\GLOBALS.H
# End Source File
# Begin Source File

SOURCE=.\ImageEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImagePaintArea.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arrows.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BCGControlBar.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
