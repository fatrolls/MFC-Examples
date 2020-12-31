# Microsoft Developer Studio Project File - Name="IOCPClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IOCPCLIENT - WIN32 RELEASE
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IOCPClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOCPClient.mak" CFG="IOCPCLIENT - WIN32 RELEASE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOCPClient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IOCPClient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IOCPClient - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Mswsock.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "IOCPClient - Win32 Debug"

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
# ADD LINK32 Mswsock.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "IOCPClient - Win32 Release"
# Name "IOCPClient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\HistoryEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPClient.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPClient.rc
# End Source File
# Begin Source File

SOURCE=.\IOCPClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPS.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPSettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyIOCP.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
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

SOURCE=.\IOCPClient.h
# End Source File
# Begin Source File

SOURCE=.\IOCPClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\IOCPS.h
# End Source File
# Begin Source File

SOURCE=.\IOCPSettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyIOCP.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
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

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IOCPClient.ico
# End Source File
# Begin Source File

SOURCE=.\res\IOCPClient.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section IOCPClient : {135AE426-195C-47B0-9F8D-78DD4D4D6B61}
# 	2:19:CLASS: MyIOCPServer:MyIOCPServer
# 	2:16:MyIOCPServer.cpp:MyIOCPServer.cpp
# 	2:14:MyIOCPServer.h:MyIOCPServer.h
# 	2:22:CLASS: MyClientContext:MyClientContext
# 	2:14:ENUM: MYIOType:MYIOType
# 	2:23:CLASS: MYOVERLAPPEDPLUS:MYOVERLAPPEDPLUS
# 	2:19:Application Include:IOCPClient.h
# End Section
# Section IOCPClient : {4923360D-CA0E-431E-A037-5EC09BC37EBE}
# 	2:19:CLASS: CHistoryEdit:CHistoryEdit
# 	2:13:HistoryEdit.h:HistoryEdit.h
# 	2:15:HistoryEdit.cpp:HistoryEdit.cpp
# 	2:19:Application Include:IOCPClient.h
# End Section
# Section IOCPClient : {6D83324B-DD14-464B-A03E-92EFCD9338E8}
# 	2:14:CLASS: JobItem:JobItem
# 	2:19:CLASS: MyIOCPServer:MyIOCPServer
# 	2:16:MyIOCPServer.cpp:MyIOCPServer1.cpp
# 	2:13:ENUM: JobType:JobType
# 	2:14:MyIOCPServer.h:MyIOCPServer1.h
# 	2:22:CLASS: MyClientContext:MyClientContext
# 	2:14:ENUM: MYIOType:MYIOType
# 	2:19:Application Include:IOCPClient.h
# End Section
# Section IOCPClient : {4329A8A3-34D9-4257-9F1B-D4547A9CBA54}
# 	2:19:RWCriticalSection.h:RWCriticalSection.h
# 	2:21:RWCriticalSection.cpp:RWCriticalSection.cpp
# 	2:19:Application Include:IOCPClient.h
# 	2:25:CLASS: CRWCriticalSection:CRWCriticalSection
# End Section
# Section IOCPClient : {02597870-3F33-4E3A-AF06-456C75B7722B}
# 	2:19:Application Include:IOCPClient.h
# 	2:14:IOCPBuffer.cpp:IOCPBuffer.cpp
# 	2:18:CLASS: CIOCPBuffer:CIOCPBuffer
# 	2:12:IOCPBuffer.h:IOCPBuffer.h
# End Section
