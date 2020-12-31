# Microsoft Developer Studio Project File - Name="XHtmlTreeTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XHtmlTreeTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XHtmlTreeTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XHtmlTreeTest.mak" CFG="XHtmlTreeTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XHtmlTreeTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XHtmlTreeTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XHtmlTreeTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_VC60"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XHtmlTreeTest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "_VC60"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XHtmlTreeTest - Win32 Release"
# Name "XHtmlTreeTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\About.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CheckedItemsDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\CreateCheckboxImageList.cpp
# ADD CPP /Yu
# End Source File
# Begin Source File

SOURCE=..\src\FindDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\FontSize.cpp
# End Source File
# Begin Source File

SOURCE=..\src\MainDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PPHtmlDrawer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\PPTooltip.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ResourceFile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\ResourceTextFile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\ROEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\src\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\src\VisualStylesXP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XBreadCrumbBar.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\XColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XEditPrompt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XGlyphButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlDraw.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlDrawLink.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTree.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTreeTest.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTreeTest.rc
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTreeTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XmlDocument.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XNamedColors.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\XString.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\About.h
# End Source File
# Begin Source File

SOURCE=..\src\CeXDib.h
# End Source File
# Begin Source File

SOURCE=..\src\CheckedItemsDialog.h
# End Source File
# Begin Source File

SOURCE=..\src\Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\src\ColorDlg.h
# End Source File
# Begin Source File

SOURCE=..\src\CreateCheckboxImageList.h
# End Source File
# Begin Source File

SOURCE=..\src\FindDialog.h
# End Source File
# Begin Source File

SOURCE=..\src\FontSize.h
# End Source File
# Begin Source File

SOURCE=..\src\MainDialog.h
# End Source File
# Begin Source File

SOURCE=..\src\PPDrawManager.h
# End Source File
# Begin Source File

SOURCE=..\src\PPHtmlDrawer.h
# End Source File
# Begin Source File

SOURCE=..\src\PPTooltip.h
# End Source File
# Begin Source File

SOURCE=..\src\Resource.h
# End Source File
# Begin Source File

SOURCE=..\src\ResourceFile.h
# End Source File
# Begin Source File

SOURCE=..\src\ResourceTextFile.h
# End Source File
# Begin Source File

SOURCE=..\src\ROEdit.h
# End Source File
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\VisualStylesXP.h
# End Source File
# Begin Source File

SOURCE=..\src\XBreadCrumbBar.h
# End Source File
# Begin Source File

SOURCE=..\src\XColorStatic.h
# End Source File
# Begin Source File

SOURCE=..\src\XColourPicker.h
# End Source File
# Begin Source File

SOURCE=..\src\XColourPopup.h
# End Source File
# Begin Source File

SOURCE=..\src\XEditPrompt.h
# End Source File
# Begin Source File

SOURCE=..\src\XGlyphButton.h
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlDraw.h
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlDrawLink.h
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTree.h
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTreeTest.h
# End Source File
# Begin Source File

SOURCE=..\src\XHtmlTreeTestDlg.h
# End Source File
# Begin Source File

SOURCE=..\src\XHyperLink.h
# End Source File
# Begin Source File

SOURCE=..\src\XListBox.h
# End Source File
# Begin Source File

SOURCE=..\src\XMessageBox.h
# End Source File
# Begin Source File

SOURCE=..\src\XmlDocument.h
# End Source File
# Begin Source File

SOURCE=..\src\XNamedColors.h
# End Source File
# Begin Source File

SOURCE=..\src\XString.h
# End Source File
# Begin Source File

SOURCE=..\src\XTrace.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\src\dogs.bmp
# End Source File
# Begin Source File

SOURCE=..\src\drag.cur
# End Source File
# Begin Source File

SOURCE=..\src\drop.cur
# End Source File
# Begin Source File

SOURCE=..\src\dropcopy.cur
# End Source File
# Begin Source File

SOURCE=..\src\dropmove.cur
# End Source File
# Begin Source File

SOURCE=..\src\golden_retriever.bmp
# End Source File
# Begin Source File

SOURCE=..\src\hans.ico
# End Source File
# Begin Source File

SOURCE=..\src\nodrop.cur
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\dogs.txt
# End Source File
# Begin Source File

SOURCE=..\src\dogs.xml
# End Source File
# Begin Source File

SOURCE=..\src\dogs10.txt
# End Source File
# Begin Source File

SOURCE=..\src\dogs10.xml
# End Source File
# Begin Source File

SOURCE=..\src\WoofWoof.wav
# End Source File
# End Target
# End Project
