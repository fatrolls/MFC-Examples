# Microsoft Developer Studio Generated NMAKE File, Based on resviewer.dsp
!IF "$(CFG)" == ""
CFG=resviewer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to resviewer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "resviewer - Win32 Release" && "$(CFG)" !=\
 "resviewer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "resviewer.mak" CFG="resviewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "resviewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "resviewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "resviewer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\resviewer.exe"

!ELSE 

ALL : "$(OUTDIR)\resviewer.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\PERsrc.obj"
	-@erase "$(INTDIR)\ResourceTree.obj"
	-@erase "$(INTDIR)\resviewer.obj"
	-@erase "$(INTDIR)\resviewer.pch"
	-@erase "$(INTDIR)\resviewer.res"
	-@erase "$(INTDIR)\resviewerDoc.obj"
	-@erase "$(INTDIR)\resviewerView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\resviewer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\resviewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resviewer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\resviewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\resviewer.pdb" /machine:I386 /out:"$(OUTDIR)\resviewer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PERsrc.obj" \
	"$(INTDIR)\ResourceTree.obj" \
	"$(INTDIR)\resviewer.obj" \
	"$(INTDIR)\resviewer.res" \
	"$(INTDIR)\resviewerDoc.obj" \
	"$(INTDIR)\resviewerView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\resviewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\resviewer.exe"

!ELSE 

ALL : "$(OUTDIR)\resviewer.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\PERsrc.obj"
	-@erase "$(INTDIR)\ResourceTree.obj"
	-@erase "$(INTDIR)\resviewer.obj"
	-@erase "$(INTDIR)\resviewer.pch"
	-@erase "$(INTDIR)\resviewer.res"
	-@erase "$(INTDIR)\resviewerDoc.obj"
	-@erase "$(INTDIR)\resviewerView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\resviewer.exe"
	-@erase "$(OUTDIR)\resviewer.ilk"
	-@erase "$(OUTDIR)\resviewer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\resviewer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resviewer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\resviewer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\resviewer.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\resviewer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PERsrc.obj" \
	"$(INTDIR)\ResourceTree.obj" \
	"$(INTDIR)\resviewer.obj" \
	"$(INTDIR)\resviewer.res" \
	"$(INTDIR)\resviewerDoc.obj" \
	"$(INTDIR)\resviewerView.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\resviewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "resviewer - Win32 Release" || "$(CFG)" ==\
 "resviewer - Win32 Debug"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\resviewer.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\resviewer.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\PERsrc.CPP

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_PERSR=\
	".\PERsrc.H"\
	

"$(INTDIR)\PERsrc.obj" : $(SOURCE) $(DEP_CPP_PERSR) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"


"$(INTDIR)\PERsrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\ResourceTree.cpp

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_RESOU=\
	".\ResourceTree.h"\
	".\resviewer.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ResourceTree.obj" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

DEP_CPP_RESOU=\
	".\ResourceTree.h"\
	".\resviewer.h"\
	

"$(INTDIR)\ResourceTree.obj" : $(SOURCE) $(DEP_CPP_RESOU) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\resviewer.cpp

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_RESVI=\
	".\MainFrm.h"\
	".\resviewer.h"\
	".\resviewerDoc.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RESVI=\
	".\ressourceTree.h"\
	

"$(INTDIR)\resviewer.obj" : $(SOURCE) $(DEP_CPP_RESVI) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"


"$(INTDIR)\resviewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\resviewer.rc
DEP_RSC_RESVIE=\
	".\res\resviewer.ico"\
	".\res\resviewer.rc2"\
	".\res\resviewerDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\resviewer.res" : $(SOURCE) $(DEP_RSC_RESVIE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\resviewerDoc.cpp

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_RESVIEW=\
	".\resviewer.h"\
	".\resviewerDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\resviewerDoc.obj" : $(SOURCE) $(DEP_CPP_RESVIEW) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

DEP_CPP_RESVIEW=\
	".\resviewer.h"\
	".\resviewerDoc.h"\
	

"$(INTDIR)\resviewerDoc.obj" : $(SOURCE) $(DEP_CPP_RESVIEW) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\resviewerView.cpp

!IF  "$(CFG)" == "resviewer - Win32 Release"

DEP_CPP_RESVIEWE=\
	".\resviewer.h"\
	".\resviewerDoc.h"\
	".\resviewerView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\resviewerView.obj" : $(SOURCE) $(DEP_CPP_RESVIEWE) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

DEP_CPP_RESVIEWE=\
	".\resviewer.h"\
	".\resviewerDoc.h"\
	".\resviewerView.h"\
	

"$(INTDIR)\resviewerView.obj" : $(SOURCE) $(DEP_CPP_RESVIEWE) "$(INTDIR)"\
 "$(INTDIR)\resviewer.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "resviewer - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\resviewer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\resviewer.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "resviewer - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\resviewer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\resviewer.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

