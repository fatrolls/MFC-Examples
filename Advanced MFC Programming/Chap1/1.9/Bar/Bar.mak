# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Bar - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Bar - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Bar - Win32 Release" && "$(CFG)" != "Bar - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Bar.mak" CFG="Bar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Bar - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Bar - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Bar - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Bar.exe"

CLEAN : 
	-@erase "$(INTDIR)\Bar.obj"
	-@erase "$(INTDIR)\Bar.pch"
	-@erase "$(INTDIR)\Bar.res"
	-@erase "$(INTDIR)\BarDoc.obj"
	-@erase "$(INTDIR)\BarView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MDlgBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Bar.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Bar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Bar.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Bar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Bar.pdb" /machine:I386 /out:"$(OUTDIR)/Bar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Bar.obj" \
	"$(INTDIR)\Bar.res" \
	"$(INTDIR)\BarDoc.obj" \
	"$(INTDIR)\BarView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MDlgBar.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Bar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Bar - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Bar.exe"

CLEAN : 
	-@erase "$(INTDIR)\Bar.obj"
	-@erase "$(INTDIR)\Bar.pch"
	-@erase "$(INTDIR)\Bar.res"
	-@erase "$(INTDIR)\BarDoc.obj"
	-@erase "$(INTDIR)\BarView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MDlgBar.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Bar.exe"
	-@erase "$(OUTDIR)\Bar.ilk"
	-@erase "$(OUTDIR)\Bar.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Bar.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Bar.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Bar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Bar.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Bar.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Bar.obj" \
	"$(INTDIR)\Bar.res" \
	"$(INTDIR)\BarDoc.obj" \
	"$(INTDIR)\BarView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MDlgBar.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Bar.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

# Name "Bar - Win32 Release"
# Name "Bar - Win32 Debug"

!IF  "$(CFG)" == "Bar - Win32 Release"

!ELSEIF  "$(CFG)" == "Bar - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Bar.cpp
DEP_CPP_BAR_C=\
	".\Bar.h"\
	".\BarDoc.h"\
	".\BarView.h"\
	".\MainFrm.h"\
	".\MDlgBar.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Bar.obj" : $(SOURCE) $(DEP_CPP_BAR_C) "$(INTDIR)"\
 "$(INTDIR)\Bar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Bar - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Bar.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bar.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Bar - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Bar.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Bar.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Bar.h"\
	".\MainFrm.h"\
	".\MDlgBar.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Bar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BarDoc.cpp
DEP_CPP_BARDO=\
	".\Bar.h"\
	".\BarDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BarDoc.obj" : $(SOURCE) $(DEP_CPP_BARDO) "$(INTDIR)"\
 "$(INTDIR)\Bar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BarView.cpp
DEP_CPP_BARVI=\
	".\Bar.h"\
	".\BarDoc.h"\
	".\BarView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\BarView.obj" : $(SOURCE) $(DEP_CPP_BARVI) "$(INTDIR)"\
 "$(INTDIR)\Bar.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bar.rc
DEP_RSC_BAR_R=\
	".\res\Bar.ico"\
	".\res\Bar.rc2"\
	".\res\BarDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Bar.res" : $(SOURCE) $(DEP_RSC_BAR_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDlgBar.cpp
DEP_CPP_MDLGB=\
	".\Bar.h"\
	".\MainFrm.h"\
	".\MDlgBar.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MDlgBar.obj" : $(SOURCE) $(DEP_CPP_MDLGB) "$(INTDIR)"\
 "$(INTDIR)\Bar.pch"


# End Source File
# End Target
# End Project
################################################################################
