# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=NotePad - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to NotePad - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NotePad - Win32 Release" && "$(CFG)" !=\
 "NotePad - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "NotePad.mak" CFG="NotePad - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NotePad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NotePad - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "NotePad - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "NotePad - Win32 Release"

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

ALL : "$(OUTDIR)\NotePad.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NotePad.obj"
	-@erase "$(INTDIR)\NotePad.pch"
	-@erase "$(INTDIR)\NotePad.res"
	-@erase "$(INTDIR)\NPDoc.obj"
	-@erase "$(INTDIR)\NPView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\NotePad.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/NotePad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NotePad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NotePad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/NotePad.pdb" /machine:I386 /out:"$(OUTDIR)/NotePad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NotePad.obj" \
	"$(INTDIR)\NotePad.res" \
	"$(INTDIR)\NPDoc.obj" \
	"$(INTDIR)\NPView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\NotePad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

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

ALL : "$(OUTDIR)\NotePad.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\NotePad.obj"
	-@erase "$(INTDIR)\NotePad.pch"
	-@erase "$(INTDIR)\NotePad.res"
	-@erase "$(INTDIR)\NPDoc.obj"
	-@erase "$(INTDIR)\NPView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\NotePad.exe"
	-@erase "$(OUTDIR)\NotePad.ilk"
	-@erase "$(OUTDIR)\NotePad.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/NotePad.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/NotePad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NotePad.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/NotePad.pdb" /debug /machine:I386 /out:"$(OUTDIR)/NotePad.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\NotePad.obj" \
	"$(INTDIR)\NotePad.res" \
	"$(INTDIR)\NPDoc.obj" \
	"$(INTDIR)\NPView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\NotePad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "NotePad - Win32 Release"
# Name "NotePad - Win32 Debug"

!IF  "$(CFG)" == "NotePad - Win32 Release"

!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\NotePad.cpp

!IF  "$(CFG)" == "NotePad - Win32 Release"

DEP_CPP_NOTEP=\
	".\MainFrm.h"\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\NPView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NotePad.obj" : $(SOURCE) $(DEP_CPP_NOTEP) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

DEP_CPP_NOTEP=\
	".\MainFrm.h"\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\NPView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NotePad.obj" : $(SOURCE) $(DEP_CPP_NOTEP) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "NotePad - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/NotePad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NotePad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/NotePad.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\NotePad.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "NotePad - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NPDoc.cpp

!IF  "$(CFG)" == "NotePad - Win32 Release"

DEP_CPP_NPDOC=\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NPDoc.obj" : $(SOURCE) $(DEP_CPP_NPDOC) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

DEP_CPP_NPDOC=\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NPDoc.obj" : $(SOURCE) $(DEP_CPP_NPDOC) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NPView.cpp

!IF  "$(CFG)" == "NotePad - Win32 Release"

DEP_CPP_NPVIE=\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\NPView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NPView.obj" : $(SOURCE) $(DEP_CPP_NPVIE) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ELSEIF  "$(CFG)" == "NotePad - Win32 Debug"

DEP_CPP_NPVIE=\
	".\NotePad.h"\
	".\NPDoc.h"\
	".\NPView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NPView.obj" : $(SOURCE) $(DEP_CPP_NPVIE) "$(INTDIR)"\
 "$(INTDIR)\NotePad.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NotePad.rc
DEP_RSC_NOTEPA=\
	".\res\NotePad.ico"\
	".\res\NotePad.rc2"\
	".\res\NPDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\NotePad.res" : $(SOURCE) $(DEP_RSC_NOTEPA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
