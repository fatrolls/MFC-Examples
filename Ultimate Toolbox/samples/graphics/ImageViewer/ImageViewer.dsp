# Microsoft Developer Studio Project File - Name="ImageViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ImageViewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImageViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImageViewer.mak" CFG="ImageViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ImageViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ImageViewer - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageViewer - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "OXSCRLWND_USE_RULER" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ImageViewer.exe"

!ELSEIF  "$(CFG)" == "ImageViewer - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "OXSCRLWND_USE_RULER" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\Lib\libs\jpgd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"ImageViewer.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ImageViewer - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ImageViewer___Win32_Release_Shared"
# PROP BASE Intermediate_Dir "ImageViewer___Win32_Release_Shared"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "OXSCRLWND_USE_RULER" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "OXSCRLWND_USE_RULER" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "NDEBUG"
# ADD RSC /l 0x1009 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /i "..\..\..\Lib\Jpeg" /i "..\..\..\Lib\Jpeg\Jpegsrc6" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\Lib\libs\jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ImageViewer.exe"
# ADD LINK32 ..\..\..\Lib\libs\jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"ImageViewer.exe"

!ENDIF 

# Begin Target

# Name "ImageViewer - Win32 Release"
# Name "ImageViewer - Win32 Debug"
# Name "ImageViewer - Win32 Release_Shared"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "UTBSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBMPFle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXGphFle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXHookWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXImageViewer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGCod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGCom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGDom.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGExp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGFle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXRulerOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXScrollWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewer.rc
# End Source File
# Begin Source File

SOURCE=.\ImageViewerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageViewerView.cpp
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
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewer.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewerDoc.h
# End Source File
# Begin Source File

SOURCE=.\ImageViewerView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\Oxdib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXHookWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXImageViewer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXJPGCod.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXJPGCom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXJPGDom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXJPGExp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXJPGFle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXRulerOrganizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXScrollWnd.h
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

SOURCE=.\res\ImageViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\ImageViewer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ImageViewerDoc.ico
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
