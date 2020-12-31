# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Graph - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Graph - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Graph - Win32 Release" && "$(CFG)" != "Graph - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Graph.mak" CFG="Graph - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Graph - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Graph - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Graph - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Graph - Win32 Release"

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

ALL : "$(OUTDIR)\Graph.exe"

CLEAN : 
	-@erase ".\Release\Graph.exe"
	-@erase ".\Release\Graph.obj"
	-@erase ".\Release\Graph.pch"
	-@erase ".\Release\TextView.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\BarView.obj"
	-@erase ".\Release\GraphView.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\GraphDoc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Graph.res"
	-@erase ".\Release\NewDoc.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Graph.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x404 /fo"$(INTDIR)/Graph.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Graph.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Graph.pdb" /machine:I386 /out:"$(OUTDIR)/Graph.exe" 
LINK32_OBJS= \
	".\Release\Graph.obj" \
	".\Release\TextView.obj" \
	".\Release\MainFrm.obj" \
	".\Release\BarView.obj" \
	".\Release\GraphView.obj" \
	".\Release\ChildFrm.obj" \
	".\Release\GraphDoc.obj" \
	".\Release\StdAfx.obj" \
	".\Release\NewDoc.obj" \
	".\Release\Graph.res"

"$(OUTDIR)\Graph.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Graph - Win32 Debug"

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

ALL : "$(OUTDIR)\Graph.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Graph.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Graph.exe"
	-@erase ".\Debug\TextView.obj"
	-@erase ".\Debug\Graph.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\GraphView.obj"
	-@erase ".\Debug\BarView.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\GraphDoc.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\Graph.res"
	-@erase ".\Debug\NewDoc.obj"
	-@erase ".\Debug\Graph.ilk"
	-@erase ".\Debug\Graph.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Graph.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x404 /fo"$(INTDIR)/Graph.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Graph.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Graph.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Graph.exe" 
LINK32_OBJS= \
	".\Debug\TextView.obj" \
	".\Debug\Graph.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\GraphView.obj" \
	".\Debug\BarView.obj" \
	".\Debug\ChildFrm.obj" \
	".\Debug\GraphDoc.obj" \
	".\Debug\MainFrm.obj" \
	".\Debug\NewDoc.obj" \
	".\Debug\Graph.res"

"$(OUTDIR)\Graph.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Graph - Win32 Release"
# Name "Graph - Win32 Debug"

!IF  "$(CFG)" == "Graph - Win32 Release"

!ELSEIF  "$(CFG)" == "Graph - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Graph - Win32 Release"

!ELSEIF  "$(CFG)" == "Graph - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Graph.cpp
DEP_CPP_GRAPH=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\GraphDoc.h"\
	".\GraphView.h"\
	".\NewDoc.h"\
	

"$(INTDIR)\Graph.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Graph - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Graph.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Graph.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Graph - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Graph.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Graph.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\ChildFrm.h"\
	".\TextView.h"\
	".\BarView.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GraphDoc.cpp

!IF  "$(CFG)" == "Graph - Win32 Release"

DEP_CPP_GRAPHD=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\GraphDoc.h"\
	
NODEP_CPP_GRAPHD=\
	".\m_intArray"\
	".\SetValue"\
	

"$(INTDIR)\GraphDoc.obj" : $(SOURCE) $(DEP_CPP_GRAPHD) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


!ELSEIF  "$(CFG)" == "Graph - Win32 Debug"

DEP_CPP_GRAPHD=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\GraphDoc.h"\
	

"$(INTDIR)\GraphDoc.obj" : $(SOURCE) $(DEP_CPP_GRAPHD) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GraphView.cpp
DEP_CPP_GRAPHV=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\GraphDoc.h"\
	".\GraphView.h"\
	

"$(INTDIR)\GraphView.obj" : $(SOURCE) $(DEP_CPP_GRAPHV) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Graph.rc
DEP_RSC_GRAPH_=\
	".\res\Graph.ico"\
	".\res\GraphDoc.ico"\
	".\res\NewDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\Graph.rc2"\
	

"$(INTDIR)\Graph.res" : $(SOURCE) $(DEP_RSC_GRAPH_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TextView.cpp
DEP_CPP_TEXTV=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\GraphDoc.h"\
	".\TextView.h"\
	

"$(INTDIR)\TextView.obj" : $(SOURCE) $(DEP_CPP_TEXTV) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BarView.cpp
DEP_CPP_BARVI=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\GraphDoc.h"\
	".\BarView.h"\
	

"$(INTDIR)\BarView.obj" : $(SOURCE) $(DEP_CPP_BARVI) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NewDoc.cpp
DEP_CPP_NEWDO=\
	".\StdAfx.h"\
	".\Graph.h"\
	".\NewDoc.h"\
	

"$(INTDIR)\NewDoc.obj" : $(SOURCE) $(DEP_CPP_NEWDO) "$(INTDIR)"\
 "$(INTDIR)\Graph.pch"


# End Source File
# End Target
# End Project
################################################################################
