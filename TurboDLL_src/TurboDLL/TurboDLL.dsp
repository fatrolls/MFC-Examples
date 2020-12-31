# Microsoft Developer Studio Project File - Name="TurboDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TurboDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TurboDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TurboDLL.mak" CFG="TurboDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TurboDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TurboDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TurboDLL - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\release"
# PROP Intermediate_Dir "..\temp\TurboDLL\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\bin\release/TurboDLL.dll"

!ELSEIF  "$(CFG)" == "TurboDLL - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\debug"
# PROP Intermediate_Dir "..\temp\TurboDLL\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\TurboDLLD.def" /out:"..\bin\debug/TurboDLLD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "TurboDLL - Win32 Release"
# Name "TurboDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TLCDragWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLCDropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLHDragWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TLHDropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListColumnInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListComboCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListDC.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListStaticCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeListTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TurboDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\TurboDLL.def

!IF  "$(CFG)" == "TurboDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "TurboDLL - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TurboDLL.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TLCDragWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLCDropWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLHDragWnd.h
# End Source File
# Begin Source File

SOURCE=.\TLHDropWnd.h
# End Source File
# Begin Source File

SOURCE=.\TreeListColumnInfo.h
# End Source File
# Begin Source File

SOURCE=.\TreeListComboCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListDC.h
# End Source File
# Begin Source File

SOURCE=.\TreeListEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListItem.h
# End Source File
# Begin Source File

SOURCE=.\TreeListResource.h
# End Source File
# Begin Source File

SOURCE=.\TreeListStaticCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TreeListTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TurboDLL.h
# End Source File
# Begin Source File

SOURCE=.\xTurboDLL.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bm_bkgnd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_bkgnd2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_checkbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_head.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_sort.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_def_tree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bm_lockbox.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur_button.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_checkbox.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_cross.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_drop.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_horz.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_lockbox.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_size.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_split.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_stop.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur_vert.cur
# End Source File
# Begin Source File

SOURCE=.\res\TurboDLL.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
