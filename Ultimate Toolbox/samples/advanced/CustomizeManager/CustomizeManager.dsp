# Microsoft Developer Studio Project File - Name="CustomizeManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CustomizeManager - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CustomizeManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CustomizeManager.mak" CFG="CustomizeManager - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CustomizeManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CustomizeManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "CustomizeManager - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "CustomizeManager - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CustomizeManager - Win32 Release"

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
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"CustomizeManager.exe"

!ELSEIF  "$(CFG)" == "CustomizeManager - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"CustomizeManager.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "CustomizeManager - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "CustomizeManager___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "CustomizeManager___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"CustomizeManager.exe"

!ELSEIF  "$(CFG)" == "CustomizeManager - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CustomizeManager___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "CustomizeManager___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"CustomizeManager.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CustomizeManager - Win32 Release"
# Name "CustomizeManager - Win32 Debug"
# Name "CustomizeManager - Win32 Unicode Release"
# Name "CustomizeManager - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Ultimate ToolBox"

# PROP Default_Filter "*.cpp"
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

SOURCE=..\..\..\source\OXBackgroundPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBMPFilePickerCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCaptionPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXChildFrameState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXColorPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXColorPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolControlOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeBackgroundPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeCaptionPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeCommandsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeCoolControlsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeInstanceManagerPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeIntelliMousePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeShortkeysPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeSplashWindowPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeTabbedMDIPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeToolbarsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeTrayIconPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeWorkspaceStatePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDockTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDocTemplateSpy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDragDockContext.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDragDropCommands.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXFontPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXFrameWndDock.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXHistoryCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXImageListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXInstanceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXIntelliMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXListBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMultiComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXOptionTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPopupBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRegistryValFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShortkeysOrganizer.cpp
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

SOURCE=..\..\..\source\OXSplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSplashWndDIB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSplitterColRowState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXWorkspaceState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Xstatus4.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeManager.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeManager.rc
# End Source File
# Begin Source File

SOURCE=.\CustomizeManagerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Ultimate ToolBox Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\include\OXCoolToolBar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeManager.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeManagerDoc.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeManagerView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CustomizeManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\CustomizeManager.rc2
# End Source File
# Begin Source File

SOURCE=.\res\CustomizeManagerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
