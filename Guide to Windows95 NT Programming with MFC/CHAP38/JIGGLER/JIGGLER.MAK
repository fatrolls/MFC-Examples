# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Jiggler - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Jiggler - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Jiggler - Win32 Release" && "$(CFG)" !=\
 "Jiggler - Win32 Debug" && "$(CFG)" != "Jiggler - Win32 Unicode Debug" &&\
 "$(CFG)" != "Jiggler - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Jiggler.mak" CFG="Jiggler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jiggler - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Jiggler - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Jiggler - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Jiggler - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Jiggler - Win32 Unicode Release"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Jiggler - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Jiggler.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Jiggler.obj"
	-@erase "$(INTDIR)\Jiggler.pch"
	-@erase "$(INTDIR)\Jiggler.res"
	-@erase "$(INTDIR)\Jiggler.tlb"
	-@erase "$(INTDIR)\JigglerC.obj"
	-@erase "$(INTDIR)\JigglerP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Jiggler.exp"
	-@erase "$(OUTDIR)\Jiggler.ilk"
	-@erase "$(OUTDIR)\Jiggler.lib"
	-@erase "$(OUTDIR)\Jiggler.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jiggler.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jiggler.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jiggler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /machine:I386
# SUBTRACT LINK32 /profile /debug
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Jiggler.pdb" /machine:I386 /def:".\Jiggler.def"\
 /out:"$(OUTDIR)/Jiggler.ocx" /implib:"$(OUTDIR)/Jiggler.lib" 
DEF_FILE= \
	".\Jiggler.def"
LINK32_OBJS= \
	"$(INTDIR)\Jiggler.obj" \
	"$(INTDIR)\Jiggler.res" \
	"$(INTDIR)\JigglerC.obj" \
	"$(INTDIR)\JigglerP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Jiggler.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\Jiggler.ocx
InputPath=.\Release\Jiggler.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Jiggler.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Jiggler.obj"
	-@erase "$(INTDIR)\Jiggler.pch"
	-@erase "$(INTDIR)\Jiggler.res"
	-@erase "$(INTDIR)\Jiggler.tlb"
	-@erase "$(INTDIR)\JigglerC.obj"
	-@erase "$(INTDIR)\JigglerP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Jiggler.exp"
	-@erase "$(OUTDIR)\Jiggler.ilk"
	-@erase "$(OUTDIR)\Jiggler.lib"
	-@erase "$(OUTDIR)\Jiggler.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jiggler.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jiggler.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jiggler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /profile /incremental:no /debug
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Jiggler.pdb" /machine:I386 /def:".\Jiggler.def"\
 /out:"$(OUTDIR)/Jiggler.ocx" /implib:"$(OUTDIR)/Jiggler.lib" 
DEF_FILE= \
	".\Jiggler.def"
LINK32_OBJS= \
	"$(INTDIR)\Jiggler.obj" \
	"$(INTDIR)\Jiggler.res" \
	"$(INTDIR)\JigglerC.obj" \
	"$(INTDIR)\JigglerP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Jiggler.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\Jiggler.ocx
InputPath=.\Debug\Jiggler.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Jiggler.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Jiggler.obj"
	-@erase "$(INTDIR)\Jiggler.pch"
	-@erase "$(INTDIR)\Jiggler.res"
	-@erase "$(INTDIR)\Jiggler.tlb"
	-@erase "$(INTDIR)\JigglerC.obj"
	-@erase "$(INTDIR)\JigglerP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Jiggler.exp"
	-@erase "$(OUTDIR)\Jiggler.ilk"
	-@erase "$(OUTDIR)\Jiggler.lib"
	-@erase "$(OUTDIR)\Jiggler.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Jiggler.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jiggler.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jiggler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /profile /incremental:no /debug
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Jiggler.pdb" /machine:I386 /def:".\Jiggler.def"\
 /out:"$(OUTDIR)/Jiggler.ocx" /implib:"$(OUTDIR)/Jiggler.lib" 
DEF_FILE= \
	".\Jiggler.def"
LINK32_OBJS= \
	"$(INTDIR)\Jiggler.obj" \
	"$(INTDIR)\Jiggler.res" \
	"$(INTDIR)\JigglerC.obj" \
	"$(INTDIR)\JigglerP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Jiggler.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\Jiggler.ocx
InputPath=.\DebugU\Jiggler.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\Jiggler.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Jiggler.obj"
	-@erase "$(INTDIR)\Jiggler.pch"
	-@erase "$(INTDIR)\Jiggler.res"
	-@erase "$(INTDIR)\Jiggler.tlb"
	-@erase "$(INTDIR)\JigglerC.obj"
	-@erase "$(INTDIR)\JigglerP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Jiggler.exp"
	-@erase "$(OUTDIR)\Jiggler.ilk"
	-@erase "$(OUTDIR)\Jiggler.lib"
	-@erase "$(OUTDIR)\Jiggler.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Jiggler.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Jiggler.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jiggler.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /machine:I386
# SUBTRACT LINK32 /profile /debug
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Jiggler.pdb" /machine:I386 /def:".\Jiggler.def"\
 /out:"$(OUTDIR)/Jiggler.ocx" /implib:"$(OUTDIR)/Jiggler.lib" 
DEF_FILE= \
	".\Jiggler.def"
LINK32_OBJS= \
	"$(INTDIR)\Jiggler.obj" \
	"$(INTDIR)\Jiggler.res" \
	"$(INTDIR)\JigglerC.obj" \
	"$(INTDIR)\JigglerP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Jiggler.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Jiggler.ocx
InputPath=.\ReleaseU\Jiggler.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Jiggler - Win32 Release"
# Name "Jiggler - Win32 Debug"
# Name "Jiggler - Win32 Unicode Debug"
# Name "Jiggler - Win32 Unicode Release"

!IF  "$(CFG)" == "Jiggler - Win32 Release"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Jiggler - Win32 Release"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Jiggler - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jiggler.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jiggler.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jiggler.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jiggler.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Jiggler.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jiggler.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/Jiggler.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jiggler.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jiggler.cpp
DEP_CPP_JIGGL=\
	".\Jiggler.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Jiggler - Win32 Release"


"$(INTDIR)\Jiggler.obj" : $(SOURCE) $(DEP_CPP_JIGGL) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"


"$(INTDIR)\Jiggler.obj" : $(SOURCE) $(DEP_CPP_JIGGL) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"


"$(INTDIR)\Jiggler.obj" : $(SOURCE) $(DEP_CPP_JIGGL) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"


"$(INTDIR)\Jiggler.obj" : $(SOURCE) $(DEP_CPP_JIGGL) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jiggler.def

!IF  "$(CFG)" == "Jiggler - Win32 Release"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jiggler.rc

!IF  "$(CFG)" == "Jiggler - Win32 Release"

DEP_RSC_JIGGLE=\
	".\Jiggler.ico"\
	".\JigglerC.bmp"\
	".\Release\Jiggler.tlb"\
	

"$(INTDIR)\Jiggler.res" : $(SOURCE) $(DEP_RSC_JIGGLE) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Jiggler.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"

DEP_RSC_JIGGLE=\
	".\Jiggler.ico"\
	".\JigglerC.bmp"\
	
NODEP_RSC_JIGGLE=\
	".\Debug\Jiggler.tlb"\
	

"$(INTDIR)\Jiggler.res" : $(SOURCE) $(DEP_RSC_JIGGLE) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Jiggler.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"

DEP_RSC_JIGGLE=\
	".\Jiggler.ico"\
	".\JigglerC.bmp"\
	
NODEP_RSC_JIGGLE=\
	".\DebugU\Jiggler.tlb"\
	

"$(INTDIR)\Jiggler.res" : $(SOURCE) $(DEP_RSC_JIGGLE) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Jiggler.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"

DEP_RSC_JIGGLE=\
	".\Jiggler.ico"\
	".\JigglerC.bmp"\
	
NODEP_RSC_JIGGLE=\
	".\ReleaseU\Jiggler.tlb"\
	

"$(INTDIR)\Jiggler.res" : $(SOURCE) $(DEP_RSC_JIGGLE) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Jiggler.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jiggler.odl

!IF  "$(CFG)" == "Jiggler - Win32 Release"


"$(OUTDIR)\Jiggler.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/Jiggler.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"


"$(OUTDIR)\Jiggler.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/Jiggler.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"


"$(OUTDIR)\Jiggler.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/Jiggler.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"


"$(OUTDIR)\Jiggler.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/Jiggler.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JigglerC.cpp
DEP_CPP_JIGGLER=\
	".\Jiggler.h"\
	".\JigglerC.h"\
	".\JigglerP.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\random.h"\
	

!IF  "$(CFG)" == "Jiggler - Win32 Release"


"$(INTDIR)\JigglerC.obj" : $(SOURCE) $(DEP_CPP_JIGGLER) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"


"$(INTDIR)\JigglerC.obj" : $(SOURCE) $(DEP_CPP_JIGGLER) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"


"$(INTDIR)\JigglerC.obj" : $(SOURCE) $(DEP_CPP_JIGGLER) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"


"$(INTDIR)\JigglerC.obj" : $(SOURCE) $(DEP_CPP_JIGGLER) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JigglerP.cpp
DEP_CPP_JIGGLERP=\
	".\Jiggler.h"\
	".\JigglerP.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Jiggler - Win32 Release"


"$(INTDIR)\JigglerP.obj" : $(SOURCE) $(DEP_CPP_JIGGLERP) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Debug"


"$(INTDIR)\JigglerP.obj" : $(SOURCE) $(DEP_CPP_JIGGLERP) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Debug"


"$(INTDIR)\JigglerP.obj" : $(SOURCE) $(DEP_CPP_JIGGLERP) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ELSEIF  "$(CFG)" == "Jiggler - Win32 Unicode Release"


"$(INTDIR)\JigglerP.obj" : $(SOURCE) $(DEP_CPP_JIGGLERP) "$(INTDIR)"\
 "$(INTDIR)\Jiggler.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
