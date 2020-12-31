# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=CCtl - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CCtl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CCtl - Win32 Release" && "$(CFG)" != "CCtl - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CCtl.mak" CFG="CCtl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CCtl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CCtl - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "CCtl - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "CCtl - Win32 Release"

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

ALL : "$(OUTDIR)\CCtl.exe"

CLEAN : 
	-@erase "$(INTDIR)\CCtl.obj"
	-@erase "$(INTDIR)\CCtl.pch"
	-@erase "$(INTDIR)\CCtl.res"
	-@erase "$(INTDIR)\CCtlDlg.obj"
	-@erase "$(INTDIR)\CharEdit.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\CCtl.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CCtl.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/CCtl.pdb" /machine:I386 /out:"$(OUTDIR)/CCtl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CCtl.obj" \
	"$(INTDIR)\CCtl.res" \
	"$(INTDIR)\CCtlDlg.obj" \
	"$(INTDIR)\CharEdit.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CCtl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CCtl - Win32 Debug"

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

ALL : "$(OUTDIR)\CCtl.exe"

CLEAN : 
	-@erase "$(INTDIR)\CCtl.obj"
	-@erase "$(INTDIR)\CCtl.pch"
	-@erase "$(INTDIR)\CCtl.res"
	-@erase "$(INTDIR)\CCtlDlg.obj"
	-@erase "$(INTDIR)\CharEdit.obj"
	-@erase "$(INTDIR)\NumEdit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\CCtl.exe"
	-@erase "$(OUTDIR)\CCtl.ilk"
	-@erase "$(OUTDIR)\CCtl.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CCtl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CCtl.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CCtl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/CCtl.pdb" /debug /machine:I386 /out:"$(OUTDIR)/CCtl.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CCtl.obj" \
	"$(INTDIR)\CCtl.res" \
	"$(INTDIR)\CCtlDlg.obj" \
	"$(INTDIR)\CharEdit.obj" \
	"$(INTDIR)\NumEdit.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\CCtl.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CCtl - Win32 Release"
# Name "CCtl - Win32 Debug"

!IF  "$(CFG)" == "CCtl - Win32 Release"

!ELSEIF  "$(CFG)" == "CCtl - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CCtl.cpp
DEP_CPP_CCTL_=\
	".\CCtl.h"\
	".\CCtlDlg.h"\
	".\CharEdit.h"\
	".\NumEdit.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CCtl.obj" : $(SOURCE) $(DEP_CPP_CCTL_) "$(INTDIR)"\
 "$(INTDIR)\CCtl.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CCtlDlg.cpp
DEP_CPP_CCTLD=\
	".\CCtl.h"\
	".\CCtlDlg.h"\
	".\CharEdit.h"\
	".\NumEdit.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CCtlDlg.obj" : $(SOURCE) $(DEP_CPP_CCTLD) "$(INTDIR)"\
 "$(INTDIR)\CCtl.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CCtl - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCtl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CCtl - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CCtl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CCtl.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CCtl.rc
DEP_RSC_CCTL_R=\
	".\res\CCtl.ico"\
	".\res\CCtl.rc2"\
	

"$(INTDIR)\CCtl.res" : $(SOURCE) $(DEP_RSC_CCTL_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CharEdit.cpp
DEP_CPP_CHARE=\
	".\CCtl.h"\
	".\CharEdit.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CharEdit.obj" : $(SOURCE) $(DEP_CPP_CHARE) "$(INTDIR)"\
 "$(INTDIR)\CCtl.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NumEdit.cpp
DEP_CPP_NUMED=\
	".\CCtl.h"\
	".\NumEdit.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NumEdit.obj" : $(SOURCE) $(DEP_CPP_NUMED) "$(INTDIR)"\
 "$(INTDIR)\CCtl.pch"


# End Source File
# End Target
# End Project
################################################################################
