# Microsoft Developer Studio Generated NMAKE File, Based on CVBScriptEditDlg.dsp
!IF "$(CFG)" == ""
CFG=CVBScriptEditDlg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CVBScriptEditDlg - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "CVBScriptEditDlg - Win32 Release" && "$(CFG)" !=\
 "CVBScriptEditDlg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CVBScriptEditDlg.mak" CFG="CVBScriptEditDlg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CVBScriptEditDlg - Win32 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "CVBScriptEditDlg - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CVBScriptEditDlg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CVBScriptEditDlg.exe"

!ELSE 

ALL : "$(OUTDIR)\CVBScriptEditDlg.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CVBScriptEditDlg.obj"
	-@erase "$(INTDIR)\CVBScriptEditDlg.pch"
	-@erase "$(INTDIR)\CVBScriptEditDlg.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TWScriptEdit.obj"
	-@erase "$(INTDIR)\VBScriptEditDlg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\CVBScriptEditDlg.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\CVBScriptEditDlg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CVBScriptEditDlg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CVBScriptEditDlg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\CVBScriptEditDlg.pdb" /machine:I386\
 /out:"$(OUTDIR)\CVBScriptEditDlg.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CVBScriptEditDlg.obj" \
	"$(INTDIR)\CVBScriptEditDlg.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TWScriptEdit.obj" \
	"$(INTDIR)\VBScriptEditDlg.obj"

"$(OUTDIR)\CVBScriptEditDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CVBScriptEditDlg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\CVBScriptEditDlg.exe"

!ELSE 

ALL : "$(OUTDIR)\CVBScriptEditDlg.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\CVBScriptEditDlg.obj"
	-@erase "$(INTDIR)\CVBScriptEditDlg.pch"
	-@erase "$(INTDIR)\CVBScriptEditDlg.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TWScriptEdit.obj"
	-@erase "$(INTDIR)\VBScriptEditDlg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\CVBScriptEditDlg.exe"
	-@erase "$(OUTDIR)\CVBScriptEditDlg.ilk"
	-@erase "$(OUTDIR)\CVBScriptEditDlg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\CVBScriptEditDlg.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\CVBScriptEditDlg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CVBScriptEditDlg.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\CVBScriptEditDlg.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\CVBScriptEditDlg.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CVBScriptEditDlg.obj" \
	"$(INTDIR)\CVBScriptEditDlg.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TWScriptEdit.obj" \
	"$(INTDIR)\VBScriptEditDlg.obj"

"$(OUTDIR)\CVBScriptEditDlg.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(CFG)" == "CVBScriptEditDlg - Win32 Release" || "$(CFG)" ==\
 "CVBScriptEditDlg - Win32 Debug"
SOURCE=.\CVBScriptEditDlg.cpp
DEP_CPP_CVBSC=\
	".\CVBScriptEditDlg.h"\
	".\StdAfx.h"\
	".\TWScriptEdit.h"\
	".\VBScriptEditDlg.h"\
	

"$(INTDIR)\CVBScriptEditDlg.obj" : $(SOURCE) $(DEP_CPP_CVBSC) "$(INTDIR)"\
 "$(INTDIR)\CVBScriptEditDlg.pch"


SOURCE=.\CVBScriptEditDlg.rc
DEP_RSC_CVBSCR=\
	".\res\CVBScriptEditDlg.ico"\
	".\res\CVBScriptEditDlg.rc2"\
	

"$(INTDIR)\CVBScriptEditDlg.res" : $(SOURCE) $(DEP_RSC_CVBSCR) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CVBScriptEditDlg - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\CVBScriptEditDlg.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CVBScriptEditDlg.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "CVBScriptEditDlg - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\CVBScriptEditDlg.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\CVBScriptEditDlg.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TWScriptEdit.cpp
DEP_CPP_TWSCR=\
	".\StdAfx.h"\
	".\TWScriptEdit.h"\
	

"$(INTDIR)\TWScriptEdit.obj" : $(SOURCE) $(DEP_CPP_TWSCR) "$(INTDIR)"\
 "$(INTDIR)\CVBScriptEditDlg.pch"


SOURCE=.\VBScriptEditDlg.cpp
DEP_CPP_VBSCR=\
	".\CVBScriptEditDlg.h"\
	".\StdAfx.h"\
	".\TWScriptEdit.h"\
	".\VBScriptEditDlg.h"\
	

"$(INTDIR)\VBScriptEditDlg.obj" : $(SOURCE) $(DEP_CPP_VBSCR) "$(INTDIR)"\
 "$(INTDIR)\CVBScriptEditDlg.pch"



!ENDIF 

