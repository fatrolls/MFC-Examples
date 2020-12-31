# Microsoft Developer Studio Project File - Name="UIlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UIlib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UIlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UIlib.mak" CFG="UIlib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UIlib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UIlib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UIlib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UILIB_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "D:\SDK\DirectX90\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UILIB_EXPORTS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x11000000" /dll /machine:I386 /out:"../bin/UIlib.dll" /implib:"../bin/UIlib.lib" /libpath:"D:\SDK\DirectX90\Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UIlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UILIB_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "D:\SDK\DirectX90\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UILIB_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x11000000" /dll /debug /machine:I386 /out:"../bin/UIlib.dll" /implib:"../bin/UIlib.lib" /pdbtype:sept /libpath:"D:\SDK\DirectX90\Lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "UIlib - Win32 Release"
# Name "UIlib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UIActiveX.cpp
# End Source File
# Begin Source File

SOURCE=.\UIAnim.cpp
# End Source File
# Begin Source File

SOURCE=.\UIBase.cpp
# End Source File
# Begin Source File

SOURCE=.\UIBlue.cpp
# End Source File
# Begin Source File

SOURCE=.\UIButton.cpp
# End Source File
# Begin Source File

SOURCE=.\UICombo.cpp
# End Source File
# Begin Source File

SOURCE=.\UIContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\UIDecoration.cpp
# End Source File
# Begin Source File

SOURCE=.\UIDlgBuilder.cpp
# End Source File
# Begin Source File

SOURCE=.\UIEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\UILabel.cpp
# End Source File
# Begin Source File

SOURCE=.\UIlib.cpp
# End Source File
# Begin Source File

SOURCE=.\UIList.cpp
# End Source File
# Begin Source File

SOURCE=.\UIManager.cpp
# End Source File
# Begin Source File

SOURCE=.\UIMarkup.cpp
# End Source File
# Begin Source File

SOURCE=.\UIPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\UITab.cpp
# End Source File
# Begin Source File

SOURCE=.\UITool.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Internal.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UIActiveX.h
# End Source File
# Begin Source File

SOURCE=.\UIAnim.h
# End Source File
# Begin Source File

SOURCE=.\UIBase.h
# End Source File
# Begin Source File

SOURCE=.\UIBlue.h
# End Source File
# Begin Source File

SOURCE=.\UIButton.h
# End Source File
# Begin Source File

SOURCE=.\UICombo.h
# End Source File
# Begin Source File

SOURCE=.\UIContainer.h
# End Source File
# Begin Source File

SOURCE=.\UIDecoration.h
# End Source File
# Begin Source File

SOURCE=.\UIDlgBuilder.h
# End Source File
# Begin Source File

SOURCE=.\UIEdit.h
# End Source File
# Begin Source File

SOURCE=.\UILabel.h
# End Source File
# Begin Source File

SOURCE=.\UIlib.h
# End Source File
# Begin Source File

SOURCE=.\UIList.h
# End Source File
# Begin Source File

SOURCE=.\UIManager.h
# End Source File
# Begin Source File

SOURCE=.\UIMarkup.h
# End Source File
# Begin Source File

SOURCE=.\UIPanel.h
# End Source File
# Begin Source File

SOURCE=.\UITab.h
# End Source File
# Begin Source File

SOURCE=.\UITool.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
