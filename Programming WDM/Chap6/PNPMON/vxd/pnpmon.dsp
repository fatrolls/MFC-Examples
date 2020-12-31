# Microsoft Developer Studio Project File - Name="pnpmon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=pnpmon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pnpmon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pnpmon.mak" CFG="pnpmon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pnpmon - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pnpmon - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pnpmon - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PNPMON_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gz /MLd /W3 /Zi /Ox /I "." /I "$(98DDK)\inc\win98" /D "_X86_" /D "DBLD_COFF" /D "IS_32" /FR /Yu"stdvxd.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 vxdwraps.clb wdmvxd.clb /nologo /dll /debug /machine:I386 /nodefaultlib /out:"Release/pnpmon.vxd" /pdbtype:sept /libpath:"$(98DDK)\lib\i386\free" -vxd -ignore:4078 -ignore:4039
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Release\pnpmon.vxd
SOURCE="$(InputPath)"
PostBuild_Cmds=$(SIWPATH)\nmsym -translate:source,package,always $(TargetPath)	copy $(TargetPath) $(WINDIR)\system
# End Special Build Tool

!ELSEIF  "$(CFG)" == "pnpmon - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PNPMON_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /W3 /Zi /Od /I "." /I "$(98DDK)\inc\win98" /D "_X86_" /D "DBLD_COFF" /D "IS_32" /D "DEBUG" /D DEBLEVEL=1 /FR /Yu"stdvxd.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vxdwraps.clb wdmvxd.clb /nologo /dll /incremental:no /debug /machine:I386 /nodefaultlib /out:"Debug/pnpmon.vxd" /pdbtype:sept /libpath:"$(98DDK)\lib\i386\free" -vxd -ignore:4078 -ignore:4039
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetPath=.\Debug\pnpmon.vxd
SOURCE="$(InputPath)"
PostBuild_Cmds=$(SIWPATH)\nmsym -translate:source,package,always $(TargetPath)	copy $(TargetPath) $(WINDIR)\system
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "pnpmon - Win32 Release"
# Name "pnpmon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\pnpmon.cpp
# End Source File
# Begin Source File

SOURCE=.\pnpmon.def
# End Source File
# Begin Source File

SOURCE=.\stdvxd.cpp
# ADD CPP /Gz /Yc"stdvxd.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Stdvxd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\DevCtrl.asm

!IF  "$(CFG)" == "pnpmon - Win32 Release"

# Begin Custom Build - Assembling...
IntDir=.\Release
InputPath=.\DevCtrl.asm
InputName=DevCtrl

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(98DDK)\bin\win98\ml -c -coff -DBLD_COFF -DIS_32 -DMASM6 -W2 -Cx -Fo$(IntDir)\$(InputName).obj -Zi -DDEBUG -DDEBLEVEL=1 -I$(98DDK)\inc\win98 $(InputPath) 
	editbin $(IntDir)\$(InputName).obj -section:_EBSS=.bss$1 -section:_INIT=.CRT$XCA -section:_EINIT=.CRT$XCZ 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "pnpmon - Win32 Debug"

# Begin Custom Build - Assembling...
IntDir=.\Debug
InputPath=.\DevCtrl.asm
InputName=DevCtrl

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(98DDK)\bin\win98\ml -c -coff -DBLD_COFF -DIS_32 -DMASM6 -W2 -Cx -Fo$(IntDir)\$(InputName).obj -Zi -DDEBUG -DDEBLEVEL=1 -I$(98DDK)\inc\win98 $(InputPath) 
	editbin $(IntDir)\$(InputName).obj -section:_EBSS=.bss$1 -section:_INIT=.CRT$XCA -section:_EINIT=.CRT$XCZ 
	
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
