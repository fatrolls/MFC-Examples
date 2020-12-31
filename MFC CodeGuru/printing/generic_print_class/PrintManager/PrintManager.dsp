# Microsoft Developer Studio Project File - Name="PrintManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PrintManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PrintManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PrintManager.mak" CFG="PrintManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PrintManager - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PrintManager - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PrintManager - Win32 Release"

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
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PrintManager - Win32 Debug"

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
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PrintManager - Win32 Release"
# Name "PrintManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CoolButton.cpp
# End Source File
# Begin Source File

SOURCE=.\FontCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\ListPrintPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\ListPrintPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\ListPrintSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintManager.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintManager.rc

!IF  "$(CFG)" == "PrintManager - Win32 Release"

!ELSEIF  "$(CFG)" == "PrintManager - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PrintManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CoolButton.h
# End Source File
# Begin Source File

SOURCE=.\FontCombo.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlPrint.h
# End Source File
# Begin Source File

SOURCE=.\ListPrintPage1.h
# End Source File
# Begin Source File

SOURCE=.\ListPrintPage2.h
# End Source File
# Begin Source File

SOURCE=.\ListPrintSetup.h
# End Source File
# Begin Source File

SOURCE=.\PrinterJob.h
# End Source File
# Begin Source File

SOURCE=.\PrintManager.h
# End Source File
# Begin Source File

SOURCE=.\PrintManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrintStatus.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\PrintManager.ico
# End Source File
# Begin Source File

SOURCE=.\res\PrintManager.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\file_dbl.avi
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section PrintManager : {4A44D713-9E2A-11D1-8BB1-0000B43382FE}
# 	2:14:PrinterJob.cpp:PrinterJob.cpp
# 	2:19:Application Include:PrintManager.h
# 	2:18:CLASS: CPrinterJob:CPrinterJob
# 	2:12:PrinterJob.h:PrinterJob.h
# End Section
# Section PrintManager : {4A44D717-9E2A-11D1-8BB1-0000B43382FE}
# 	1:13:IDD_LISTSETUP:105
# 	2:16:Resource Include:resource.h
# 	2:13:IDD_LISTSETUP:IDD_LISTSETUP
# 	2:16:ListPrintSetup.h:ListPrintSetup.h
# 	2:10:ENUM: enum:enum
# 	2:22:CLASS: CListPrintSetup:CListPrintSetup
# 	2:18:ListPrintSetup.cpp:ListPrintSetup.cpp
# 	2:19:Application Include:PrintManager.h
# End Section
# Section PrintManager : {4A44D712-9E2A-11D1-8BB1-0000B43382FE}
# 	1:16:IDD_PRINT_STATUS:106
# 	2:16:Resource Include:resource.h
# 	2:19:CLASS: CPrintStatus:CPrintStatus
# 	2:15:PrintStatus.cpp:PrintStatus.cpp
# 	2:13:PrintStatus.h:PrintStatus.h
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:PrintManager.h
# 	2:16:IDD_PRINT_STATUS:IDD_PRINT_STATUS
# End Section
# Section PrintManager : {4A44D716-9E2A-11D1-8BB1-0000B43382FE}
# 	1:13:IDD_LISTPAGE2:104
# 	2:16:Resource Include:resource.h
# 	2:22:CLASS: CListPrintPage2:CListPrintPage2
# 	2:10:ENUM: enum:enum
# 	2:13:IDD_LISTPAGE2:IDD_LISTPAGE2
# 	2:18:ListPrintPage2.cpp:ListPrintPage2.cpp
# 	2:19:Application Include:PrintManager.h
# 	2:16:ListPrintPage2.h:ListPrintPage2.h
# End Section
# Section PrintManager : {4A44D715-9E2A-11D1-8BB1-0000B43382FE}
# 	1:13:IDD_LISTPAGE1:103
# 	2:16:Resource Include:resource.h
# 	2:22:CLASS: CListPrintPage1:CListPrintPage1
# 	2:13:IDD_LISTPAGE1:IDD_LISTPAGE1
# 	2:10:ENUM: enum:enum
# 	2:18:ListPrintPage1.cpp:ListPrintPage1.cpp
# 	2:19:Application Include:PrintManager.h
# 	2:16:ListPrintPage1.h:ListPrintPage1.h
# End Section
# Section PrintManager : {4A44D719-9E2A-11D1-8BB1-0000B43382FE}
# 	2:12:CoolButton.h:CoolButton.h
# 	2:14:CoolButton.cpp:CoolButton.cpp
# 	2:18:CLASS: CCoolButton:CCoolButton
# 	2:19:Application Include:PrintManager.h
# End Section
# Section PrintManager : {4A44D714-9E2A-11D1-8BB1-0000B43382FE}
# 	2:17:ListCtrlPrint.cpp:ListCtrlPrint.cpp
# 	2:15:ListCtrlPrint.h:ListCtrlPrint.h
# 	2:19:Application Include:PrintManager.h
# 	2:21:CLASS: CListCtrlPrint:CListCtrlPrint
# End Section
# Section PrintManager : {4A44D718-9E2A-11D1-8BB1-0000B43382FE}
# 	2:13:FontCombo.cpp:FontCombo.cpp
# 	2:17:CLASS: CFontCombo:CFontCombo
# 	2:11:FontCombo.h:FontCombo.h
# 	2:19:Application Include:PrintManager.h
# End Section
