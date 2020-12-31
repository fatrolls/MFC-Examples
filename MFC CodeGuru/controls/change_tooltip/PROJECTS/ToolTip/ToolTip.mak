# Microsoft Developer Studio Generated NMAKE File, Based on ToolTip.dsp
!IF "$(CFG)" == ""
CFG=ToolTip - Win32 Release
!MESSAGE No configuration specified. Defaulting to ToolTip - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ToolTip - Win32 Release" && "$(CFG)" !=\
 "ToolTip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ToolTip.mak" CFG="ToolTip - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ToolTip - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ToolTip - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ToolTip - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ToolTip.exe"

!ELSE 

ALL : "$(OUTDIR)\ToolTip.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChangeTTT.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ToolTip.obj"
	-@erase "$(INTDIR)\ToolTip.pch"
	-@erase "$(INTDIR)\ToolTip.res"
	-@erase "$(INTDIR)\ToolTipDoc.obj"
	-@erase "$(INTDIR)\ToolTipView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ToolTip.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ToolTip.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ToolTip.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ToolTip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\ToolTip.pdb" /machine:I386 /out:"$(OUTDIR)\ToolTip.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChangeTTT.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ToolTip.obj" \
	"$(INTDIR)\ToolTip.res" \
	"$(INTDIR)\ToolTipDoc.obj" \
	"$(INTDIR)\ToolTipView.obj"

"$(OUTDIR)\ToolTip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ToolTip.exe"

!ELSE 

ALL : "$(OUTDIR)\ToolTip.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChangeTTT.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ToolTip.obj"
	-@erase "$(INTDIR)\ToolTip.pch"
	-@erase "$(INTDIR)\ToolTip.res"
	-@erase "$(INTDIR)\ToolTipDoc.obj"
	-@erase "$(INTDIR)\ToolTipView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ToolTip.exe"
	-@erase "$(OUTDIR)\ToolTip.ilk"
	-@erase "$(OUTDIR)\ToolTip.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ToolTip.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ToolTip.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ToolTip.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\ToolTip.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ToolTip.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChangeTTT.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ToolTip.obj" \
	"$(INTDIR)\ToolTip.res" \
	"$(INTDIR)\ToolTipDoc.obj" \
	"$(INTDIR)\ToolTipView.obj"

"$(OUTDIR)\ToolTip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "ToolTip - Win32 Release" || "$(CFG)" ==\
 "ToolTip - Win32 Debug"
SOURCE=.\ChangeTTT.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_CHANG=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ChangeTTT.obj" : $(SOURCE) $(DEP_CPP_CHANG) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_CHANG=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ChangeTTT.obj" : $(SOURCE) $(DEP_CPP_CHANG) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_CHILD=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_MAINF=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_MAINF=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ToolTip - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ToolTip.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ToolTip.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ToolTip.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ToolTip.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ToolTip.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_TOOLT=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTip.obj" : $(SOURCE) $(DEP_CPP_TOOLT) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_TOOLT=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTip.obj" : $(SOURCE) $(DEP_CPP_TOOLT) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 

SOURCE=.\ToolTip.rc
DEP_RSC_TOOLTI=\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	".\res\ToolTip.ico"\
	".\res\ToolTip.rc2"\
	".\res\ToolTipDoc.ico"\
	

"$(INTDIR)\ToolTip.res" : $(SOURCE) $(DEP_RSC_TOOLTI) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ToolTipDoc.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_TOOLTIP=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTipDoc.obj" : $(SOURCE) $(DEP_CPP_TOOLTIP) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_TOOLTIP=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTipDoc.obj" : $(SOURCE) $(DEP_CPP_TOOLTIP) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 

SOURCE=.\ToolTipView.cpp

!IF  "$(CFG)" == "ToolTip - Win32 Release"

DEP_CPP_TOOLTIPV=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTipView.obj" : $(SOURCE) $(DEP_CPP_TOOLTIPV) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ELSEIF  "$(CFG)" == "ToolTip - Win32 Debug"

DEP_CPP_TOOLTIPV=\
	".\ChangeTTT.h"\
	".\ChildFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\ToolTip.h"\
	".\ToolTipDoc.h"\
	".\ToolTipView.h"\
	

"$(INTDIR)\ToolTipView.obj" : $(SOURCE) $(DEP_CPP_TOOLTIPV) "$(INTDIR)"\
 "$(INTDIR)\ToolTip.pch"


!ENDIF 


!ENDIF 

