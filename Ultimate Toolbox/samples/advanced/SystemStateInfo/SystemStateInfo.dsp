# Microsoft Developer Studio Project File - Name="SystemStateInfo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SystemStateInfo - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SystemStateInfo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SystemStateInfo.mak" CFG="SystemStateInfo - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SystemStateInfo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SystemStateInfo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SystemStateInfo - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "SystemStateInfo - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "SystemStateInfo - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SystemStateInfo - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Processor\Intel\Cpuinf32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\Cpuinfr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"SystemStateInfo.exe"

!ELSEIF  "$(CFG)" == "SystemStateInfo - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Processor\Intel\Cpuinf32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\Lib\libs\Cpuinfr.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBC" /out:"SystemStateInfo.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "SystemStateInfo - Win32 Release_Shared"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Shared"
# PROP BASE Intermediate_Dir "Release_Shared"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Processor\Intel\Cpuinf32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\Cpuinfr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"SystemStateInfo.exe"

!ELSEIF  "$(CFG)" == "SystemStateInfo - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode_Debug"
# PROP BASE Intermediate_Dir "Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Processor\Intel\Cpuinf32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\Lib\libs\Cpuinfr.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"SystemStateInfo.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "SystemStateInfo - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode_Release"
# PROP BASE Intermediate_Dir "Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Processor\Intel\Cpuinf32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\Cpuinfr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"SystemStateInfo.exe"

!ENDIF 

# Begin Target

# Name "SystemStateInfo - Win32 Release"
# Name "SystemStateInfo - Win32 Debug"
# Name "SystemStateInfo - Win32 Release_Shared"
# Name "SystemStateInfo - Win32 Unicode_Debug"
# Name "SystemStateInfo - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\MFCToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OX3DTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXAdvancedAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXAdvancedAssertMail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\oxdocktabctrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDragDockContext.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXFrameWndDock.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXInstanceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXInteger.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXIteratorService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXNetBrowseTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXService.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSizeCtrlBar.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSizeDockBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSizeToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSkinnedSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSkinnedTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSkins.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSplashWndDIB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSysInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXToolTipCtrl.cpp
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

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Xstatus4.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ApplicationsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkResourcesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PageDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ServicesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SSIDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SSITaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysInfoDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemStateInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemStateInfo.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "UTHeader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCalendar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCalendarPopup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDllExt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHookWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXInstanceManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXInteger.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXInteger.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXItemTip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXItemTipWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXIteratorService.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXLayoutManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXLayoutManager.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXNetBrowseTree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSeparator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXService.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXShortcutBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSysInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTaskbarIcon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTaskbarIcon.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeCal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeCombo.h
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
# End Group
# Begin Source File

SOURCE=.\ApplicationsDialog.h
# End Source File
# Begin Source File

SOURCE=.\NetworkResourcesDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSplashWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSplashWnd.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSplashWndDIB.h
# End Source File
# Begin Source File

SOURCE=.\PageDialog.h
# End Source File
# Begin Source File

SOURCE=.\ProcessesDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServicesDialog.h
# End Source File
# Begin Source File

SOURCE=.\SSIDialog.h
# End Source File
# Begin Source File

SOURCE=.\SSITaskbarIcon.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysInfoDialog.h
# End Source File
# Begin Source File

SOURCE=.\SystemStateInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\processe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\services.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shb_larg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shb_smal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sysinfo_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SystemStateInfo.ico
# End Source File
# Begin Source File

SOURCE=.\res\SystemStateInfo.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
