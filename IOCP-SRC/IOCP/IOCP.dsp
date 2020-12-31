# Microsoft Developer Studio Project File - Name="IOCP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IOCP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IOCP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOCP.mak" CFG="IOCP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOCP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IOCP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IOCP - Win32 Release"

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

!ELSEIF  "$(CFG)" == "IOCP - Win32 Debug"

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

# Name "IOCP - Win32 Release"
# Name "IOCP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\HistoryEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCP.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCP.rc
# End Source File
# Begin Source File

SOURCE=.\IOCPBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\IOCPDlg.cpp
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

SOURCE=.\IOCP.h
# End Source File
# Begin Source File

SOURCE=.\IOCPBuffer.h
# End Source File
# Begin Source File

SOURCE=.\IOCPDlg.h
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

SOURCE=.\res\IOCP.ico
# End Source File
# Begin Source File

SOURCE=.\res\IOCP.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section IOCP : {0650B52C-1226-401D-806B-6E9404786330}
# 	1:12:IDD_SETTINGS:103
# 	2:16:Resource Include:resource.h
# 	2:22:CLASS: IOCPSettingsDlg:IOCPSettingsDlg
# 	2:17:IOCPSettingsDlg.h:IOCPSettingsDlg.h
# 	2:10:ENUM: enum:enum
# 	2:12:IDD_SETTINGS:IDD_SETTINGS
# 	2:19:Application Include:iocp.h
# 	2:19:IOCPSettingsDlg.cpp:IOCPSettingsDlg.cpp
# End Section
# Section IOCP : {4923360D-CA0E-431E-A037-5EC09BC37EBE}
# 	2:19:CLASS: CHistoryEdit:CHistoryEdit
# 	2:13:HistoryEdit.h:HistoryEdit.h
# 	2:15:HistoryEdit.cpp:HistoryEdit.cpp
# 	2:19:Application Include:IOCP.h
# End Section
