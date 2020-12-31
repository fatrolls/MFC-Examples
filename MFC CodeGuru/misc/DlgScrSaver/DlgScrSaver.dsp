# Microsoft Developer Studio Project File - Name="DlgScrSaver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DlgScrSaver - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DlgScrSaver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DlgScrSaver.mak" CFG="DlgScrSaver - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DlgScrSaver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DlgScrSaver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DlgScrSaver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"Stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:".\Release\DlgScrSaver.scr"

!ELSEIF  "$(CFG)" == "DlgScrSaver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"Stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\Debug\DlgScrSaver.scr"

!ENDIF 

# Begin Target

# Name "DlgScrSaver - Win32 Release"
# Name "DlgScrSaver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DlgScrSaver.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScrSaver.rc

!IF  "$(CFG)" == "DlgScrSaver - Win32 Release"

!ELSEIF  "$(CFG)" == "DlgScrSaver - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Drawwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\meta.cpp
# End Source File
# Begin Source File

SOURCE=.\Saverdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Saverwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp
# ADD CPP /Yc"Stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;inl;fi;fd"
# Begin Source File

SOURCE=.\CIMAGE.H
# End Source File
# Begin Source File

SOURCE=.\CIMAGEB.H
# End Source File
# Begin Source File

SOURCE=.\CMAP.H
# End Source File
# Begin Source File

SOURCE=.\Collect.h
# End Source File
# Begin Source File

SOURCE=.\DlgScrSaver.h
# End Source File
# Begin Source File

SOURCE=.\drawwnd.h
# End Source File
# Begin Source File

SOURCE=.\meta.h
# End Source File
# Begin Source File

SOURCE=.\Saverdlg.h
# End Source File
# Begin Source File

SOURCE=.\saverwnd.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\Datenverlust.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DlgScrSaver.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Falsch.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InternetExplorer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NoHelpID.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OleMainThreadWndName.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Pfad.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Saver.ico
# End Source File
# Begin Source File

SOURCE=.\res\saver.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Schwerwiegend.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Screen Saver.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Speed.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Standard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Winhelp.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CIMAGE.lib
# End Source File
# Begin Source File

SOURCE=.\JPEG.lib
# End Source File
# Begin Source File

SOURCE=.\PNG.lib
# End Source File
# Begin Source File

SOURCE=.\ZLIB.lib
# End Source File
# End Target
# End Project
