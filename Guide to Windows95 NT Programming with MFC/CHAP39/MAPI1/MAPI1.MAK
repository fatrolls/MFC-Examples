# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Mapi1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Mapi1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Mapi1 - Win32 Release" && "$(CFG)" != "Mapi1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mapi1.mak" CFG="Mapi1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mapi1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Mapi1 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Mapi1 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Mapi1 - Win32 Release"

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

ALL : "$(OUTDIR)\Mapi1.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Mapi1.obj"
	-@erase "$(INTDIR)\Mapi1.pch"
	-@erase "$(INTDIR)\Mapi1.res"
	-@erase "$(INTDIR)\Mapi1Doc.obj"
	-@erase "$(INTDIR)\Mapi1Vw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Mapi1.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mapi1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Mapi1.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mapi1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Mapi1.pdb" /machine:I386 /out:"$(OUTDIR)/Mapi1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Mapi1.obj" \
	"$(INTDIR)\Mapi1.res" \
	"$(INTDIR)\Mapi1Doc.obj" \
	"$(INTDIR)\Mapi1Vw.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Mapi1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Mapi1 - Win32 Debug"

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

ALL : "$(OUTDIR)\Mapi1.exe"

CLEAN : 
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Mapi1.obj"
	-@erase "$(INTDIR)\Mapi1.pch"
	-@erase "$(INTDIR)\Mapi1.res"
	-@erase "$(INTDIR)\Mapi1Doc.obj"
	-@erase "$(INTDIR)\Mapi1Vw.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Mapi1.exe"
	-@erase "$(OUTDIR)\Mapi1.ilk"
	-@erase "$(OUTDIR)\Mapi1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mapi1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Mapi1.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mapi1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Mapi1.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Mapi1.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Mapi1.obj" \
	"$(INTDIR)\Mapi1.res" \
	"$(INTDIR)\Mapi1Doc.obj" \
	"$(INTDIR)\Mapi1Vw.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Mapi1.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Mapi1 - Win32 Release"
# Name "Mapi1 - Win32 Debug"

!IF  "$(CFG)" == "Mapi1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Mapi1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Mapi1 - Win32 Release"

!ELSEIF  "$(CFG)" == "Mapi1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mapi1.cpp
DEP_CPP_MAPI1=\
	".\MainFrm.h"\
	".\Mapi1.h"\
	".\Mapi1Doc.h"\
	".\Mapi1Vw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mapi1.obj" : $(SOURCE) $(DEP_CPP_MAPI1) "$(INTDIR)"\
 "$(INTDIR)\Mapi1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Mapi1 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mapi1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mapi1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Mapi1 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Mapi1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Mapi1.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Mapi1.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Mapi1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mapi1Doc.cpp

!IF  "$(CFG)" == "Mapi1 - Win32 Release"

DEP_CPP_MAPI1D=\
	".\Mapi1.h"\
	".\Mapi1Doc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mapi1Doc.obj" : $(SOURCE) $(DEP_CPP_MAPI1D) "$(INTDIR)"\
 "$(INTDIR)\Mapi1.pch"


!ELSEIF  "$(CFG)" == "Mapi1 - Win32 Debug"

DEP_CPP_MAPI1D=\
	".\Mapi1.h"\
	".\Mapi1Doc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mapi1Doc.obj" : $(SOURCE) $(DEP_CPP_MAPI1D) "$(INTDIR)"\
 "$(INTDIR)\Mapi1.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mapi1Vw.cpp
DEP_CPP_MAPI1V=\
	".\Mapi1.h"\
	".\Mapi1Doc.h"\
	".\Mapi1Vw.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Mapi1Vw.obj" : $(SOURCE) $(DEP_CPP_MAPI1V) "$(INTDIR)"\
 "$(INTDIR)\Mapi1.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mapi1.rc
DEP_RSC_MAPI1_=\
	".\res\Mapi1.ico"\
	".\res\Mapi1.rc2"\
	".\res\Mapi1Doc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Mapi1.res" : $(SOURCE) $(DEP_RSC_MAPI1_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
