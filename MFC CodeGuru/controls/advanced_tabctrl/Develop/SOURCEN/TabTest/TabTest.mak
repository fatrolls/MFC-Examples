# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TabTest - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TabTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TabTest - Win32 Release" && "$(CFG)" !=\
 "TabTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TabTest.mak" CFG="TabTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TabTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TabTest - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "TabTest - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "TabTest - Win32 Release"

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

ALL : "$(OUTDIR)\TabTest.exe"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TabCtrlAdvanced.obj"
	-@erase "$(INTDIR)\TabTest.obj"
	-@erase "$(INTDIR)\TabTest.pch"
	-@erase "$(INTDIR)\TabTest.res"
	-@erase "$(INTDIR)\TabTestDoc.obj"
	-@erase "$(INTDIR)\TabTestView.obj"
	-@erase "$(OUTDIR)\TabTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TabTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TabTest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TabTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TabTest.pdb" /machine:I386 /out:"$(OUTDIR)/TabTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TabCtrlAdvanced.obj" \
	"$(INTDIR)\TabTest.obj" \
	"$(INTDIR)\TabTest.res" \
	"$(INTDIR)\TabTestDoc.obj" \
	"$(INTDIR)\TabTestView.obj"

"$(OUTDIR)\TabTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"

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

ALL : "$(OUTDIR)\TabTest.exe" "$(OUTDIR)\TabTest.bsc"

CLEAN : 
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TabCtrlAdvanced.obj"
	-@erase "$(INTDIR)\TabCtrlAdvanced.sbr"
	-@erase "$(INTDIR)\TabTest.obj"
	-@erase "$(INTDIR)\TabTest.pch"
	-@erase "$(INTDIR)\TabTest.res"
	-@erase "$(INTDIR)\TabTest.sbr"
	-@erase "$(INTDIR)\TabTestDoc.obj"
	-@erase "$(INTDIR)\TabTestDoc.sbr"
	-@erase "$(INTDIR)\TabTestView.obj"
	-@erase "$(INTDIR)\TabTestView.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\TabTest.bsc"
	-@erase "$(OUTDIR)\TabTest.exe"
	-@erase "$(OUTDIR)\TabTest.ilk"
	-@erase "$(OUTDIR)\TabTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/TabTest.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TabTest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TabTest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TabCtrlAdvanced.sbr" \
	"$(INTDIR)\TabTest.sbr" \
	"$(INTDIR)\TabTestDoc.sbr" \
	"$(INTDIR)\TabTestView.sbr"

"$(OUTDIR)\TabTest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TabTest.pdb" /debug /machine:I386 /out:"$(OUTDIR)/TabTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TabCtrlAdvanced.obj" \
	"$(INTDIR)\TabTest.obj" \
	"$(INTDIR)\TabTest.res" \
	"$(INTDIR)\TabTestDoc.obj" \
	"$(INTDIR)\TabTestView.obj"

"$(OUTDIR)\TabTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "TabTest - Win32 Release"
# Name "TabTest - Win32 Debug"

!IF  "$(CFG)" == "TabTest - Win32 Release"

!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "TabTest - Win32 Release"

!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TabTest.cpp
DEP_CPP_TABTE=\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\TabCtrlAdvanced.h"\
	".\TabTest.h"\
	".\TabTestDoc.h"\
	".\TabTestView.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\TabTest.obj" : $(SOURCE) $(DEP_CPP_TABTE) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\TabTest.obj" : $(SOURCE) $(DEP_CPP_TABTE) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\TabTest.sbr" : $(SOURCE) $(DEP_CPP_TABTE) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TabTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TabTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/TabTest.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TabTest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\TabTest.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\StdAfx.h"\
	".\TabTest.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TabTestDoc.cpp
DEP_CPP_TABTES=\
	".\StdAfx.h"\
	".\TabTest.h"\
	".\TabTestDoc.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\TabTestDoc.obj" : $(SOURCE) $(DEP_CPP_TABTES) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\TabTestDoc.obj" : $(SOURCE) $(DEP_CPP_TABTES) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\TabTestDoc.sbr" : $(SOURCE) $(DEP_CPP_TABTES) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TabTestView.cpp
DEP_CPP_TABTEST=\
	".\StdAfx.h"\
	".\TabCtrlAdvanced.h"\
	".\TabTest.h"\
	".\TabTestDoc.h"\
	".\TabTestView.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\TabTestView.obj" : $(SOURCE) $(DEP_CPP_TABTEST) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\TabTestView.obj" : $(SOURCE) $(DEP_CPP_TABTEST) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\TabTestView.sbr" : $(SOURCE) $(DEP_CPP_TABTEST) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TabTest.rc
DEP_RSC_TABTEST_=\
	".\res\TabTest.ico"\
	".\res\TabTest.rc2"\
	".\res\TabTestDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\TabTest.res" : $(SOURCE) $(DEP_RSC_TABTEST_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TabCtrlAdvanced.cpp
DEP_CPP_TABCT=\
	".\StdAfx.h"\
	".\TabCtrlAdvanced.h"\
	".\TabTest.h"\
	

!IF  "$(CFG)" == "TabTest - Win32 Release"


"$(INTDIR)\TabCtrlAdvanced.obj" : $(SOURCE) $(DEP_CPP_TABCT) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ELSEIF  "$(CFG)" == "TabTest - Win32 Debug"


"$(INTDIR)\TabCtrlAdvanced.obj" : $(SOURCE) $(DEP_CPP_TABCT) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"

"$(INTDIR)\TabCtrlAdvanced.sbr" : $(SOURCE) $(DEP_CPP_TABCT) "$(INTDIR)"\
 "$(INTDIR)\TabTest.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
