# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Msdi - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Msdi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Msdi - Win32 Release" && "$(CFG)" != "Msdi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Msdi.mak" CFG="Msdi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Msdi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Msdi - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Msdi - Win32 Debug"
CPP=cl.exe
F90=fl32.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Msdi - Win32 Release"

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

ALL : "$(OUTDIR)\Msdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Grafview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Msdi.obj"
	-@erase "$(INTDIR)\Msdi.pch"
	-@erase "$(INTDIR)\Msdi.res"
	-@erase "$(INTDIR)\Msdiapp.obj"
	-@erase "$(INTDIR)\MsdiDoc.obj"
	-@erase "$(INTDIR)\Msdifrm.obj"
	-@erase "$(INTDIR)\MsdiView.obj"
	-@erase "$(INTDIR)\Outview.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Viewfrm.obj"
	-@erase "$(OUTDIR)\Msdi.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Msdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x100c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/Msdi.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Msdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Msdi.pdb" /machine:I386 /out:"$(OUTDIR)/Msdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Grafview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Msdi.obj" \
	"$(INTDIR)\Msdi.res" \
	"$(INTDIR)\Msdiapp.obj" \
	"$(INTDIR)\MsdiDoc.obj" \
	"$(INTDIR)\Msdifrm.obj" \
	"$(INTDIR)\MsdiView.obj" \
	"$(INTDIR)\Outview.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Viewfrm.obj"

"$(OUTDIR)\Msdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Msdi - Win32 Debug"

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

ALL : "$(OUTDIR)\Msdi.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Grafview.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Msdi.obj"
	-@erase "$(INTDIR)\Msdi.pch"
	-@erase "$(INTDIR)\Msdi.res"
	-@erase "$(INTDIR)\Msdiapp.obj"
	-@erase "$(INTDIR)\MsdiDoc.obj"
	-@erase "$(INTDIR)\Msdifrm.obj"
	-@erase "$(INTDIR)\MsdiView.obj"
	-@erase "$(INTDIR)\Outview.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Viewfrm.obj"
	-@erase "$(OUTDIR)\Msdi.exe"
	-@erase "$(OUTDIR)\Msdi.ilk"
	-@erase "$(OUTDIR)\Msdi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Msdi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x100c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/Msdi.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Msdi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Msdi.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Msdi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Grafview.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Msdi.obj" \
	"$(INTDIR)\Msdi.res" \
	"$(INTDIR)\Msdiapp.obj" \
	"$(INTDIR)\MsdiDoc.obj" \
	"$(INTDIR)\Msdifrm.obj" \
	"$(INTDIR)\MsdiView.obj" \
	"$(INTDIR)\Outview.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Viewfrm.obj"

"$(OUTDIR)\Msdi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "Msdi - Win32 Release"
# Name "Msdi - Win32 Debug"

!IF  "$(CFG)" == "Msdi - Win32 Release"

!ELSEIF  "$(CFG)" == "Msdi - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Msdi - Win32 Release"

!ELSEIF  "$(CFG)" == "Msdi - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdi.cpp
DEP_CPP_MSDI_=\
	".\grafview.h"\
	".\MainFrm.h"\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\MsdiDoc.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\MsdiView.h"\
	".\outview.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Msdi.obj" : $(SOURCE) $(DEP_CPP_MSDI_) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Msdi - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Msdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Msdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Msdi - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Msdi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Msdi.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\outview.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsdiDoc.cpp
DEP_CPP_MSDID=\
	".\grafview.h"\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\MsdiDoc.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\outview.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MsdiDoc.obj" : $(SOURCE) $(DEP_CPP_MSDID) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsdiView.cpp
DEP_CPP_MSDIV=\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\MsdiDoc.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\MsdiView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MsdiView.obj" : $(SOURCE) $(DEP_CPP_MSDIV) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdi.rc
DEP_RSC_MSDI_R=\
	".\RES\GRAFVIEW.ICO"\
	".\res\Msdi.ico"\
	".\res\Msdi.rc2"\
	".\RES\MSDIVIEW.ICO"\
	".\RES\OUTVIEW.ICO"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Msdi.res" : $(SOURCE) $(DEP_RSC_MSDI_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdiapp.cpp
DEP_CPP_MSDIA=\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Msdiapp.obj" : $(SOURCE) $(DEP_CPP_MSDIA) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdifrm.cpp
DEP_CPP_MSDIF=\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Msdifrm.obj" : $(SOURCE) $(DEP_CPP_MSDIF) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Outview.cpp
DEP_CPP_OUTVI=\
	".\MainFrm.h"\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\outview.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Outview.obj" : $(SOURCE) $(DEP_CPP_OUTVI) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Viewfrm.cpp
DEP_CPP_VIEWF=\
	".\msdiapp.h"\
	".\msdifrm.h"\
	".\StdAfx.h"\
	".\viewfrm.h"\
	

"$(INTDIR)\Viewfrm.obj" : $(SOURCE) $(DEP_CPP_VIEWF) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Grafview.cpp
DEP_CPP_GRAFV=\
	".\grafview.h"\
	".\Msdi.h"\
	".\msdiapp.h"\
	".\MsdiDoc.h"\
	".\msdifrm.h"\
	".\msdivfrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Grafview.obj" : $(SOURCE) $(DEP_CPP_GRAFV) "$(INTDIR)"\
 "$(INTDIR)\Msdi.pch"


# End Source File
# End Target
# End Project
################################################################################
