# Microsoft Developer Studio Project File - Name="PukamSoft" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PukamSoft - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PukamSoft.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PukamSoft.mak" CFG="PukamSoft - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PukamSoft - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PukamSoft - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Vishal/Lathi Storage Services/PukamSoft", GQGAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PukamSoft - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../common/cimage/lib/imagelib.lib ../common/cimage/lib/zlib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PukamSoft - Win32 Debug"

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
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../common/cimage/lib/imagelib_d.lib ../common/cimage/lib/zlib_d.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PukamSoft - Win32 Release"
# Name "PukamSoft - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Common SRC"

# PROP Default_Filter ""
# Begin Group "UIClasses SRC"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\Common\UIClasses\SkinControl.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedStatic.cpp
# End Source File
# End Group
# Begin Group "Tools SRC"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\Common\Tools\cell.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\CustomDB.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\editdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\FinancialCalc.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\GlobalFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\helpers.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\imgobj.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\row.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\StringEx.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tablecontainer.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tabledata.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tablepage.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\trans.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\BillingInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomerInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InwardTransactionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftNavDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainMenuDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OutwardTransactionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PukamSoft.cpp
# End Source File
# Begin Source File

SOURCE=.\PukamSoft.rc
# End Source File
# Begin Source File

SOURCE=.\PukamSoftDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TopBandDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Common H"

# PROP Default_Filter ""
# Begin Group "UIClasses H"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\Common\UIClasses\SkinControl.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedButton.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedComboBox.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedEdit.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedListBox.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedScrollBar.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Common\UIClasses\SkinnedStatic.h
# End Source File
# End Group
# Begin Group "Tools H"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\Common\Tools\cell.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\CustomDB.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\editdlg.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\FinancialCalc.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\GlobalFunctions.h
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\helpers.h
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\imgobj.h
# End Source File
# Begin Source File

SOURCE=..\Common\CIMAGE\SRC\imgobj.inl
# End Source File
# Begin Source File

SOURCE=.\MessageBoxDlg.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\row.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\StringEx.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tablecontainer.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tabledata.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tools\tablepage.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Common\GlobalConstants.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BillingInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\BitmapIDs.h
# End Source File
# Begin Source File

SOURCE=.\CustomerInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageIDs.h
# End Source File
# Begin Source File

SOURCE=.\InwardTransactionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\LeftNavDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainMenuDlg.h
# End Source File
# Begin Source File

SOURCE=.\OutwardTransactionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PukamSoft.h
# End Source File
# Begin Source File

SOURCE=.\PukamSoftDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReportsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TopBandDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PukamSoft.ico
# End Source File
# Begin Source File

SOURCE=.\res\PukamSoft.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
