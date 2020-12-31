# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=CmDgTest - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CmDgTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CmDgTest - Win32 Release" && "$(CFG)" !=\
 "CmDgTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CmDgTest.mak" CFG="CmDgTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CmDgTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CmDgTest - Win32 Debug" (based on "Win32 (x86) Application")
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
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "CmDgTest - Win32 Release"

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

ALL : "$(OUTDIR)\CmDgTest.exe"

CLEAN : 
	-@erase ".\Release\CmDgTest.exe"
	-@erase ".\Release\CmDgTest.obj"
	-@erase ".\Release\CmDgTest.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\CmDgTestDoc.obj"
	-@erase ".\Release\CmDgTestView.obj"
	-@erase ".\Release\CmDgTest.res"
	-@erase ".\Release\MyFileDialog.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CmDgTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x406 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x406 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x406 /fo"$(INTDIR)/CmDgTest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CmDgTest.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/CmDgTest.pdb" /machine:I386 /out:"$(OUTDIR)/CmDgTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/CmDgTest.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/CmDgTestDoc.obj" \
	"$(INTDIR)/CmDgTestView.obj" \
	"$(INTDIR)/MyFileDialog.obj" \
	"$(INTDIR)/CmDgTest.res"

"$(OUTDIR)\CmDgTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"

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

ALL : "$(OUTDIR)\CmDgTest.exe" "$(OUTDIR)\CmDgTest.bsc"

CLEAN : 
	-@erase ".\Debug\CmDgTest.exe"
	-@erase ".\Debug\CmDgTest.obj"
	-@erase ".\Debug\CmDgTest.pch"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\CmDgTestDoc.obj"
	-@erase ".\Debug\CmDgTestView.obj"
	-@erase ".\Debug\CmDgTest.res"
	-@erase ".\Debug\MyFileDialog.obj"
	-@erase ".\Debug\CmDgTest.ilk"
	-@erase ".\Debug\CmDgTest.pdb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\CmDgTest.bsc"
	-@erase ".\Debug\CmDgTest.sbr"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\MainFrm.sbr"
	-@erase ".\Debug\CmDgTestDoc.sbr"
	-@erase ".\Debug\CmDgTestView.sbr"
	-@erase ".\Debug\MyFileDialog.sbr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/CmDgTest.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x406 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x406 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x406 /fo"$(INTDIR)/CmDgTest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CmDgTest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/CmDgTest.sbr" \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/MainFrm.sbr" \
	"$(INTDIR)/CmDgTestDoc.sbr" \
	"$(INTDIR)/CmDgTestView.sbr" \
	"$(INTDIR)/MyFileDialog.sbr"

"$(OUTDIR)\CmDgTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/CmDgTest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/CmDgTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/CmDgTest.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/CmDgTestDoc.obj" \
	"$(INTDIR)/CmDgTestView.obj" \
	"$(INTDIR)/MyFileDialog.obj" \
	"$(INTDIR)/CmDgTest.res"

"$(OUTDIR)\CmDgTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CmDgTest - Win32 Release"
# Name "CmDgTest - Win32 Debug"

!IF  "$(CFG)" == "CmDgTest - Win32 Release"

!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "CmDgTest - Win32 Release"

!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CmDgTest.cpp
DEP_CPP_CMDGT=\
	".\StdAfx.h"\
	".\CmDgTest.h"\
	".\MainFrm.h"\
	".\CmDgTestDoc.h"\
	".\CmDgTestView.h"\
	".\MyFileDialog.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"


"$(INTDIR)\CmDgTest.obj" : $(SOURCE) $(DEP_CPP_CMDGT) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"


"$(INTDIR)\CmDgTest.obj" : $(SOURCE) $(DEP_CPP_CMDGT) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"

"$(INTDIR)\CmDgTest.sbr" : $(SOURCE) $(DEP_CPP_CMDGT) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/CmDgTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CmDgTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/CmDgTest.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CmDgTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\CmDgTest.h"\
	".\MainFrm.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CmDgTestDoc.cpp
DEP_CPP_CMDGTE=\
	".\StdAfx.h"\
	".\CmDgTest.h"\
	".\CmDgTestDoc.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"


"$(INTDIR)\CmDgTestDoc.obj" : $(SOURCE) $(DEP_CPP_CMDGTE) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"


"$(INTDIR)\CmDgTestDoc.obj" : $(SOURCE) $(DEP_CPP_CMDGTE) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"

"$(INTDIR)\CmDgTestDoc.sbr" : $(SOURCE) $(DEP_CPP_CMDGTE) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CmDgTestView.cpp
DEP_CPP_CMDGTES=\
	".\StdAfx.h"\
	".\CmDgTest.h"\
	".\CmDgTestDoc.h"\
	".\CmDgTestView.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"


"$(INTDIR)\CmDgTestView.obj" : $(SOURCE) $(DEP_CPP_CMDGTES) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"


"$(INTDIR)\CmDgTestView.obj" : $(SOURCE) $(DEP_CPP_CMDGTES) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"

"$(INTDIR)\CmDgTestView.sbr" : $(SOURCE) $(DEP_CPP_CMDGTES) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CmDgTest.rc
DEP_RSC_CMDGTEST=\
	".\res\CmDgTest.ico"\
	".\res\CmDgTestDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\CmDgTest.rc2"\
	

"$(INTDIR)\CmDgTest.res" : $(SOURCE) $(DEP_RSC_CMDGTEST) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyFileDialog.cpp
DEP_CPP_MYFIL=\
	".\StdAfx.h"\
	".\CmDgTest.h"\
	".\MyFileDialog.h"\
	

!IF  "$(CFG)" == "CmDgTest - Win32 Release"


"$(INTDIR)\MyFileDialog.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ELSEIF  "$(CFG)" == "CmDgTest - Win32 Debug"


"$(INTDIR)\MyFileDialog.obj" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"

"$(INTDIR)\MyFileDialog.sbr" : $(SOURCE) $(DEP_CPP_MYFIL) "$(INTDIR)"\
 "$(INTDIR)\CmDgTest.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
