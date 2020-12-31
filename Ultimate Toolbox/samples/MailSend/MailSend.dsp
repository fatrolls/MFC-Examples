# Microsoft Developer Studio Project File - Name="MailSend" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MailSend - Win32 Unicode_Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MailSend.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MailSend.mak" CFG="MailSend - Win32 Unicode_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MailSend - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MailSend - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MailSend - Win32 Release_Shared" (based on "Win32 (x86) Application")
!MESSAGE "MailSend - Win32 Unicode_Debug" (based on "Win32 (x86) Application")
!MESSAGE "MailSend - Win32 Unicode_Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MailSend - Win32 Release"

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
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /machine:I386 /out:"MailSend.exe"

!ELSEIF  "$(CFG)" == "MailSend - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"MailSend.exe"

!ELSEIF  "$(CFG)" == "MailSend - Win32 Release_Shared"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MailSend"
# PROP BASE Intermediate_Dir "MailSend"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Shared"
# PROP Intermediate_Dir "Release_Shared"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "..\..\include" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib /nologo /subsystem:windows /machine:I386 /out:"MailSend.exe"
# ADD LINK32 mapi32.lib /nologo /subsystem:windows /machine:I386 /out:"MailSend.exe"

!ELSEIF  "$(CFG)" == "MailSend - Win32 Unicode_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MailSen0"
# PROP BASE Intermediate_Dir "MailSen0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NOT_REGISTERED" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"MailSend.exe"
# ADD LINK32 mapi32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /out:"MailSend.exe"

!ELSEIF  "$(CFG)" == "MailSend - Win32 Unicode_Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MailSen1"
# PROP BASE Intermediate_Dir "MailSen1"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\include" /I "..\..\..\Include" /I "..\..\..\Source\UTSampleAbout" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "NOT_REGISTERED" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
# ADD RSC /l 0x813 /i "..\..\..\Include" /i "..\..\..\Source\UTSampleAbout" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mapi32.lib /nologo /subsystem:windows /machine:I386 /out:"MailSend.exe"
# ADD LINK32 mapi32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"MailSend.exe"

!ENDIF 

# Begin Target

# Name "MailSend - Win32 Release"
# Name "MailSend - Win32 Debug"
# Name "MailSend - Win32 Release_Shared"
# Name "MailSend - Win32 Unicode_Debug"
# Name "MailSend - Win32 Unicode_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "UTSource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\OXDispatchMarshaller.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXFinalReleaseWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\oxmdisp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXOwnThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXOwnThreadCmdTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\OXSendMail.CPP
# End Source File
# Begin Source File

SOURCE=..\..\source\OXThreadEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\Xstring.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CgiHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cgitooledrv.cpp
# End Source File
# Begin Source File

SOURCE=.\MailEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\MailMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\MailSend.cpp
# End Source File
# Begin Source File

SOURCE=.\MailSend.odl
# End Source File
# Begin Source File

SOURCE=.\MailSend.rc
# End Source File
# Begin Source File

SOURCE=.\MailSendDlg.cpp
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

SOURCE=.\CgiHandler.h
# End Source File
# Begin Source File

SOURCE=.\CgiToOleDrv.h
# End Source File
# Begin Source File

SOURCE=.\MailCmd.h
# End Source File
# Begin Source File

SOURCE=.\MailEngine.h
# End Source File
# Begin Source File

SOURCE=.\MailMessage.h
# End Source File
# Begin Source File

SOURCE=.\MailSend.h
# End Source File
# Begin Source File

SOURCE=.\MailSendDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXDispatchMarshaller.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXFinalReleaseWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\oxmdisp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXOwnThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXOwnThreadCmdTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXSendMail.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\OXThreadEngine.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XString.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MailSend.ico
# End Source File
# Begin Source File

SOURCE=.\res\MailSend.rc2
# End Source File
# End Group
# End Target
# End Project
