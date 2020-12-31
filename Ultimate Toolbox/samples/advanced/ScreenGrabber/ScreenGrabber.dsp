# Microsoft Developer Studio Project File - Name="ScreenGrabber" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ScreenGrabber - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScreenGrabber.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScreenGrabber.mak" CFG="ScreenGrabber - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScreenGrabber - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ScreenGrabber - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ScreenGrabber - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScreenGrabber - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ScreenGrabber.exe" /libpath:"..\..\..\Lib\libs"

!ELSEIF  "$(CFG)" == "ScreenGrabber - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jpgd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"ScreenGrabber.exe" /pdbtype:sept /libpath:"..\..\..\Lib\libs"

!ELSEIF  "$(CFG)" == "ScreenGrabber - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ScreenGr"
# PROP BASE Intermediate_Dir "ScreenGr"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ScreenGrabber.exe"
# ADD LINK32 jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ScreenGrabber.exe" /libpath:"..\..\..\Lib\libs"

!ENDIF 

# Begin Target

# Name "ScreenGrabber - Win32 Release"
# Name "ScreenGrabber - Win32 Debug"
# Name "ScreenGrabber - Win32 Release_Shared"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\Source\Copytree.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Dir.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Dstrlist.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\File.cpp"
# End Source File
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

SOURCE=..\..\..\source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXBMPFle.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXContextHelpPropertyPage.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXContextHelpPropertySheet.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Oxdib.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDirDlg.cpp"
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

SOURCE="..\..\..\Source\OXGphFle.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXHistoryCombo.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXJPGCod.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXJPGCom.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXJPGDom.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXJPGExp.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXJPGFle.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXLayoutManager.cpp"
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

SOURCE="..\..\..\Source\OXScreenGrab.cpp"
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

SOURCE="..\..\..\Source\OXSpinCtrl.cpp"
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

SOURCE="..\..\..\Source\OXTaskbarIcon.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXToolTipCtrl.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Path.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Xstatus4.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Xstring.cpp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\CaptureTaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageActivation.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDestination.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageImage.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPagePreferences.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageSource.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertySheetCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenGrabber.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenGrabber.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WndTrackingHelper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CaptureTaskbarIcon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXContextHelpPropertyPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXContextHelpPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageActivation.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDestination.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageFile.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageImage.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPagePreferences.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageSource.h
# End Source File
# Begin Source File

SOURCE=.\PropertySheetCapture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenGrabber.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WndTrackingHelper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ScreenGrabber.ico
# End Source File
# Begin Source File

SOURCE=.\res\ScreenGrabber.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
