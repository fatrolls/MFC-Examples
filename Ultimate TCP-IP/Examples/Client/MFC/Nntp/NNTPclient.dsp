# Microsoft Developer Studio Project File - Name="NNTPclient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NNTPclient - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NNTPclient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NNTPclient.mak" CFG="NNTPclient - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NNTPclient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NNTPclient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "NNTPclient - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "NNTPclient - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NNTPclient - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /Ob1 /I "..\..\include" /I "..\..\..\..\Include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NNTPclient - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\INCLUDE" /I "..\..\..\..\Include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "NNTPclient - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "NNTPclient___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "NNTPclient___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Unicode_Debug"
# PROP Intermediate_Dir ".\Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\INCLUDE" /I "..\..\..\..\Include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\..\INCLUDE" /I "..\..\..\..\Include\\" /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "NNTPclient - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "NNTPclient___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "NNTPclient___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Unicode_Release"
# PROP Intermediate_Dir ".\Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\..\..\Include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /Ob1 /I "..\..\include" /I "..\..\..\..\Include\\" /D "_WINDOWS" /D "_AFXDLL" /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ws2_32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "NNTPclient - Win32 Release"
# Name "NNTPclient - Win32 Debug"
# Name "NNTPclient - Win32 Unicode Debug"
# Name "NNTPclient - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MyNntpClass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\Nartlist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\Ngrplist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\Nntpc.cpp
# End Source File
# Begin Source File

SOURCE=.\NNTPclient.cpp
# End Source File
# Begin Source File

SOURCE=.\NNTPclient.rc
# End Source File
# Begin Source File

SOURCE=.\NNTPclientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\richtext.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\ut_clnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\UT_HeaderEncoding.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\source\UT_StrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\UTDataSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\utfile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\UTMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\Utmime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\utstrlst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Source\UTUUEncode.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MyNntpClass.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\nntpc.h
# End Source File
# Begin Source File

SOURCE=.\NNTPclient.h
# End Source File
# Begin Source File

SOURCE=.\NNTPclientDlg.h
# End Source File
# Begin Source File

SOURCE=.\PostDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\richtext.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\ut_clnt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\ut_strop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\UTDataSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\UTEncode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\uterr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\utfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\UTMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\Utmime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\utstrlst.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\uttaglst.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Include\UTUUEncode.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\NNTPclient.ico
# End Source File
# Begin Source File

SOURCE=.\res\NNTPclient.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Filecopy.avi
# End Source File
# Begin Source File

SOURCE=.\res\Findcomp.avi
# End Source File
# Begin Source File

SOURCE=.\msnews.txt
# End Source File
# Begin Source File

SOURCE=.\psi.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Sakhr.txt
# End Source File
# End Target
# End Project
# Section NNTPclient : {E9A5593C-CAB0-11D1-8C0B-0000F8754DA1}
# 	2:5:Class:CRichText
# 	2:10:HeaderFile:richtext.h
# 	2:8:ImplFile:richtext.cpp
# End Section
# Section NNTPclient : {3B7C8860-D78F-101B-B9B5-04021C009402}
# 	2:21:DefaultSinkHeaderFile:richtext.h
# 	2:16:DefaultSinkClass:CRichText
# End Section
