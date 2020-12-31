# Microsoft Developer Studio Generated NMAKE File, Based on Tool.dsp
!IF "$(CFG)" == ""
CFG=Tool - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Tool - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Tool - Win32 Release" && "$(CFG)" != "Tool - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tool.mak" CFG="Tool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Tool - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Tool.exe"

!ELSE 

ALL : "$(OUTDIR)\Tool.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\DlgAbout.obj"
	-@erase "$(INTDIR)\FormCommandView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RenderView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tool.obj"
	-@erase "$(INTDIR)\Tool.pch"
	-@erase "$(INTDIR)\Tool.res"
	-@erase "$(INTDIR)\ToolDoc.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Tool.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Tool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Tool.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\Tool.pdb" /machine:I386 /out:"$(OUTDIR)\Tool.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DlgAbout.obj" \
	"$(INTDIR)\FormCommandView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RenderView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tool.obj" \
	"$(INTDIR)\Tool.res" \
	"$(INTDIR)\ToolDoc.obj"

"$(OUTDIR)\Tool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Tool.exe"

!ELSE 

ALL : "$(OUTDIR)\Tool.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\DlgAbout.obj"
	-@erase "$(INTDIR)\FormCommandView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\RenderView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tool.obj"
	-@erase "$(INTDIR)\Tool.pch"
	-@erase "$(INTDIR)\Tool.res"
	-@erase "$(INTDIR)\ToolDoc.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Tool.exe"
	-@erase "$(OUTDIR)\Tool.ilk"
	-@erase "$(OUTDIR)\Tool.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\Tool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Tool.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Tool.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib glu32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Tool.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Tool.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DlgAbout.obj" \
	"$(INTDIR)\FormCommandView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\RenderView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tool.obj" \
	"$(INTDIR)\Tool.res" \
	"$(INTDIR)\ToolDoc.obj"

"$(OUTDIR)\Tool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Tool - Win32 Release" || "$(CFG)" == "Tool - Win32 Debug"
SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Tool - Win32 Release"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\FormCommandView.h"\
	".\RenderView.h"\
	".\Tool.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\FormCommandView.h"\
	".\RenderView.h"\
	".\Tool.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ENDIF 

SOURCE=.\DlgAbout.cpp
DEP_CPP_DLGAB=\
	".\DlgAbout.h"\
	

"$(INTDIR)\DlgAbout.obj" : $(SOURCE) $(DEP_CPP_DLGAB) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


SOURCE=.\FormCommandView.cpp

!IF  "$(CFG)" == "Tool - Win32 Release"

DEP_CPP_FORMC=\
	".\ChildFrm.h"\
	".\FormCommandView.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\FormCommandView.obj" : $(SOURCE) $(DEP_CPP_FORMC) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

DEP_CPP_FORMC=\
	".\ChildFrm.h"\
	".\FormCommandView.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\FormCommandView.obj" : $(SOURCE) $(DEP_CPP_FORMC) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Tool.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


SOURCE=.\RenderView.cpp

!IF  "$(CFG)" == "Tool - Win32 Release"

DEP_CPP_RENDE=\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\RenderView.obj" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

DEP_CPP_RENDE=\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\RenderView.obj" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Tool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\Tool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Tool.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\Tool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Tool.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Tool.cpp

!IF  "$(CFG)" == "Tool - Win32 Release"

DEP_CPP_TOOL_=\
	".\ChildFrm.h"\
	".\DlgAbout.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\Tool.obj" : $(SOURCE) $(DEP_CPP_TOOL_) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ELSEIF  "$(CFG)" == "Tool - Win32 Debug"

DEP_CPP_TOOL_=\
	".\ChildFrm.h"\
	".\DlgAbout.h"\
	".\MainFrm.h"\
	".\RenderView.h"\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\Tool.obj" : $(SOURCE) $(DEP_CPP_TOOL_) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"


!ENDIF 

SOURCE=.\Tool.rc
DEP_RSC_TOOL_R=\
	".\res\Tool.ico"\
	".\res\Tool.rc2"\
	".\res\Toolbar.bmp"\
	".\res\ToolDoc.ico"\
	

"$(INTDIR)\Tool.res" : $(SOURCE) $(DEP_RSC_TOOL_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ToolDoc.cpp
DEP_CPP_TOOLD=\
	".\Tool.h"\
	".\ToolDoc.h"\
	

"$(INTDIR)\ToolDoc.obj" : $(SOURCE) $(DEP_CPP_TOOLD) "$(INTDIR)"\
 "$(INTDIR)\Tool.pch"



!ENDIF 

