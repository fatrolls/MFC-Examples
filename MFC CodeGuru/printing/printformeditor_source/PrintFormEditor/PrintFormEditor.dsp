# Microsoft Developer Studio Project File - Name="PrintFormEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PrintFormEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PrintFormEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PrintFormEditor.mak" CFG="PrintFormEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PrintFormEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PrintFormEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PrintFormEditor - Win32 Release"

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
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Desc=backuping
PreLink_Cmds=xcopy .\res\*.* e:\bck\PrintFormEditor\Res /D /C >NIL	xcopy *.*\
        e:\bck\PrintFormEditor /D /C >NIL
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PrintFormEditor - Win32 Debug"

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
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Desc=backuping
PreLink_Cmds=xcopy .\res\*.* e:\bck\PrintFormEditor\Res /D /C >NIL	xcopy *.*\
        e:\bck\PrintFormEditor /D /C >NIL
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PrintFormEditor - Win32 Release"
# Name "PrintFormEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\gfx.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\HorizRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\infodlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PagePage1.cpp
# End Source File
# Begin Source File

SOURCE=.\PagerSizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PapersBar.cpp
# End Source File
# Begin Source File

SOURCE=.\PinButton.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintFormEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintFormEditor.rc

!IF  "$(CFG)" == "PrintFormEditor - Win32 Release"

!ELSEIF  "$(CFG)" == "PrintFormEditor - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VertRuler.cpp
# End Source File
# Begin Source File

SOURCE=.\View.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ColourPicker.h
# End Source File
# Begin Source File

SOURCE=.\ColourPopup.h
# End Source File
# Begin Source File

SOURCE=.\Doc.h
# End Source File
# Begin Source File

SOURCE=.\gfx.h
# End Source File
# Begin Source File

SOURCE=.\GfxProperty.h
# End Source File
# Begin Source File

SOURCE=.\HorizRuler.h
# End Source File
# Begin Source File

SOURCE=.\infodlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PagePage1.h
# End Source File
# Begin Source File

SOURCE=.\PagerSizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PapersBar.h
# End Source File
# Begin Source File

SOURCE=.\PinButton.h
# End Source File
# Begin Source File

SOURCE=.\PrintFormEditor.h
# End Source File
# Begin Source File

SOURCE=.\PropDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropPage1.h
# End Source File
# Begin Source File

SOURCE=.\PropPage2.h
# End Source File
# Begin Source File

SOURCE=.\PropPage3.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VertRuler.h
# End Source File
# Begin Source File

SOURCE=.\View.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\applogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\PrintFormEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\PrintFormEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\prophelp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\proppin1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\proppin3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\PrintFormEditor.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section PrintFormEditor : {9EC0CDB1-0B77-11D2-8414-0000B43382FE}
# 	2:19:CLASS: CColourPopup:CColourPopup
# 	2:13:ColourPopup.h:ColourPopup.h
# 	2:15:ColourPopup.cpp:ColourPopup.cpp
# 	2:19:Application Include:printformeditor.h
# End Section
# Section PrintFormEditor : {163B49D2-0F42-11D2-842B-0000B43382FE}
# 	2:11:PinButton.h:PinButton.h
# 	2:17:CLASS: CPinButton:CPinButton
# 	2:13:PinButton.cpp:PinButton.cpp
# 	2:19:Application Include:printformeditor.h
# End Section
# Section PrintFormEditor : {9EC0CDB0-0B77-11D2-8414-0000B43382FE}
# 	2:16:ColourPicker.cpp:ColourPicker.cpp
# 	2:14:ColourPicker.h:ColourPicker.h
# 	2:20:CLASS: CColourPicker:CColourPicker
# 	2:19:Application Include:printformeditor.h
# End Section
