# Microsoft Developer Studio Project File - Name="VisualStudioLikeDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisualStudioLikeDemo - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisualStudioLikeDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisualStudioLikeDemo.mak" CFG="VisualStudioLikeDemo - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisualStudioLikeDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisualStudioLikeDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VisualStudioLikeDemo - Win32 Debug_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "VisualStudioLikeDemo - Win32 Release_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "VisualStudioLikeDemo - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisualStudioLikeDemo - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"VisualStudioLikeDemo.exe"

!ELSEIF  "$(CFG)" == "VisualStudioLikeDemo - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"VisualStudioLikeDemo.exe"
# SUBTRACT LINK32 /profile /map

!ELSEIF  "$(CFG)" == "VisualStudioLikeDemo - Win32 Debug_Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "VisualStudioLikeDemo___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "VisualStudioLikeDemo___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"VisualStudioLikeDemo.exe"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"VisualStudioLikeDemo.exe"
# SUBTRACT LINK32 /profile /map

!ELSEIF  "$(CFG)" == "VisualStudioLikeDemo - Win32 Release_Unicode"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VisualStudioLikeDemo___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "VisualStudioLikeDemo___Win32_Release_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /Zd /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"VisualStudioLikeDemo.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"VisualStudioLikeDemo.exe"

!ELSEIF  "$(CFG)" == "VisualStudioLikeDemo - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VisualStudioLikeDemo___Win32_Release_Shared"
# PROP BASE Intermediate_Dir "VisualStudioLikeDemo___Win32_Release_Shared"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"VisualStudioLikeDemo.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"VisualStudioLikeDemo.exe"

!ENDIF 

# Begin Target

# Name "VisualStudioLikeDemo - Win32 Release"
# Name "VisualStudioLikeDemo - Win32 Debug"
# Name "VisualStudioLikeDemo - Win32 Debug_Unicode"
# Name "VisualStudioLikeDemo - Win32 Release_Unicode"
# Name "VisualStudioLikeDemo - Win32 Release_Shared"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTBSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Source\COPYTREE.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\DIR.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\DSTRLIST.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\FILE.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\MFCToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OX3DTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXAdvancedAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXAdvancedAssertMail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBackgroundPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBMPFilePickerCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCaptionPainter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXColorPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXColorPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCoolComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolControlOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeBackgroundPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeCaptionPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeCoolControlsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCustomizeIntelliMousePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeSplashWindowPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeTrayIconPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDockTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXDragDockContext.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXFontPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXFrameWndDock.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHistoryCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXIntelliMouse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXIteratorRegistryItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMultiComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPopupBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRegistryItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXScrollWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSizeCtrlBar.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSizeDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSizeDockBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSizeToolBar.cpp
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

SOURCE=..\..\..\Source\OXSplashWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSplashWndDIB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSplitterRect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTabView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Path.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Xstatus4.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\XSTRING.CPP
# End Source File
# End Group
# Begin Group "CustomizeManagerFramework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Source\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXChildFrameState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeCommandsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeInstanceManagerPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeShortkeysPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeTabbedMDIPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeToolbarsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCustomizeWorkspaceStatePage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXDocTemplateSpy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXDragDropCommands.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHistoryCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXImageListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXInstanceManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXLayoutManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXListBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXOptionTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRegistryValFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShortkeysOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSplitterColRowState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTaskbarIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXWorkspaceState.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\3DTabViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemo.rc
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemoView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3DTabViewBar.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OX3DTabView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBackgroundPainter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBaseSubclassedComboBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapMenuOrganizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCaptionPainter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCoolToolBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeBackgroundPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeCaptionPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeCommandsPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeInstanceManagerPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizePage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeShortkeysPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeSplashWindowPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeToolbarsPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeTrayIconPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCustomizeWorkspaceStatePage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDragDropCommands.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXFontPickerButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXFrameWndDock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHistoryCombo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHistoryCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXImageListBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXIteratorRegistryItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXMenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXRegistryItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXRegistryItem.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXScrollWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXShortcutBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXShortkeysOrganizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSizeCtrlBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSizeDockBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OXSkins.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSplashWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSplitterRect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXStatic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OXSzMiniDockFrmWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTabClientWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTabView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTaskbarIcon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXTaskbarIcon.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXWorkspaceState.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabViewBar.h
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemo.h
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\VisualStudioLikeDemoView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\coolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il_3dtab.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il_class.bmp
# End Source File
# Begin Source File

SOURCE=.\res\il_filev.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_window.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VisualStudioLikeDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisualStudioLikeDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VisualStudioLikeDemoDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
