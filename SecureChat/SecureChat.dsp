# Microsoft Developer Studio Project File - Name="SecureChat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SecureChat - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SecureChat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SecureChat.mak" CFG="SecureChat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SecureChat - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SecureChat - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SecureChat - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ox /Ot /Ow /Og /Oi /Op /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Oa
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x417 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SecureChat - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SecureChat - Win32 Release"
# Name "SecureChat - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\HistoryEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPS.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCryptLib.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\RanDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Rijndael.cpp
# End Source File
# Begin Source File

SOURCE=.\SecureChat.cpp
# End Source File
# Begin Source File

SOURCE=.\SecureChat.rc
# End Source File
# Begin Source File

SOURCE=.\SecureChatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SecureChatIOCP.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\HistoryEdit.h
# End Source File
# Begin Source File

SOURCE=.\IOCPBuffer.h
# End Source File
# Begin Source File

SOURCE=.\IOCPS.h
# End Source File
# Begin Source File

SOURCE=.\MyCryptLib.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\RanDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Rijndael.h
# End Source File
# Begin Source File

SOURCE=.\SecureChat.h
# End Source File
# Begin Source File

SOURCE=.\SecureChatDlg.h
# End Source File
# Begin Source File

SOURCE=.\SecureChatIOCP.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SecureChat.ico
# End Source File
# Begin Source File

SOURCE=.\res\SecureChat.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section SecureChat : {A9069EFC-CE12-4AA9-B3AB-6674BFF03C05}
# 	2:12:Rijndael.cpp:Rijndael.cpp
# 	2:16:CLASS: CRijndael:CRijndael
# 	2:10:ENUM: enum:enum
# 	2:10:Rijndael.h:Rijndael.h
# 	2:19:Application Include:SecureChat.h
# End Section
# Section SecureChat : {1D59376E-425A-49E9-96D5-5A5C460D73C9}
# 	1:10:IDD_RANDOM:103
# 	2:16:Resource Include:resource.h
# 	2:10:IDD_RANDOM:IDD_RANDOM
# 	2:10:ENUM: enum:enum
# 	2:13:RanDialog.cpp:RanDialog.cpp
# 	2:11:RanDialog.h:RanDialog.h
# 	2:17:CLASS: CRanDialog:CRanDialog
# 	2:19:Application Include:SecureChat.h
# End Section
# Section SecureChat : {DD3CCC5A-974C-4F72-B2BE-73006EEABEF5}
# 	2:18:CLASS: tagITEMINFO:tagITEMINFO
# 	2:14:MyListCtrl.cpp:MyListCtrl.cpp
# 	2:17:CLASS: MyListCtrl:MyListCtrl
# 	2:12:MyListCtrl.h:MyListCtrl.h
# 	2:17:TYPEDEF: ITEMINFO:ITEMINFO
# 	2:19:Application Include:SecureChat.h
# End Section
# Section SecureChat : {A7E640AE-00F2-4AA1-8023-CC0F96C3CBC5}
# 	2:19:Application Include:SecureChat.h
# 	2:14:IOCPBuffer.cpp:IOCPBuffer.cpp
# 	2:18:CLASS: CIOCPBuffer:CIOCPBuffer
# 	2:12:IOCPBuffer.h:IOCPBuffer.h
# End Section
# Section SecureChat : {26E5C0D5-F119-4FD7-A41B-3226F85E6706}
# 	2:19:CLASS: CHistoryEdit:CHistoryEdit
# 	2:13:HistoryEdit.h:HistoryEdit.h
# 	2:15:HistoryEdit.cpp:HistoryEdit.cpp
# 	2:19:Application Include:SecureChat.h
# End Section
# Section SecureChat : {6DC3D60F-F204-4C43-BE92-A0CDF727019B}
# 	2:13:CLASS: MyIOCP:MyIOCP
# 	2:8:MyIOCP.h:MyIOCP.h
# 	2:10:MyIOCP.cpp:MyIOCP.cpp
# 	2:19:Application Include:SecureChat.h
# End Section
# Section SecureChat : {D2DAD8BA-DC8C-4EFD-8C92-A603562965CF}
# 	2:20:CLASS: ClientContext:ClientContext
# 	2:14:CLASS: JobItem:JobItem
# 	2:18:TYPEDEF: BufferMap:BufferMap
# 	2:19:TYPEDEF: ContextMap:ContextMap
# 	2:12:ENUM: IOType:IOType
# 	2:9:IOCPS.cpp:IOCPS.cpp
# 	2:12:CLASS: IOCPS:IOCPS
# 	2:13:ENUM: JobType:JobType
# 	2:19:Application Include:SecureChat.h
# 	2:7:IOCPS.h:IOCPS.h
# 	2:13:FUNC: HashKey:HashKey
# End Section
