# Microsoft Developer Studio Project File - Name="ExtendedEditControls" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ExtendedEditControls - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ExtendedEditControls.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ExtendedEditControls.mak" CFG="ExtendedEditControls - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ExtendedEditControls - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ExtendedEditControls - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ExtendedEditControls - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "ExtendedEditControls - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "ExtendedEditControls - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ExtendedEditControls - Win32 Release"

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
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"ExtendedEditControls.exe"

!ELSEIF  "$(CFG)" == "ExtendedEditControls - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"ExtendedEditControls.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ExtendedEditControls - Win32 Release_Shared"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ExtendedEditControls___Win32_Release_Shared"
# PROP BASE Intermediate_Dir "ExtendedEditControls___Win32_Release_Shared"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"ExtendedEditControls.exe"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"ExtendedEditControls.exe"

!ELSEIF  "$(CFG)" == "ExtendedEditControls - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ExtendedEditControls___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "ExtendedEditControls___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"ExtendedEditControls.exe" /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"ExtendedEditControls.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "ExtendedEditControls - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ExtendedEditControls___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "ExtendedEditControls___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"ExtendedEditControls.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"ExtendedEditControls.exe"

!ENDIF 

# Begin Target

# Name "ExtendedEditControls - Win32 Release"
# Name "ExtendedEditControls - Win32 Debug"
# Name "ExtendedEditControls - Win32 Release_Shared"
# Name "ExtendedEditControls - Win32 Unicode_Debug"
# Name "ExtendedEditControls - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTBSource"

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

SOURCE=..\..\..\Source\OXBrowseColorEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBrowseDirEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalculatorCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCalculatorEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXColorPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXColorPickerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXCoolToolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXDirDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\oxdocktabctrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXDragDockContext.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXFolderPickerDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXFontPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXFrameWndDock.CPP
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHistoryCombo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMaskedEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMDIFloatWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPhysicalEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPhysicalEditEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPopupBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXRectTracker.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShellFolderTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXShellNamespaceNavigator.cpp
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

SOURCE=..\..\..\Source\OXStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXSzMiniDockFrmWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXToolTipCtrl.cpp
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

SOURCE=..\..\..\Source\Copytree.cpp
# End Source File
# Begin Source File

SOURCE=.\CurrencyEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Dir.cpp
# End Source File
# Begin Source File

SOURCE=.\DropEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Dstrlist.cpp
# End Source File
# Begin Source File

SOURCE=.\EditExtensionsSht.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendedEditControls.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendedEditControls.rc
# End Source File
# Begin Source File

SOURCE=.\ExtendedEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\File.cpp
# End Source File
# Begin Source File

SOURCE=.\MaskedEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NumericEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysicalEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Xstring.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CurrencyEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\DropEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditExtensionsSht.h
# End Source File
# Begin Source File

SOURCE=.\ExtendedEditControls.h
# End Source File
# Begin Source File

SOURCE=.\ExtendedEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\MaskedEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\NumericEditDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBrowseColorEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBrowseDirEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXColorPickerButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXColorPickerCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDirDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDropEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXFolderPickerDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXMaskedEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXPhysicalEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXPhysicalEditEx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXPopupBarCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXStatic.h
# End Source File
# Begin Source File

SOURCE=.\PhysicalEditDlg.h
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

SOURCE=.\res\ExtendedEditControls.ico
# End Source File
# Begin Source File

SOURCE=.\res\ExtendedEditControls.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ExtendedEditControls.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
