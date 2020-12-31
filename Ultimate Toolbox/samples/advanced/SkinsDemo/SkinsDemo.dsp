# Microsoft Developer Studio Project File - Name="SkinsDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SkinsDemo - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SkinsDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SkinsDemo.mak" CFG="SkinsDemo - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SkinsDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SkinsDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SkinsDemo - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "SkinsDemo - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SkinsDemo - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"SkinsDemo.exe"

!ELSEIF  "$(CFG)" == "SkinsDemo - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"SkinsDemo.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "SkinsDemo - Win32 Unicode Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SkinsDemo___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "SkinsDemo___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"SkinsDemo.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"SkinsDemo.exe"

!ELSEIF  "$(CFG)" == "SkinsDemo - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SkinsDemo___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "SkinsDemo___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"SkinsDemo.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"SkinsDemo.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SkinsDemo - Win32 Release"
# Name "SkinsDemo - Win32 Debug"
# Name "SkinsDemo - Win32 Unicode Release"
# Name "SkinsDemo - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Ultimate Toolbox Source"

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

SOURCE=..\..\..\source\OXBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBitmapMenuOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBrowseColorEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXBrowseDirEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalculatorCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalculatorEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalendar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalendarEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXChildFrameState.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXColorPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolComboBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolToolBar.cpp
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

SOURCE=..\..\..\source\OXEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXFolderPickerDlg.cpp
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

SOURCE=..\..\..\source\OXIPEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXItemTip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXItemTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXListEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMaskedEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPhysicalEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPhysicalEditEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPopupBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPropertiesWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPropertyDescriptionPane.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\oxpropertytree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShdWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShellFolderTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShellNamespaceNavigator.cpp
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

SOURCE="..\..\..\Source\OXToolTipCtrl.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeCal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTreeItem.cpp
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

SOURCE=.\FoldersBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinsDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinsDemo.rc
# End Source File
# Begin Source File

SOURCE=.\SkinsDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SkinsDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\FoldersBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesBar.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SkinsDemo.h
# End Source File
# Begin Source File

SOURCE=.\SkinsDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\SkinsDemoView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\command_group.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\custom_button.ico
# End Source File
# Begin Source File

SOURCE=.\res\large.bmp
# End Source File
# Begin Source File

SOURCE=..\..\gui\Shortcutbar\res\large.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\new_popup_menu.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\noimage.ico
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\OXHandCursor.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\OXNoHandCursor.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\OXNotes.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\OXSpinHor.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\OXSpinVer.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\oxtbcopy.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\oxtbmove.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\oxtbremove.cur
# End Source File
# Begin Source File

SOURCE=.\res\properties_toolbar.bmp
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_all.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_bottomleft.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_bottomright.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_down.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_left.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_leftright.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_right.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_topbottom.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_topleft.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_topright.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\scrl_up.cur
# End Source File
# Begin Source File

SOURCE=..\..\..\include\res\separator.ico
# End Source File
# Begin Source File

SOURCE=..\..\gui\Shortcutbar\res\ShortcutBar.ico
# End Source File
# Begin Source File

SOURCE=.\res\SkinsDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\SkinsDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SkinsDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\small.bmp
# End Source File
# Begin Source File

SOURCE=..\..\gui\Shortcutbar\res\small.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar2Disabled.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar2Hot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar2Normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_buttons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TreeImages.bmp
# End Source File
# Begin Source File

SOURCE=..\..\gui\Shortcutbar\res\TreeImages.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
