# Microsoft Developer Studio Project File - Name="ex06b" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 50006
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ex06b - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ex06b.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ex06b.mak" CFG="ex06b - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ex06b - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ex06b - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ex06b - Win32 Release"

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
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ex06b - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
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

# Name "ex06b - Win32 Release"
# Name "ex06b - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ex06b.cpp
# End Source File
# Begin Source File

SOURCE=.\ex06b.rc

!IF  "$(CFG)" == "ex06b - Win32 Release"

!ELSEIF  "$(CFG)" == "ex06b - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ex06bDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ex06bDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ex06bView.cpp
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

SOURCE=.\ex06b.h
# End Source File
# Begin Source File

SOURCE=.\Ex06bDialog.h
# End Source File
# Begin Source File

SOURCE=.\ex06bDoc.h
# End Source File
# Begin Source File

SOURCE=.\ex06bView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
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

SOURCE=.\res\ex06b.ico
# End Source File
# Begin Source File

SOURCE=.\res\ex06b.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ex06bDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon0.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon7.ico
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
