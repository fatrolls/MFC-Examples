# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DDESrv - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DDESrv - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DDESrv - Win32 Release" && "$(CFG)" != "DDESrv - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DDESrv.mak" CFG="DDESrv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DDESrv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DDESrv - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DDESrv - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DDESrv - Win32 Release"

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

ALL : "$(OUTDIR)\DDESrv.exe"

CLEAN : 
	-@erase "$(INTDIR)\Advise.obj"
	-@erase "$(INTDIR)\DDEDoc.obj"
	-@erase "$(INTDIR)\DDESrv.obj"
	-@erase "$(INTDIR)\DDESrv.pch"
	-@erase "$(INTDIR)\DDESrv.res"
	-@erase "$(INTDIR)\DDEView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\DDESrv.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDESrv.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DDESrv.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DDESrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/DDESrv.pdb" /machine:I386 /out:"$(OUTDIR)/DDESrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Advise.obj" \
	"$(INTDIR)\DDEDoc.obj" \
	"$(INTDIR)\DDESrv.obj" \
	"$(INTDIR)\DDESrv.res" \
	"$(INTDIR)\DDEView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DDESrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DDESrv - Win32 Debug"

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

ALL : "$(OUTDIR)\DDESrv.exe"

CLEAN : 
	-@erase "$(INTDIR)\Advise.obj"
	-@erase "$(INTDIR)\DDEDoc.obj"
	-@erase "$(INTDIR)\DDESrv.obj"
	-@erase "$(INTDIR)\DDESrv.pch"
	-@erase "$(INTDIR)\DDESrv.res"
	-@erase "$(INTDIR)\DDEView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\DDESrv.exe"
	-@erase "$(OUTDIR)\DDESrv.ilk"
	-@erase "$(OUTDIR)\DDESrv.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDESrv.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DDESrv.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DDESrv.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DDESrv.pdb" /debug /machine:I386 /out:"$(OUTDIR)/DDESrv.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Advise.obj" \
	"$(INTDIR)\DDEDoc.obj" \
	"$(INTDIR)\DDESrv.obj" \
	"$(INTDIR)\DDESrv.res" \
	"$(INTDIR)\DDEView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\DDESrv.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DDESrv - Win32 Release"
# Name "DDESrv - Win32 Debug"

!IF  "$(CFG)" == "DDESrv - Win32 Release"

!ELSEIF  "$(CFG)" == "DDESrv - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DDESrv.cpp
DEP_CPP_DDESR=\
	".\DDEDoc.h"\
	".\DDESrv.h"\
	".\DDEView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DDESrv.obj" : $(SOURCE) $(DEP_CPP_DDESR) "$(INTDIR)"\
 "$(INTDIR)\DDESrv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DDESrv - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDESrv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DDESrv.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DDESrv - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDESrv.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DDESrv.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Advise.h"\
	".\DDEDoc.h"\
	".\DDESrv.h"\
	".\DDEView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\DDESrv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDEDoc.cpp
DEP_CPP_DDEDO=\
	".\DDEDoc.h"\
	".\DDESrv.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DDEDoc.obj" : $(SOURCE) $(DEP_CPP_DDEDO) "$(INTDIR)"\
 "$(INTDIR)\DDESrv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDEView.cpp
DEP_CPP_DDEVI=\
	".\DDEDoc.h"\
	".\DDESrv.h"\
	".\DDEView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DDEView.obj" : $(SOURCE) $(DEP_CPP_DDEVI) "$(INTDIR)"\
 "$(INTDIR)\DDESrv.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DDESrv.rc
DEP_RSC_DDESRV=\
	".\res\DDEDoc.ico"\
	".\res\DDESrv.ico"\
	".\res\DDESrv.rc2"\
	

"$(INTDIR)\DDESrv.res" : $(SOURCE) $(DEP_RSC_DDESRV) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Advise.cpp
DEP_CPP_ADVIS=\
	".\Advise.h"\
	".\DDESrv.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Advise.obj" : $(SOURCE) $(DEP_CPP_ADVIS) "$(INTDIR)"\
 "$(INTDIR)\DDESrv.pch"


# End Source File
# End Target
# End Project
################################################################################
