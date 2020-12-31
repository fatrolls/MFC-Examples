# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Spw - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Spw - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Spw - Win32 Release" && "$(CFG)" != "Spw - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Spw.mak" CFG="Spw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Spw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Spw - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Spw - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Spw - Win32 Release"

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

ALL : "$(OUTDIR)\Spw.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Spw.obj"
	-@erase "$(INTDIR)\Spw.pch"
	-@erase "$(INTDIR)\Spw.res"
	-@erase "$(INTDIR)\SpwDoc.obj"
	-@erase "$(INTDIR)\SpwEVw.obj"
	-@erase "$(INTDIR)\SpwFVw.obj"
	-@erase "$(INTDIR)\SpwView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Spw.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Spw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Spw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Spw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Spw.pdb" /machine:I386 /out:"$(OUTDIR)/Spw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Spw.obj" \
	"$(INTDIR)\Spw.res" \
	"$(INTDIR)\SpwDoc.obj" \
	"$(INTDIR)\SpwEVw.obj" \
	"$(INTDIR)\SpwFVw.obj" \
	"$(INTDIR)\SpwView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Spw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Spw - Win32 Debug"

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

ALL : "$(OUTDIR)\Spw.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Spw.obj"
	-@erase "$(INTDIR)\Spw.pch"
	-@erase "$(INTDIR)\Spw.res"
	-@erase "$(INTDIR)\SpwDoc.obj"
	-@erase "$(INTDIR)\SpwEVw.obj"
	-@erase "$(INTDIR)\SpwFVw.obj"
	-@erase "$(INTDIR)\SpwView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Spw.exe"
	-@erase "$(OUTDIR)\Spw.ilk"
	-@erase "$(OUTDIR)\Spw.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Spw.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Spw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Spw.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Spw.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Spw.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Spw.obj" \
	"$(INTDIR)\Spw.res" \
	"$(INTDIR)\SpwDoc.obj" \
	"$(INTDIR)\SpwEVw.obj" \
	"$(INTDIR)\SpwFVw.obj" \
	"$(INTDIR)\SpwView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Spw.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Spw - Win32 Release"
# Name "Spw - Win32 Debug"

!IF  "$(CFG)" == "Spw - Win32 Release"

!ELSEIF  "$(CFG)" == "Spw - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Spw.cpp
DEP_CPP_SPW_C=\
	".\MainFrm.h"\
	".\Spw.h"\
	".\SpwDoc.h"\
	".\SpwView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Spw.obj" : $(SOURCE) $(DEP_CPP_SPW_C) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Spw - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Spw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Spw.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Spw - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Spw.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Spw.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Spw.h"\
	".\SpwDoc.h"\
	".\SPwEVw.h"\
	".\SPwFVw.h"\
	".\SpwView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpwDoc.cpp
DEP_CPP_SPWDO=\
	".\Spw.h"\
	".\SpwDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SpwDoc.obj" : $(SOURCE) $(DEP_CPP_SPWDO) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpwView.cpp
DEP_CPP_SPWVI=\
	".\Spw.h"\
	".\SpwDoc.h"\
	".\SpwView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SpwView.obj" : $(SOURCE) $(DEP_CPP_SPWVI) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Spw.rc
DEP_RSC_SPW_R=\
	".\res\Spw.ico"\
	".\res\Spw.rc2"\
	".\res\SpwDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Spw.res" : $(SOURCE) $(DEP_RSC_SPW_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpwEVw.cpp
DEP_CPP_SPWEV=\
	".\Spw.h"\
	".\SPwEVw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SpwEVw.obj" : $(SOURCE) $(DEP_CPP_SPWEV) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpwFVw.cpp
DEP_CPP_SPWFV=\
	".\Spw.h"\
	".\SPwFVw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SpwFVw.obj" : $(SOURCE) $(DEP_CPP_SPWFV) "$(INTDIR)"\
 "$(INTDIR)\Spw.pch"


# End Source File
# End Target
# End Project
################################################################################
