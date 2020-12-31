# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Scribble - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Scribble - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Scribble - Win32 Release" && "$(CFG)" !=\
 "Scribble - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Scribble.mak" CFG="Scribble - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Scribble - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Scribble - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Scribble - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Scribble - Win32 Release"

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

ALL : "$(OUTDIR)\Scribble.exe"

CLEAN : 
	-@erase ".\Release\Scribble.exe"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\Scribble.pch"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\ScribbleDoc.obj"
	-@erase ".\Release\ScribbleView.obj"
	-@erase ".\Release\Scribble.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Scribble.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Scribble.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x404 /fo"$(INTDIR)/Scribble.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Scribble.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Scribble.pdb" /machine:I386 /out:"$(OUTDIR)/Scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/ScribbleDoc.obj" \
	"$(INTDIR)/ScribbleView.obj" \
	"$(INTDIR)/Scribble.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Scribble.res"

"$(OUTDIR)\Scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"

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

ALL : "$(OUTDIR)\Scribble.exe" "$(OUTDIR)\Scribble.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Scribble.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Scribble.exe"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\ScribbleView.obj"
	-@erase ".\Debug\ScribbleDoc.obj"
	-@erase ".\Debug\Scribble.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\Scribble.res"
	-@erase ".\Debug\Scribble.ilk"
	-@erase ".\Debug\Scribble.pdb"
	-@erase ".\Debug\Scribble.bsc"
	-@erase ".\Debug\Scribble.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\ChildFrm.sbr"
	-@erase ".\Debug\ScribbleDoc.sbr"
	-@erase ".\Debug\ScribbleView.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Scribble.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x404 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x404 /fo"$(INTDIR)/Scribble.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Scribble.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Scribble.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/ChildFrm.sbr" \
	"$(INTDIR)/ScribbleDoc.sbr" \
	"$(INTDIR)/ScribbleView.sbr"

"$(OUTDIR)\Scribble.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Scribble.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Scribble.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/ScribbleView.obj" \
	"$(INTDIR)/ScribbleDoc.obj" \
	"$(INTDIR)/Scribble.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Scribble.res"

"$(OUTDIR)\Scribble.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Scribble - Win32 Release"
# Name "Scribble - Win32 Debug"

!IF  "$(CFG)" == "Scribble - Win32 Release"

!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Scribble - Win32 Release"

!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scribble.cpp
DEP_CPP_SCRIB=\
	".\StdAfx.h"\
	".\Scribble.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\ScribbleDoc.h"\
	".\ScribbleView.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"


"$(INTDIR)\Scribble.obj" : $(SOURCE) $(DEP_CPP_SCRIB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"


"$(INTDIR)\Scribble.obj" : $(SOURCE) $(DEP_CPP_SCRIB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"

"$(INTDIR)\Scribble.sbr" : $(SOURCE) $(DEP_CPP_SCRIB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Scribble.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Scribble.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Scribble.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Scribble.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\Scribble.h"\
	".\MainFrm.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\Scribble.h"\
	".\ChildFrm.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScribbleDoc.cpp
DEP_CPP_SCRIBB=\
	".\StdAfx.h"\
	".\Scribble.h"\
	".\ScribbleDoc.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"


"$(INTDIR)\ScribbleDoc.obj" : $(SOURCE) $(DEP_CPP_SCRIBB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"


"$(INTDIR)\ScribbleDoc.obj" : $(SOURCE) $(DEP_CPP_SCRIBB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"

"$(INTDIR)\ScribbleDoc.sbr" : $(SOURCE) $(DEP_CPP_SCRIBB) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScribbleView.cpp
DEP_CPP_SCRIBBL=\
	".\StdAfx.h"\
	".\Scribble.h"\
	".\ScribbleDoc.h"\
	".\ScribbleView.h"\
	

!IF  "$(CFG)" == "Scribble - Win32 Release"


"$(INTDIR)\ScribbleView.obj" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ELSEIF  "$(CFG)" == "Scribble - Win32 Debug"


"$(INTDIR)\ScribbleView.obj" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"

"$(INTDIR)\ScribbleView.sbr" : $(SOURCE) $(DEP_CPP_SCRIBBL) "$(INTDIR)"\
 "$(INTDIR)\Scribble.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scribble.rc
DEP_RSC_SCRIBBLE=\
	".\res\Scribble.ico"\
	".\res\ScribbleDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\Scribble.rc2"\
	

"$(INTDIR)\Scribble.res" : $(SOURCE) $(DEP_RSC_SCRIBBLE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
