# Microsoft Developer Studio Project File - Name="ComboTree" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ComboTree - Win32 DebugUnicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComboTree.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComboTree.mak" CFG="ComboTree - Win32 DebugUnicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComboTree - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ComboTree - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ComboTree - Win32 DebugUnicode" (based on "Win32 (x86) Application")
!MESSAGE "ComboTree - Win32 ReleaseUnicode" (based on "Win32 (x86) Application")
!MESSAGE "ComboTree - Win32 ReleaseShared" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComboTree - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"ComboTree.exe"

!ELSEIF  "$(CFG)" == "ComboTree - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"ComboTree.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ComboTree - Win32 DebugUnicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ComboTree___Win32_DebugUnicode"
# PROP BASE Intermediate_Dir "ComboTree___Win32_DebugUnicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUnicode"
# PROP Intermediate_Dir "DebugUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"ComboTree.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ComboTree - Win32 ReleaseUnicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ComboTree___Win32_ReleaseUnicode"
# PROP BASE Intermediate_Dir "ComboTree___Win32_ReleaseUnicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUnicode"
# PROP Intermediate_Dir "ReleaseUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"ComboTree.exe"

!ELSEIF  "$(CFG)" == "ComboTree - Win32 ReleaseShared"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ComboTree___Win32_ReleaseShared"
# PROP BASE Intermediate_Dir "ComboTree___Win32_ReleaseShared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseShared"
# PROP Intermediate_Dir "ReleaseShared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"ComboTree.exe"

!ENDIF 

# Begin Target

# Name "ComboTree - Win32 Release"
# Name "ComboTree - Win32 Debug"
# Name "ComboTree - Win32 DebugUnicode"
# Name "ComboTree - Win32 ReleaseUnicode"
# Name "ComboTree - Win32 ReleaseShared"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ComboOXTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboTree.rc
# End Source File
# Begin Source File

SOURCE=.\ComboTreeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXComboPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShellFolderTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShellNamespaceNavigator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeCal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ComboOXTree.h
# End Source File
# Begin Source File

SOURCE=.\ComboTree.h
# End Source File
# Begin Source File

SOURCE=.\ComboTreeDlg.h
# End Source File
# Begin Source File

SOURCE=.\FolderTree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXComboPickerCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXShellFolderTree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXShellNamespaceNavigator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeCal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ComboTree.ico
# End Source File
# Begin Source File

SOURCE=.\res\ComboTree.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ComboTree.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
