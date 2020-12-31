# Microsoft Developer Studio Generated NMAKE File, Based on VBScriptEditor.dsp
!IF "$(CFG)" == ""
CFG=VBScriptEditor - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VBScriptEditor - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "VBScriptEditor - Win32 Release" && "$(CFG)" !=\
 "VBScriptEditor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VBScriptEditor.mak" CFG="VBScriptEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VBScriptEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VBScriptEditor - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "VBScriptEditor - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VBScriptEditor.exe"

!ELSE 

ALL : "$(OUTDIR)\VBScriptEditor.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\VBScriptEditor.obj"
	-@erase "$(INTDIR)\VBScriptEditor.pch"
	-@erase "$(INTDIR)\VBScriptEditor.res"
	-@erase "$(INTDIR)\VBScriptEditorDoc.obj"
	-@erase "$(INTDIR)\VBScriptEditorView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\VBScriptEditor.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\VBScriptEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VBScriptEditor.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VBScriptEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\VBScriptEditor.pdb" /machine:I386\
 /out:"$(OUTDIR)\VBScriptEditor.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VBScriptEditor.obj" \
	"$(INTDIR)\VBScriptEditor.res" \
	"$(INTDIR)\VBScriptEditorDoc.obj" \
	"$(INTDIR)\VBScriptEditorView.obj"

"$(OUTDIR)\VBScriptEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VBScriptEditor - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\VBScriptEditor.exe"

!ELSE 

ALL : "$(OUTDIR)\VBScriptEditor.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\VBScriptEditor.obj"
	-@erase "$(INTDIR)\VBScriptEditor.pch"
	-@erase "$(INTDIR)\VBScriptEditor.res"
	-@erase "$(INTDIR)\VBScriptEditorDoc.obj"
	-@erase "$(INTDIR)\VBScriptEditorView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\VBScriptEditor.exe"
	-@erase "$(OUTDIR)\VBScriptEditor.ilk"
	-@erase "$(OUTDIR)\VBScriptEditor.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\VBScriptEditor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VBScriptEditor.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VBScriptEditor.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\VBScriptEditor.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\VBScriptEditor.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VBScriptEditor.obj" \
	"$(INTDIR)\VBScriptEditor.res" \
	"$(INTDIR)\VBScriptEditorDoc.obj" \
	"$(INTDIR)\VBScriptEditorView.obj"

"$(OUTDIR)\VBScriptEditor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "VBScriptEditor - Win32 Release" || "$(CFG)" ==\
 "VBScriptEditor - Win32 Debug"
SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\VBScriptEditor.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\VBScriptEditor.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "VBScriptEditor - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\VBScriptEditor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VBScriptEditor.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VBScriptEditor - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\VBScriptEditor.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VBScriptEditor.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VBScriptEditor.cpp
DEP_CPP_VBSCR=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\VBScriptEditor.h"\
	".\VBScriptEditorDoc.h"\
	".\VBScriptEditorView.h"\
	

"$(INTDIR)\VBScriptEditor.obj" : $(SOURCE) $(DEP_CPP_VBSCR) "$(INTDIR)"\
 "$(INTDIR)\VBScriptEditor.pch"


SOURCE=.\VBScriptEditor.rc
DEP_RSC_VBSCRI=\
	".\res\Toolbar.bmp"\
	".\res\VBScriptEditor.ico"\
	".\res\VBScriptEditor.rc2"\
	".\res\VBScriptEditorDoc.ico"\
	

"$(INTDIR)\VBScriptEditor.res" : $(SOURCE) $(DEP_RSC_VBSCRI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VBScriptEditorDoc.cpp
DEP_CPP_VBSCRIP=\
	".\StdAfx.h"\
	".\VBScriptEditor.h"\
	".\VBScriptEditorDoc.h"\
	".\VBScriptEditorView.h"\
	

"$(INTDIR)\VBScriptEditorDoc.obj" : $(SOURCE) $(DEP_CPP_VBSCRIP) "$(INTDIR)"\
 "$(INTDIR)\VBScriptEditor.pch"


SOURCE=.\VBScriptEditorView.cpp
DEP_CPP_VBSCRIPT=\
	".\StdAfx.h"\
	".\VBScriptEditor.h"\
	".\VBScriptEditorDoc.h"\
	".\VBScriptEditorView.h"\
	

"$(INTDIR)\VBScriptEditorView.obj" : $(SOURCE) $(DEP_CPP_VBSCRIPT) "$(INTDIR)"\
 "$(INTDIR)\VBScriptEditor.pch"



!ENDIF 

