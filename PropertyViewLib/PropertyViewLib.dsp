# Microsoft Developer Studio Project File - Name="PropertyViewLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=PropertyViewLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PropertyViewLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PropertyViewLib.mak" CFG="PropertyViewLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PropertyViewLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PropertyViewLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/PropertyViewLib", HIUBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PropertyViewLib - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x406 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x406 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
OutDir=.\Release
SOURCE="$(InputPath)"
PostBuild_Desc=Copying files...
PostBuild_Cmds=if exist ..\lib copy $(OutDir)\*.lib ..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PropertyViewLib - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x406 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x406 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\PropertyViewLibD.lib"
# Begin Special Build Tool
OutDir=.\Debug
SOURCE="$(InputPath)"
PostBuild_Desc=Copying files...
PostBuild_Cmds=if exist ..\lib copy $(OutDir)\*.lib ..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PropertyViewLib - Win32 Release"
# Name "PropertyViewLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ECommentPane.cpp
# End Source File
# Begin Source File

SOURCE=.\EGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EGridView.cpp
# End Source File
# Begin Source File

SOURCE=.\EIconTextButtonProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\ENumericProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyColor.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyDir.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyDouble.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyFile.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyFont.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyInt.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertySeparator.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyString.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyTextblock.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropertyTextblockWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropList.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropView.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\EPropWndEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\EXMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\EXTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EXTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\EXWaitingTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\HoverButton.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRawPixels.cpp
# End Source File
# Begin Source File

SOURCE=.\SomeObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ST_SplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CheckOff.h
# End Source File
# Begin Source File

SOURCE=.\CheckOffDisabled.h
# End Source File
# Begin Source File

SOURCE=.\CheckOn.h
# End Source File
# Begin Source File

SOURCE=.\CheckOnDisabled.h
# End Source File
# Begin Source File

SOURCE=.\ECommentPane.h
# End Source File
# Begin Source File

SOURCE=.\EGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\EGridView.h
# End Source File
# Begin Source File

SOURCE=.\EIconTextButtonProperty.h
# End Source File
# Begin Source File

SOURCE=.\ENumericProperty.h
# End Source File
# Begin Source File

SOURCE=.\EPropCtrl.h
# End Source File
# Begin Source File

SOURCE=.\EProperty.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyCheck.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyColor.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyCombo.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyDir.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyDouble.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyFile.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyFloat.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyFont.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyInt.h
# End Source File
# Begin Source File

SOURCE=.\EPropertySeparator.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyString.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyTextblock.h
# End Source File
# Begin Source File

SOURCE=.\EPropertyTextblockWindow.h
# End Source File
# Begin Source File

SOURCE=.\EPropList.h
# End Source File
# Begin Source File

SOURCE=.\EPropListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\EPropView.h
# End Source File
# Begin Source File

SOURCE=.\EPropWnd.h
# End Source File
# Begin Source File

SOURCE=.\EPropWndEdit.h
# End Source File
# Begin Source File

SOURCE=.\EXMenu.h
# End Source File
# Begin Source File

SOURCE=.\EXTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\EXTreeView.h
# End Source File
# Begin Source File

SOURCE=.\EXWaitingTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HoverButton.h
# End Source File
# Begin Source File

SOURCE=.\IGridRow.h
# End Source File
# Begin Source File

SOURCE=.\IPropertyChangeListener.h
# End Source File
# Begin Source File

SOURCE=.\IPropertyHost.h
# End Source File
# Begin Source File

SOURCE=.\IRowList.h
# End Source File
# Begin Source File

SOURCE=.\IXTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\MinimizeBitmaps52x13.h
# End Source File
# Begin Source File

SOURCE=.\NodeClosed.h
# End Source File
# Begin Source File

SOURCE=.\NodeOpen.h
# End Source File
# Begin Source File

SOURCE=.\SetRawPixels.h
# End Source File
# Begin Source File

SOURCE=.\SomeObject.h
# End Source File
# Begin Source File

SOURCE=.\ST_SplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\History.txt
# End Source File
# Begin Source File

SOURCE=.\Usage.txt
# End Source File
# End Target
# End Project
