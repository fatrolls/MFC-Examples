# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=winpe - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to winpe - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "winpe - Win32 Release" && "$(CFG)" != "winpe - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "winpe.mak" CFG="winpe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "winpe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "winpe - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "winpe - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "winpe - Win32 Release"

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

ALL : "$(OUTDIR)\winpe.exe"

CLEAN : 
	-@erase "$(INTDIR)\DebugDirView.obj"
	-@erase "$(INTDIR)\DumpXView.obj"
	-@erase "$(INTDIR)\ExportView.obj"
	-@erase "$(INTDIR)\HeaderView.obj"
	-@erase "$(INTDIR)\ImportView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ResourceSView.obj"
	-@erase "$(INTDIR)\SectionTblView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\winpe.obj"
	-@erase "$(INTDIR)\winpe.pch"
	-@erase "$(INTDIR)\winpe.res"
	-@erase "$(INTDIR)\winpeDoc.obj"
	-@erase "$(OUTDIR)\winpe.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/winpe.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/winpe.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/winpe.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/winpe.pdb" /machine:I386 /out:"$(OUTDIR)/winpe.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DebugDirView.obj" \
	"$(INTDIR)\DumpXView.obj" \
	"$(INTDIR)\ExportView.obj" \
	"$(INTDIR)\HeaderView.obj" \
	"$(INTDIR)\ImportView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ResourceSView.obj" \
	"$(INTDIR)\SectionTblView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\winpe.obj" \
	"$(INTDIR)\winpe.res" \
	"$(INTDIR)\winpeDoc.obj"

"$(OUTDIR)\winpe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "winpe - Win32 Debug"

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

ALL : "$(OUTDIR)\winpe.exe"

CLEAN : 
	-@erase "$(INTDIR)\DebugDirView.obj"
	-@erase "$(INTDIR)\DumpXView.obj"
	-@erase "$(INTDIR)\ExportView.obj"
	-@erase "$(INTDIR)\HeaderView.obj"
	-@erase "$(INTDIR)\ImportView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ResourceSView.obj"
	-@erase "$(INTDIR)\SectionTblView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\winpe.obj"
	-@erase "$(INTDIR)\winpe.pch"
	-@erase "$(INTDIR)\winpe.res"
	-@erase "$(INTDIR)\winpeDoc.obj"
	-@erase "$(OUTDIR)\winpe.exe"
	-@erase "$(OUTDIR)\winpe.ilk"
	-@erase "$(OUTDIR)\winpe.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/winpe.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/winpe.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/winpe.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/winpe.pdb" /debug /machine:I386 /out:"$(OUTDIR)/winpe.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DebugDirView.obj" \
	"$(INTDIR)\DumpXView.obj" \
	"$(INTDIR)\ExportView.obj" \
	"$(INTDIR)\HeaderView.obj" \
	"$(INTDIR)\ImportView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ResourceSView.obj" \
	"$(INTDIR)\SectionTblView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\winpe.obj" \
	"$(INTDIR)\winpe.res" \
	"$(INTDIR)\winpeDoc.obj"

"$(OUTDIR)\winpe.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "winpe - Win32 Release"
# Name "winpe - Win32 Debug"

!IF  "$(CFG)" == "winpe - Win32 Release"

!ELSEIF  "$(CFG)" == "winpe - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "winpe - Win32 Release"

!ELSEIF  "$(CFG)" == "winpe - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\winpe.cpp
DEP_CPP_WINPE=\
	".\dumpxview.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\winpe.obj" : $(SOURCE) $(DEP_CPP_WINPE) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "winpe - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/winpe.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\winpe.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "winpe - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/winpe.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\winpe.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\DebugDirView.h"\
	".\dumpxview.h"\
	".\ExportView.h"\
	".\HeaderView.h"\
	".\ImportView.h"\
	".\MainFrm.h"\
	".\resourcesview.h"\
	".\SectionTblView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\winpeDoc.cpp
DEP_CPP_WINPED=\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\winpeDoc.obj" : $(SOURCE) $(DEP_CPP_WINPED) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\winpe.rc
DEP_RSC_WINPE_=\
	".\res\Toolbar.bmp"\
	".\res\winpe.ico"\
	".\res\winpe.rc2"\
	".\res\winpeDoc.ico"\
	

"$(INTDIR)\winpe.res" : $(SOURCE) $(DEP_RSC_WINPE_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\HeaderView.cpp
DEP_CPP_HEADE=\
	".\HeaderView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\HeaderView.obj" : $(SOURCE) $(DEP_CPP_HEADE) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SectionTblView.cpp
DEP_CPP_SECTI=\
	".\SectionTblView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\SectionTblView.obj" : $(SOURCE) $(DEP_CPP_SECTI) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DebugDirView.cpp
DEP_CPP_DEBUG=\
	".\DebugDirView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\DebugDirView.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ResourceSView.cpp
DEP_CPP_RESOU=\
	".\resourcesview.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\ResourceSView.obj" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ExportView.cpp
DEP_CPP_EXPOR=\
	".\ExportView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\ExportView.obj" : $(SOURCE) $(DEP_CPP_EXPOR) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ImportView.cpp
DEP_CPP_IMPOR=\
	".\ImportView.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\ImportView.obj" : $(SOURCE) $(DEP_CPP_IMPOR) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DumpXView.cpp
DEP_CPP_DUMPX=\
	".\dumpxview.h"\
	".\StdAfx.h"\
	".\winpe.h"\
	".\winpeDoc.h"\
	

"$(INTDIR)\DumpXView.obj" : $(SOURCE) $(DEP_CPP_DUMPX) "$(INTDIR)"\
 "$(INTDIR)\winpe.pch"


# End Source File
# End Target
# End Project
################################################################################
