# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Panel3d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Panel3d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Panel3d - Win32 Release" && "$(CFG)" !=\
 "Panel3d - Win32 Debug" && "$(CFG)" != "Panel3d - Win32 Unicode Debug" &&\
 "$(CFG)" != "Panel3d - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Panel3d.mak" CFG="Panel3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Panel3d - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Panel3d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Panel3d - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Panel3d - Win32 Unicode Release" (based on\
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
# PROP Target_Last_Scanned "Panel3d - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Panel3d - Win32 Release"

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

ALL : "$(OUTDIR)\Panel3d.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Panel3d.obj"
	-@erase "$(INTDIR)\Panel3d.pch"
	-@erase "$(INTDIR)\Panel3d.res"
	-@erase "$(INTDIR)\Panel3d.tlb"
	-@erase "$(INTDIR)\Panel3dC.obj"
	-@erase "$(INTDIR)\Panel3dP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Panel3d.exp"
	-@erase "$(OUTDIR)\Panel3d.lib"
	-@erase "$(OUTDIR)\Panel3d.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Panel3d.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Panel3d.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Panel3d.pdb" /machine:I386 /def:".\Panel3d.def"\
 /out:"$(OUTDIR)/Panel3d.ocx" /implib:"$(OUTDIR)/Panel3d.lib" 
DEF_FILE= \
	".\Panel3d.def"
LINK32_OBJS= \
	"$(INTDIR)\Panel3d.obj" \
	"$(INTDIR)\Panel3d.res" \
	"$(INTDIR)\Panel3dC.obj" \
	"$(INTDIR)\Panel3dP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Panel3d.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\Panel3d.ocx
InputPath=.\Release\Panel3d.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"

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

ALL : "$(OUTDIR)\Panel3d.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Panel3d.obj"
	-@erase "$(INTDIR)\Panel3d.pch"
	-@erase "$(INTDIR)\Panel3d.res"
	-@erase "$(INTDIR)\Panel3d.tlb"
	-@erase "$(INTDIR)\Panel3dC.obj"
	-@erase "$(INTDIR)\Panel3dP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Panel3d.exp"
	-@erase "$(OUTDIR)\Panel3d.ilk"
	-@erase "$(OUTDIR)\Panel3d.lib"
	-@erase "$(OUTDIR)\Panel3d.ocx"
	-@erase "$(OUTDIR)\Panel3d.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Panel3d.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Panel3d.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Panel3d.pdb" /debug /machine:I386 /def:".\Panel3d.def"\
 /out:"$(OUTDIR)/Panel3d.ocx" /implib:"$(OUTDIR)/Panel3d.lib" 
DEF_FILE= \
	".\Panel3d.def"
LINK32_OBJS= \
	"$(INTDIR)\Panel3d.obj" \
	"$(INTDIR)\Panel3d.res" \
	"$(INTDIR)\Panel3dC.obj" \
	"$(INTDIR)\Panel3dP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Panel3d.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\Panel3d.ocx
InputPath=.\Debug\Panel3d.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"

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

ALL : "$(OUTDIR)\Panel3d.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Panel3d.obj"
	-@erase "$(INTDIR)\Panel3d.pch"
	-@erase "$(INTDIR)\Panel3d.res"
	-@erase "$(INTDIR)\Panel3d.tlb"
	-@erase "$(INTDIR)\Panel3dC.obj"
	-@erase "$(INTDIR)\Panel3dP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Panel3d.exp"
	-@erase "$(OUTDIR)\Panel3d.ilk"
	-@erase "$(OUTDIR)\Panel3d.lib"
	-@erase "$(OUTDIR)\Panel3d.ocx"
	-@erase "$(OUTDIR)\Panel3d.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Panel3d.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Panel3d.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Panel3d.pdb" /debug /machine:I386 /def:".\Panel3d.def"\
 /out:"$(OUTDIR)/Panel3d.ocx" /implib:"$(OUTDIR)/Panel3d.lib" 
DEF_FILE= \
	".\Panel3d.def"
LINK32_OBJS= \
	"$(INTDIR)\Panel3d.obj" \
	"$(INTDIR)\Panel3d.res" \
	"$(INTDIR)\Panel3dC.obj" \
	"$(INTDIR)\Panel3dP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Panel3d.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\Panel3d.ocx
InputPath=.\DebugU\Panel3d.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"

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

ALL : "$(OUTDIR)\Panel3d.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\Panel3d.obj"
	-@erase "$(INTDIR)\Panel3d.pch"
	-@erase "$(INTDIR)\Panel3d.res"
	-@erase "$(INTDIR)\Panel3d.tlb"
	-@erase "$(INTDIR)\Panel3dC.obj"
	-@erase "$(INTDIR)\Panel3dP.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Panel3d.exp"
	-@erase "$(OUTDIR)\Panel3d.lib"
	-@erase "$(OUTDIR)\Panel3d.ocx"
	-@erase "$(OUTDIR)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Panel3d.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Panel3d.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Panel3d.pdb" /machine:I386 /def:".\Panel3d.def"\
 /out:"$(OUTDIR)/Panel3d.ocx" /implib:"$(OUTDIR)/Panel3d.lib" 
DEF_FILE= \
	".\Panel3d.def"
LINK32_OBJS= \
	"$(INTDIR)\Panel3d.obj" \
	"$(INTDIR)\Panel3d.res" \
	"$(INTDIR)\Panel3dC.obj" \
	"$(INTDIR)\Panel3dP.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Panel3d.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Panel3d.ocx
InputPath=.\ReleaseU\Panel3d.ocx
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

# Name "Panel3d - Win32 Release"
# Name "Panel3d - Win32 Debug"
# Name "Panel3d - Win32 Unicode Debug"
# Name "Panel3d - Win32 Unicode Release"

!IF  "$(CFG)" == "Panel3d - Win32 Release"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Panel3d - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Panel3d.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Panel3d.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Panel3d.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/Panel3d.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Panel3d.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3d.cpp
DEP_CPP_PANEL=\
	".\Panel3d.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Panel3d - Win32 Release"


"$(INTDIR)\Panel3d.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"


"$(INTDIR)\Panel3d.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"


"$(INTDIR)\Panel3d.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"


"$(INTDIR)\Panel3d.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3d.rc

!IF  "$(CFG)" == "Panel3d - Win32 Release"

DEP_RSC_PANEL3=\
	".\Panel3d.ico"\
	".\Panel3dc.bmp"\
	
NODEP_RSC_PANEL3=\
	".\Release\Panel3d.tlb"\
	

"$(INTDIR)\Panel3d.res" : $(SOURCE) $(DEP_RSC_PANEL3) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Panel3d.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"

DEP_RSC_PANEL3=\
	".\Panel3d.ico"\
	".\Panel3dc.bmp"\
	
NODEP_RSC_PANEL3=\
	".\Debug\Panel3d.tlb"\
	

"$(INTDIR)\Panel3d.res" : $(SOURCE) $(DEP_RSC_PANEL3) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Panel3d.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"

DEP_RSC_PANEL3=\
	".\Panel3d.ico"\
	".\Panel3dc.bmp"\
	
NODEP_RSC_PANEL3=\
	".\DebugU\Panel3d.tlb"\
	

"$(INTDIR)\Panel3d.res" : $(SOURCE) $(DEP_RSC_PANEL3) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Panel3d.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"

DEP_RSC_PANEL3=\
	".\Panel3d.ico"\
	".\Panel3dc.bmp"\
	
NODEP_RSC_PANEL3=\
	".\ReleaseU\Panel3d.tlb"\
	

"$(INTDIR)\Panel3d.res" : $(SOURCE) $(DEP_RSC_PANEL3) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/Panel3d.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3dC.cpp
DEP_CPP_PANEL3D=\
	".\Panel3d.h"\
	".\Panel3dC.h"\
	".\Panel3dP.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\colors.h"\
	

!IF  "$(CFG)" == "Panel3d - Win32 Release"


"$(INTDIR)\Panel3dC.obj" : $(SOURCE) $(DEP_CPP_PANEL3D) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"


"$(INTDIR)\Panel3dC.obj" : $(SOURCE) $(DEP_CPP_PANEL3D) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"


"$(INTDIR)\Panel3dC.obj" : $(SOURCE) $(DEP_CPP_PANEL3D) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"


"$(INTDIR)\Panel3dC.obj" : $(SOURCE) $(DEP_CPP_PANEL3D) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3dP.cpp
DEP_CPP_PANEL3DP=\
	".\Panel3d.h"\
	".\Panel3dC.h"\
	".\Panel3dP.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Panel3d - Win32 Release"


"$(INTDIR)\Panel3dP.obj" : $(SOURCE) $(DEP_CPP_PANEL3DP) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"


"$(INTDIR)\Panel3dP.obj" : $(SOURCE) $(DEP_CPP_PANEL3DP) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"


"$(INTDIR)\Panel3dP.obj" : $(SOURCE) $(DEP_CPP_PANEL3DP) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"


"$(INTDIR)\Panel3dP.obj" : $(SOURCE) $(DEP_CPP_PANEL3DP) "$(INTDIR)"\
 "$(INTDIR)\Panel3d.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3d.odl

!IF  "$(CFG)" == "Panel3d - Win32 Release"


"$(OUTDIR)\Panel3d.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/Panel3d.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"


"$(OUTDIR)\Panel3d.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/Panel3d.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"


"$(OUTDIR)\Panel3d.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/Panel3d.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"


"$(OUTDIR)\Panel3d.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/Panel3d.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Panel3d.def

!IF  "$(CFG)" == "Panel3d - Win32 Release"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Debug"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Panel3d - Win32 Unicode Release"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
