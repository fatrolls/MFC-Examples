# Microsoft Developer Studio Project File - Name="ZapMail" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ZapMail - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ZapMail.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ZapMail.mak" CFG="ZapMail - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZapMail - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ZapMail - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZapMail - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ZapMail - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ZapMail - Win32 Release"
# Name "ZapMail - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppOctetStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Base64.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAttachments.cpp
# End Source File
# Begin Source File

SOURCE=.\MailMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\MIMECode.cpp
# End Source File
# Begin Source File

SOURCE=.\MIMEContentAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\MIMEMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\SMTP.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextPlain.cpp
# End Source File
# Begin Source File

SOURCE=.\ZapMail.cpp
# End Source File
# Begin Source File

SOURCE=.\ZapMail.rc
# End Source File
# Begin Source File

SOURCE=.\ZapMailDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppOctetStream.h
# End Source File
# Begin Source File

SOURCE=.\Base64.h
# End Source File
# Begin Source File

SOURCE=.\DlgAttachments.h
# End Source File
# Begin Source File

SOURCE=.\MailMessage.h
# End Source File
# Begin Source File

SOURCE=.\MIMECode.h
# End Source File
# Begin Source File

SOURCE=.\MIMEContentAgent.h
# End Source File
# Begin Source File

SOURCE=.\MIMEMessage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SMTP.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextPlain.h
# End Source File
# Begin Source File

SOURCE=.\ZapMail.h
# End Source File
# Begin Source File

SOURCE=.\ZapMailDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ZapMail.ico
# End Source File
# Begin Source File

SOURCE=.\res\ZapMail.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ZapMail : {333BA6C6-F593-11D1-870E-444553540001}
# 	2:13:MailMessage.h:MailMessage.h
# 	2:15:MailMessage.cpp:MailMessage.cpp
# 	2:19:CLASS: CMailMessage:CMailMessage
# 	2:19:Application Include:ZapMail.h
# End Section
# Section ZapMail : {333BA6C5-F593-11D1-870E-444553540001}
# 	2:8:Base64.h:Base64.h
# 	2:14:CLASS: CBase64:CBase64
# 	2:19:Application Include:ZapMail.h
# 	2:10:Base64.cpp:Base64.cpp
# End Section
# Section ZapMail : {333BA6C9-F593-11D1-870E-444553540001}
# 	2:10:MIMEType.h:MIMEType.h
# 	2:12:MIMEType.cpp:MIMEType.cpp
# 	2:16:CLASS: CMIMEType:CMIMEType
# 	2:19:Application Include:ZapMail.h
# End Section
# Section ZapMail : {333BA6C4-F593-11D1-870E-444553540001}
# 	2:18:AppOctetStream.cpp:AppOctetStream.cpp
# 	2:22:CLASS: CAppOctetStream:CAppOctetStream
# 	2:19:Application Include:ZapMail.h
# 	2:16:AppOctetStream.h:AppOctetStream.h
# End Section
# Section ZapMail : {333BA6CB-F593-11D1-870E-444553540001}
# 	2:17:CLASS: CTextPlain:CTextPlain
# 	2:13:TextPlain.cpp:TextPlain.cpp
# 	2:11:TextPlain.h:TextPlain.h
# 	2:19:Application Include:ZapMail.h
# End Section
# Section ZapMail : {333BA6C8-F593-11D1-870E-444553540001}
# 	2:13:MIMEMessage.h:MIMEMessage.h
# 	2:23:ENUM: eMIMEEncodingCode:eMIMEEncodingCode
# 	2:19:CLASS: CMIMEMessage:CMIMEMessage
# 	2:19:ENUM: eMIMETypeCode:eMIMETypeCode
# 	2:15:MIMEMessage.cpp:MIMEMessage.cpp
# 	2:19:Application Include:ZapMail.h
# End Section
# Section ZapMail : {333BA6CA-F593-11D1-870E-444553540001}
# 	2:12:CLASS: CSMTP:CSMTP
# 	2:15:ENUM: eResponse:eResponse
# 	2:8:SMTP.cpp:SMTP.cpp
# 	2:19:Application Include:ZapMail.h
# 	2:6:SMTP.h:SMTP.h
# End Section
# Section ZapMail : {333BA6C7-F593-11D1-870E-444553540001}
# 	2:10:MIMECode.h:MIMECode.h
# 	2:12:MIMECode.cpp:MIMECode.cpp
# 	2:16:CLASS: CMIMECode:CMIMECode
# 	2:19:Application Include:ZapMail.h
# End Section
