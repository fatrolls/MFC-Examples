# Microsoft Developer Studio Project File - Name="Mrcext" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Mrcext - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mrcext4.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mrcext4.mak" CFG="Mrcext - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mrcext - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Mrcext - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Mrcext - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE F90 /I "WinDebug/"
# ADD F90 /I "WinDebug/"
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"mrcstafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"mrcstafx.h" /Fd".\Debug\mrcextx.pdb" /FD /c
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x0 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\inc" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /def:"mrcext.def" /implib:"mrcext.lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin\mrcex42d.dll" /implib:"..\bin\mrcext4d.lib" /libpath:"..\bin"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Mrcext - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE F90 /I "WinRel/"
# ADD F90 /I "WinRel/"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"mrcstafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"mrcstafx.h" /Fd".\Release\mrcextx.pdb" /FD /c
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x0 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\inc" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386 /def:"mrcext.def" /implib:"mrcext.lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\bin\Mrcex42.dll" /implib:"..\bin\mrcext4.lib" /libpath:"..\bin"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Mrcext - Win32 Debug"
# Name "Mrcext - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BMPBTN.CPP
# End Source File
# Begin Source File

SOURCE=.\cfgtbar.cpp
# End Source File
# Begin Source File

SOURCE=.\CLRLABEL.CPP
# End Source File
# Begin Source File

SOURCE=.\DIB.CPP
# End Source File
# Begin Source File

SOURCE=.\DRAGDOCK.CPP
# End Source File
# Begin Source File

SOURCE=.\FRAMEWND.CPP
# End Source File
# Begin Source File

SOURCE=.\mdifloat.cpp
# End Source File
# Begin Source File

SOURCE=.\MRCANIMA.CPP
# End Source File
# Begin Source File

SOURCE=.\MRCEXT.CPP
# End Source File
# Begin Source File

SOURCE=.\MRCEXT.RC
# End Source File
# Begin Source File

SOURCE=.\MRCSTAFX.CPP
# ADD BASE CPP /Yc"mrcstafx.h"
# ADD CPP /Yc"mrcstafx.h"
# End Source File
# Begin Source File

SOURCE=.\readme.txt
# End Source File
# Begin Source File

SOURCE=.\SIZECONT.CPP
# End Source File
# Begin Source File

SOURCE=.\SIZEDLG.CPP
# End Source File
# Begin Source File

SOURCE=.\SIZEDOCK.CPP
# End Source File
# Begin Source File

SOURCE=.\SZTOOLBA.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\cfgTbar.h
# End Source File
# Begin Source File

SOURCE=..\inc\mrcext.h
# End Source File
# Begin Source File

SOURCE=.\Mrcpriv.h
# End Source File
# Begin Source File

SOURCE=.\Mrcstafx.h
# End Source File
# Begin Source File

SOURCE=.\occimpl.h
# End Source File
# Begin Source File

SOURCE=.\ocdb.h
# End Source File
# Begin Source File

SOURCE=.\ocdbid.h
# End Source File
# Begin Source File

SOURCE=.\olebind.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MRCEXT.RC2
# End Source File
# End Group
# End Target
# End Project
