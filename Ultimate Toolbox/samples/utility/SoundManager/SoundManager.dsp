# Microsoft Developer Studio Project File - Name="SoundManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SoundManager - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SoundManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SoundManager.mak" CFG="SoundManager - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SoundManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SoundManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SoundManager - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "SoundManager - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "SoundManager - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoundManager - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"SoundManager.exe"

!ELSEIF  "$(CFG)" == "SoundManager - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"SoundManager.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "SoundManager - Win32 Release_Shared"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SoundMan"
# PROP BASE Intermediate_Dir "SoundMan"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"SoundManager.exe"

!ELSEIF  "$(CFG)" == "SoundManager - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SoundMa0"
# PROP BASE Intermediate_Dir "SoundMa0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"SoundManager.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"SoundManager.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "SoundManager - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SoundMa1"
# PROP BASE Intermediate_Dir "SoundMa1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "NDEBUG"
# ADD RSC /l 0x1009 /i "..\..\..\include" /i "..\..\..\source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"SoundManager.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"SoundManager.exe"

!ENDIF 

# Begin Target

# Name "SoundManager - Win32 Release"
# Name "SoundManager - Win32 Debug"
# Name "SoundManager - Win32 Release_Shared"
# Name "SoundManager - Win32 Unicode_Debug"
# Name "SoundManager - Win32 Unicode_Release"
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

SOURCE=..\..\..\source\OXAdvancedAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXAdvancedAssertMail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCaptionPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHistoryCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHyperLinkAction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXItemTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMultiComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRegistryValFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSoundCustomizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSoundEffectManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSoundWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXStaticHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXStaticText.cpp
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

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# End Group
# Begin Group "Skins Framework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\OX3DTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenuOrganizer.cpp
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

SOURCE=..\..\..\source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShortcutBar.cpp
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

SOURCE=..\..\..\source\OXSkinnedComboBox.cpp
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

SOURCE=..\..\..\source\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Xstatus4.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MyAnimateCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MyStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundManager.rc
# End Source File
# Begin Source File

SOURCE=.\SoundManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MyAnimateCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MyStatic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCaptionPainter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHistoryCombo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHookWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\oxmulticombobox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXMultiComboBox.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSoundCustomizeDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSoundEffectManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSoundWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXStaticText.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXStaticText.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SoundManager.h
# End Source File
# Begin Source File

SOURCE=.\SoundManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\sndplay.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sndstop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SoundManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\SoundManager.rc2
# End Source File
# Begin Source File

SOURCE=.\res\treelist.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\avi_test.avi
# End Source File
# Begin Source File

SOURCE=.\res\Drumroll.wav
# End Source File
# Begin Source File

SOURCE=.\Sound\Drumroll.wav
# End Source File
# Begin Source File

SOURCE=.\res\Mfc2.avi
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
