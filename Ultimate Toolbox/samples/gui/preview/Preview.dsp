# Microsoft Developer Studio Project File - Name="Preview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Preview - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Preview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Preview.mak" CFG="Preview - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Preview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Preview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Preview - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "Preview - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "Preview - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Preview - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"Preview.exe"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Preview_"
# PROP BASE Intermediate_Dir ".\Preview_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Preview_"
# PROP Intermediate_Dir ".\Preview_"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\..\..\Lib\libs\jpgd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /out:"Preview.exe"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Preview_"
# PROP BASE Intermediate_Dir "Preview_"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /I "..\..\..\Lib\Jpeg" /I "..\..\..\Lib\Jpeg\Jpegsrc6" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Preview.exe"
# ADD LINK32 ..\..\..\Lib\libs\jpgr.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /out:"Preview.exe"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Preview0"
# PROP BASE Intermediate_Dir "Preview0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NOT_REGISTERED" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Preview.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"Preview.exe"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Preview1"
# PROP BASE Intermediate_Dir "Preview1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\..\include" /I "..\..\..\source\utsampleabout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /D "_UNICODE" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\..\..\include" /i "..\..\..\source\utsampleabout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386 /out:"Preview.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"Preview.exe"

!ENDIF 

# Begin Target

# Name "Preview - Win32 Release"
# Name "Preview - Win32 Debug"
# Name "Preview - Win32 Release_Shared"
# Name "Preview - Win32 Unicode_Debug"
# Name "Preview - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\UTSampleAbout\HtmlCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXBMPFle.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Oxdib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXGphFle.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXImageListBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGCod.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGCom.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGDom.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGExp.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXJPGFle.cpp

!IF  "$(CFG)" == "Preview - Win32 Release"

!ELSEIF  "$(CFG)" == "Preview - Win32 Debug"

!ELSEIF  "$(CFG)" == "Preview - Win32 Release_Shared"

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Preview - Win32 Unicode_Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXMetaFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\OXPreviewDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UTBStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UTSampleAbout\UTSampleAbout.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OXDocMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\OXWinApp.CPP
# End Source File
# Begin Source File

SOURCE=.\Preview.cpp
# End Source File
# Begin Source File

SOURCE=.\Preview.rc
# End Source File
# Begin Source File

SOURCE=.\PreviewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewView.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDIB.H
# End Source File
# Begin Source File

SOURCE=.\OXDocMgr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXImageListBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXMetaFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXPreviewDialog.h
# End Source File
# Begin Source File

SOURCE=.\OXWinApp.H
# End Source File
# Begin Source File

SOURCE=.\Preview.h
# End Source File
# Begin Source File

SOURCE=.\PreviewDoc.h
# End Source File
# Begin Source File

SOURCE=.\PreviewView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Preview.ico
# End Source File
# Begin Source File

SOURCE=.\res\Preview.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PreviewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Preview.exe.manifest
# End Source File
# End Target
# End Project
