# Microsoft Developer Studio Project File - Name="wdmstub" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=wdmstub - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Wdmstub.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wdmstub.mak" CFG="wdmstub - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wdmstub - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "wdmstub - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wdmstub - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WDMSTUB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gz /MLd /W3 /Zi /Od /I "." /I "$(DDKPATH)\inc" /I "$(98DDK)\inc\win98" /I "$(DDKPATH)\inc\ddk" /D "_X86_" /D "BLD_COFF" /D "IS_32" /D "DEBUG" /D DEBLEVEL=1 /FR /Fp"Debug/vxd.pch" /Yu"stdvxd.h" /Fo"Debug/" /Fd"Debug/vxd.pdb" -Gs -Zpl /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 vxdwraps.clb wdmvxd.clb /nologo /machine:I386 /nodefaultlib /out:"Release/wdmstub.vxd" /libpath:"$(98DDK)\lib\i386\free" -vxd -ignore:4078 -ignore:4039
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
IntDir=.\Release
TargetPath=.\Release\wdmstub.vxd
SOURCE="$(InputPath)"
PostBuild_Desc=Finishing...
PostBuild_Cmds=$(98DDK)\bin\win98\bin16\rc -r -Fo$(IntDir)\version.res version.rc	$(98DDK)\bin\win98\adrc2vxd $(TargetPath) $(IntDir)\version.res 	$(SIWPATH)\nmsym -translate:source,package,always $(TargetPath)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "wdmstub - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WDMSTUB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /W3 /Zi /Od /I "." /I "$(DDKPATH)\inc" /I "$(98DDK)\inc\win98" /I "$(DDKPATH)\inc\ddk" /D "_X86_" /D "BLD_COFF" /D "IS_32" /D "DEBUG" /D DEBLEVEL=1 /FR /Fp"Debug/vxd.pch" /Yu"stdvxd.h" /Fd"Debug/vxd.pdb" -Gs -Zpl /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vxdwraps.clb wdmvxd.clb /nologo /incremental:no /map /debug /machine:I386 /nodefaultlib /out:"Debug/wdmstub.vxd" /pdbtype:sept /libpath:"$(98DDK)\lib\i386\free" -vxd -vxd -ignore:4078 -ignore:4039
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
IntDir=.\Debug
TargetPath=.\Debug\wdmstub.vxd
SOURCE="$(InputPath)"
PostBuild_Desc=Finishing...
PostBuild_Cmds=$(98DDK)\bin\win98\bin16\rc -r -Fo$(IntDir)\version.res version.rc	$(98DDK)\bin\win98\adrc2vxd $(TargetPath) $(IntDir)\version.res 	$(SIWPATH)\nmsym -translate:source,package,always $(TargetPath)	copy $(TargetPath) $(WINDIR)\system
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "wdmstub - Win32 Release"
# Name "wdmstub - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\NonStubs.cpp
DEP_CPP_NONST=\
	".\NonStubs.h"\
	"e:\nt5ddk\inc\alpharef.h"\
	"e:\nt5ddk\inc\basetsd.h"\
	"e:\nt5ddk\inc\bugcodes.h"\
	"e:\nt5ddk\inc\ddk\ntddk.h"\
	"e:\nt5ddk\inc\guiddef.h"\
	"e:\nt5ddk\inc\ia64reg.h"\
	"e:\nt5ddk\inc\ntdef.h"\
	"e:\nt5ddk\inc\ntiologc.h"\
	"e:\nt5ddk\inc\ntstatus.h"\
	

!IF  "$(CFG)" == "wdmstub - Win32 Release"

# ADD CPP /D DBG=0
# SUBTRACT CPP /D "DEBUG" /D DEBLEVEL=1 /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "wdmstub - Win32 Debug"

# ADD CPP /D DBG=1
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Stdvxd.cpp
DEP_CPP_STDVX=\
	".\Stdvxd.h"\
	"e:\98ddk\inc\win98\basedef.h"\
	"e:\98ddk\inc\win98\configmg.h"\
	"e:\98ddk\inc\win98\debug.h"\
	"e:\98ddk\inc\win98\regdef.h"\
	"e:\98ddk\inc\win98\shell.h"\
	"e:\98ddk\inc\win98\vmm.h"\
	"e:\98ddk\inc\win98\vmmreg.h"\
	"e:\98ddk\inc\win98\vtd.h"\
	"e:\98ddk\inc\win98\vwin32.h"\
	"e:\98ddk\inc\win98\vxdldr.h"\
	"e:\98ddk\inc\win98\vxdwraps.h"\
	"e:\nt5ddk\inc\alpharef.h"\
	"e:\nt5ddk\inc\basetsd.h"\
	"e:\nt5ddk\inc\bugcodes.h"\
	"e:\nt5ddk\inc\ddk\ntddk.h"\
	"e:\nt5ddk\inc\guiddef.h"\
	"e:\nt5ddk\inc\ia64reg.h"\
	"e:\nt5ddk\inc\ntdef.h"\
	"e:\nt5ddk\inc\ntiologc.h"\
	"e:\nt5ddk\inc\ntstatus.h"\
	
# ADD CPP /Yc"stdvxd.h"
# End Source File
# Begin Source File

SOURCE=.\version.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\WdmStub.cpp
DEP_CPP_WDMST=\
	".\NonStubs.h"\
	".\Stdvxd.h"\
	"e:\98ddk\inc\win98\basedef.h"\
	"e:\98ddk\inc\win98\configmg.h"\
	"e:\98ddk\inc\win98\debug.h"\
	"e:\98ddk\inc\win98\regdef.h"\
	"e:\98ddk\inc\win98\shell.h"\
	"e:\98ddk\inc\win98\vmm.h"\
	"e:\98ddk\inc\win98\vmmreg.h"\
	"e:\98ddk\inc\win98\vtd.h"\
	"e:\98ddk\inc\win98\vwin32.h"\
	"e:\98ddk\inc\win98\vxdldr.h"\
	"e:\98ddk\inc\win98\vxdwraps.h"\
	"e:\nt5ddk\inc\alpharef.h"\
	"e:\nt5ddk\inc\basetsd.h"\
	"e:\nt5ddk\inc\bugcodes.h"\
	"e:\nt5ddk\inc\ddk\ntddk.h"\
	"e:\nt5ddk\inc\guiddef.h"\
	"e:\nt5ddk\inc\ia64reg.h"\
	"e:\nt5ddk\inc\ntdef.h"\
	"e:\nt5ddk\inc\ntiologc.h"\
	"e:\nt5ddk\inc\ntstatus.h"\
	
# End Source File
# Begin Source File

SOURCE=.\wdmstub.def
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\NonStubs.h
# End Source File
# Begin Source File

SOURCE=.\Stdvxd.h
# End Source File
# Begin Source File

SOURCE=.\Version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\DevCtrl.asm

!IF  "$(CFG)" == "wdmstub - Win32 Release"

# Begin Custom Build - Assembling...
IntDir=.\Release
InputPath=.\DevCtrl.asm
InputName=DevCtrl

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(98DDK)\bin\win98\ml -c -coff -DBLD_COFF -DIS_32 -DMASM6 -W2 -Cx -Fo$(IntDir)\$(InputName).obj -Zi  -I$(98DDK)\inc\win98 $(InputPath) 
	editbin $(IntDir)\$(InputName).obj -section:_EBSS=.bss$1 -section:_INIT=.CRT$XCA -section:_EINIT=.CRT$XCZ 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "wdmstub - Win32 Debug"

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
# Begin Source File

SOURCE=.\Version.inc
# End Source File
# End Target
# End Project
