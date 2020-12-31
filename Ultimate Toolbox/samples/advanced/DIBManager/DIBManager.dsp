# Microsoft Developer Studio Project File - Name="DIBManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DIBManager - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DIBManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DIBManager.mak" CFG="DIBManager - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DIBManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DIBManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DIBManager - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /I "..\..\..\lib\jpeg\jpegsrc6" /I "..\..\..\lib\jpeg" /I "..\..\..\archive\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /i "..\..\..\lib\jpeg\jpegsrc6" /i "..\..\..\lib\jpeg" /i "..\..\..\archive\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /nodefaultlib:"MSVCRT" /out:"DIBManager.exe" /libpath:"..\..\..\lib\libs"

!ELSEIF  "$(CFG)" == "DIBManager - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /I "..\..\..\lib\jpeg\jpegsrc6" /I "..\..\..\lib\jpeg" /I "..\..\..\archive\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /i "..\..\..\lib\jpeg\jpegsrc6" /i "..\..\..\lib\jpeg" /i "..\..\..\archive\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jpgd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"DIBManager.exe" /pdbtype:sept /libpath:"..\..\..\lib\libs"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "DIBManager - Win32 Release"
# Name "DIBManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\Source\Convfile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Copytree.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Cpystdlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Dir.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Dirlist.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Dstrlist.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\File.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Filelist.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Mdeldlg.cpp"
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

SOURCE="..\..\..\Source\Oxbitbuf.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXBitmapMenu.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXBitmapMenuOrganizer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXBMPFle.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXCaptionPainter.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXChildFrameState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Oxcmpfl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Oxcompr.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXCoolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXCoolToolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDFlHdr.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Oxdib.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDirDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDlgBar.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\oxdocktabctrl.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDocTemplateSpy.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXDragDockContext.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXFrameWndDock.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXGphFle.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXHistoryCombo.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
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

SOURCE="..\..\..\Source\OXMDIFloatWnd.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMenuBar.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXRectTracker.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXRegistryItem.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRegistryValFile.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXRollup.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXScrollTip.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXScrollTipOwner.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXShortcutBar.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSizeCtrlBar.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSizeDlgBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSizeDockBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSizeToolBar.cpp"
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

SOURCE="..\..\..\Source\OXSplashWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSplashWndDIB.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSplitterColRowState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSplitterRect.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXSzMiniDockFrmWnd.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXTabClientWnd.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXTleBar.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXToolTipCtrl.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXUxTheme.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\OXWorkspaceState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Oxzoomvw.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Path.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Pathiter.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Progress.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Watchbuf.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Xstatus4.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\Source\Xstring.cpp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DIBManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DIBManager.rc
# End Source File
# Begin Source File

SOURCE=.\DIBManagerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DIBManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OXDocMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OXPreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\OXWinApp.cpp
# End Source File
# Begin Source File

SOURCE=.\ProtectedFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ResampleImageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScaleRollupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeFilesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkspaceDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\CONVFILE.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\CRYPFILE.h
# End Source File
# Begin Source File

SOURCE=.\DIBManager.h
# End Source File
# Begin Source File

SOURCE=.\DIBManagerDoc.h
# End Source File
# Begin Source File

SOURCE=.\DIBManagerView.h
# End Source File
# Begin Source File

SOURCE=.\ExportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImageInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXBitmapMenuOrganizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCMPFL.H
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXCOMPR.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDIB.H
# End Source File
# Begin Source File

SOURCE=.\OXDocMgr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OXPreviewDialog.h
# End Source File
# Begin Source File

SOURCE=.\OXWinApp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXZOOMVW.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXZOOMVW.inl
# End Source File
# Begin Source File

SOURCE=.\ProtectedFile.h
# End Source File
# Begin Source File

SOURCE=.\ResampleImageDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScaleRollupDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TreeFilesDlg.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\XSTATUS4.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\BMPdemo.BMP
# End Source File
# Begin Source File

SOURCE=.\res\check.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CoolBarWallPaper.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DIBManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\DIBManager.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DIBManagerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\dummy.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\dummy1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\dummyhot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\imagelis.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\logo_dum.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\mainfram_copy.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\newtool.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\ToolbarHot.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cup.avi
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\search.avi
# End Source File
# End Target
# End Project
