# Microsoft Developer Studio Project File - Name="SkinCtrlTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SkinCtrlTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SkinCtrlTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkinCtrlTest.mak" CFG="SkinCtrlTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkinCtrlTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SkinCtrlTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/SkinCtrlTest", HEBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkinCtrlTest - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NO_SKIN_INI" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SkinCtrlTest - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NO_SKIN_INI" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SkinCtrlTest - Win32 Release"
# Name "SkinCtrlTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Shared\delayredraw.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\EnBitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\HookMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\RoundCorner.cpp
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinBase.cpp
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrlMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrls.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinCtrlTest.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinCtrlTest.rc
# End Source File
# Begin Source File

SOURCE=.\SkinCtrlTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinGlobals.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Shared\Subclass.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\WinClasses.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Shared\delayredraw.h
# End Source File
# Begin Source File

SOURCE=..\Shared\EnBitmap.h
# End Source File
# Begin Source File

SOURCE=..\Shared\HookMgr.h
# End Source File
# Begin Source File

SOURCE=.\PropPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\Shared\RoundCorner.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinBase.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrl.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrlMgr.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinCtrls.h
# End Source File
# Begin Source File

SOURCE=.\SkinCtrlTest.h
# End Source File
# Begin Source File

SOURCE=.\SkinCtrlTestDlg.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinGlobals.h
# End Source File
# Begin Source File

SOURCE=..\SkinWindows\SkinGlobalsData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Shared\Subclass.h
# End Source File
# Begin Source File

SOURCE=..\Shared\SysColors.h
# End Source File
# Begin Source File

SOURCE=..\Shared\wclassdefines.h
# End Source File
# Begin Source File

SOURCE=..\Shared\WinClasses.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_cold_clipleft.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_cold_clipright.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_cold_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_cold_mid.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_cold_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_dis_clipleft.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_dis_clipright.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_dis_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_dis_mid.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_dis_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_hot_clipleft.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_hot_clipright.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_hot_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_hot_mid.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\btn_hot_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\scroll_cold.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\scroll_dis.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\scroll_hot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SkinCtrlTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\SkinCtrlTest.rc2
# End Source File
# Begin Source File

SOURCE=.\RES\spin_cold_down.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_cold_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_cold_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_cold_up.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_dis_down.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_dis_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_dis_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_dis_up.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_hot_down.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_hot_left.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_hot_right.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\spin_hot_up.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
