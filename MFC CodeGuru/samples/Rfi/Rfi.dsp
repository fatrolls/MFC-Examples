# Microsoft Developer Studio Project File - Name="Rfi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Rfi - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Rfi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rfi.mak" CFG="Rfi - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Rfi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Rfi - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Rfi - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /incremental:yes /debug /machine:I386

!ELSEIF  "$(CFG)" == "Rfi - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "Rfi - Win32 Release"
# Name "Rfi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AddRepeatersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CompleteSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteRepeatersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditRepeaterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\lbctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ntray.cpp
# End Source File
# Begin Source File

SOURCE=.\Rfi.cpp
# End Source File
# Begin Source File

SOURCE=.\Rfi.rc

!IF  "$(CFG)" == "Rfi - Win32 Release"

!ELSEIF  "$(CFG)" == "Rfi - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RfiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AddRepeatersDlg.h
# End Source File
# Begin Source File

SOURCE=.\CompleteSet.h
# End Source File
# Begin Source File

SOURCE=.\DeleteRepeatersDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditRepeaterDlg.h
# End Source File
# Begin Source File

SOURCE=.\lbctrl.h
# End Source File
# Begin Source File

SOURCE=.\ntray.h
# End Source File
# Begin Source File

SOURCE=.\Rfi.h
# End Source File
# Begin Source File

SOURCE=.\RfiDlg.h
# End Source File
# Begin Source File

SOURCE=.\Splash1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\reptr.ico
# End Source File
# Begin Source File

SOURCE=.\res\Rfi.ico
# End Source File
# Begin Source File

SOURCE=.\res\Rfi.rc2
# End Source File
# Begin Source File

SOURCE=.\res\rfiicon.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tray.ico
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Next Release.txt"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\This release.txt"
# End Source File
# End Group
# End Target
# End Project
# Section Rfi : {405404A1-38CC-11D1-914F-0060976CDDF4}
# 	2:19:CLASS: CListBoxCtrl:CListBoxCtrl
# 	2:10:lbctrl.cpp:lbctrl.cpp
# 	2:8:lbctrl.h:lbctrl.h
# 	2:19:Application Include:Rfi.h
# End Section
# Section Rfi : {405404A0-38CC-11D1-914F-0060976CDDF4}
# 	2:19:CLASS: CListBoxCtrl:CListBoxCtrl
# 	2:10:lbctrl.cpp:lbctrl.cpp
# 	2:8:lbctrl.h:lbctrl.h
# 	2:19:Application Include:Rfi.h
# End Section
