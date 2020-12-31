# Microsoft Developer Studio Generated NMAKE File, Based on ColorEdit.dsp
!IF "$(CFG)" == ""
CFG=ColorEdit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ColorEdit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ColorEdit - Win32 Release" && "$(CFG)" !=\
 "ColorEdit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ColorEdit.mak" CFG="ColorEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ColorEdit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ColorEdit - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ColorEdit.exe" "$(OUTDIR)\ColorEdit.tlb"

!ELSE 

ALL : "$(OUTDIR)\ColorEdit.exe" "$(OUTDIR)\ColorEdit.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ClockStatus.obj"
	-@erase "$(INTDIR)\ColorEdit.obj"
	-@erase "$(INTDIR)\ColorEdit.pch"
	-@erase "$(INTDIR)\ColorEdit.res"
	-@erase "$(INTDIR)\ColorEdit.tlb"
	-@erase "$(INTDIR)\ColorEditDoc.obj"
	-@erase "$(INTDIR)\ColorEditView.obj"
	-@erase "$(INTDIR)\ColorString.obj"
	-@erase "$(INTDIR)\CreditStatic.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\splash255.obj"
	-@erase "$(INTDIR)\StatusMessage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringEx.obj"
	-@erase "$(INTDIR)\ToolBarEx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ColorEdit.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\ColorEdit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ColorEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ColorEdit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\ColorEdit.pdb" /machine:I386 /out:"$(OUTDIR)\ColorEdit.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ClockStatus.obj" \
	"$(INTDIR)\ColorEdit.obj" \
	"$(INTDIR)\ColorEdit.res" \
	"$(INTDIR)\ColorEditDoc.obj" \
	"$(INTDIR)\ColorEditView.obj" \
	"$(INTDIR)\ColorString.obj" \
	"$(INTDIR)\CreditStatic.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ProgressBar.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\splash255.obj" \
	"$(INTDIR)\StatusMessage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringEx.obj" \
	"$(INTDIR)\ToolBarEx.obj"

"$(OUTDIR)\ColorEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ColorEdit.exe" "$(OUTDIR)\ColorEdit.tlb"

!ELSE 

ALL : "$(OUTDIR)\ColorEdit.exe" "$(OUTDIR)\ColorEdit.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ClockStatus.obj"
	-@erase "$(INTDIR)\ColorEdit.obj"
	-@erase "$(INTDIR)\ColorEdit.pch"
	-@erase "$(INTDIR)\ColorEdit.res"
	-@erase "$(INTDIR)\ColorEdit.tlb"
	-@erase "$(INTDIR)\ColorEditDoc.obj"
	-@erase "$(INTDIR)\ColorEditView.obj"
	-@erase "$(INTDIR)\ColorString.obj"
	-@erase "$(INTDIR)\CreditStatic.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ProgressBar.obj"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\Search.obj"
	-@erase "$(INTDIR)\splash255.obj"
	-@erase "$(INTDIR)\StatusMessage.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringEx.obj"
	-@erase "$(INTDIR)\ToolBarEx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ColorEdit.exe"
	-@erase "$(OUTDIR)\ColorEdit.ilk"
	-@erase "$(OUTDIR)\ColorEdit.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\ColorEdit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ColorEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ColorEdit.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\ColorEdit.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\ColorEdit.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ClockStatus.obj" \
	"$(INTDIR)\ColorEdit.obj" \
	"$(INTDIR)\ColorEdit.res" \
	"$(INTDIR)\ColorEditDoc.obj" \
	"$(INTDIR)\ColorEditView.obj" \
	"$(INTDIR)\ColorString.obj" \
	"$(INTDIR)\CreditStatic.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ProgressBar.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\Search.obj" \
	"$(INTDIR)\splash255.obj" \
	"$(INTDIR)\StatusMessage.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringEx.obj" \
	"$(INTDIR)\ToolBarEx.obj"

"$(OUTDIR)\ColorEdit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "ColorEdit - Win32 Release" || "$(CFG)" ==\
 "ColorEdit - Win32 Debug"
SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\ClockStatusBar.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\ClockStatusBar.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\ClockStatus.cpp
DEP_CPP_CLOCK=\
	".\ClockStatusBar.h"\
	

"$(INTDIR)\ClockStatus.obj" : $(SOURCE) $(DEP_CPP_CLOCK) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


SOURCE=.\ColorEdit.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_COLOR=\
	".\ChildFrm.h"\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\MainFrm.h"\
	".\memdc.h"\
	".\splash255.h"\
	".\StringEx.h"\
	".\ToolBarEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEdit.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_COLOR=\
	".\ChildFrm.h"\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\MainFrm.h"\
	".\memdc.h"\
	".\splash255.h"\
	".\StringEx.h"\
	".\ToolBarEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEdit.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\ColorEdit.odl

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\ColorEdit.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\ColorEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\ColorEdit.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\ColorEdit.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ColorEdit.rc
DEP_RSC_COLORE=\
	".\res\ColorEdit.ico"\
	".\res\ColorEdit.rc2"\
	".\res\ColorEditDoc.ico"\
	".\res\splash.bmp"\
	".\res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "ColorEdit - Win32 Release"


"$(INTDIR)\ColorEdit.res" : $(SOURCE) $(DEP_RSC_COLORE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\ColorEdit.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"


"$(INTDIR)\ColorEdit.res" : $(SOURCE) $(DEP_RSC_COLORE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\ColorEdit.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\ColorEditDoc.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_COLORED=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorString.h"\
	".\ProgressBar.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEditDoc.obj" : $(SOURCE) $(DEP_CPP_COLORED) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_COLORED=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorString.h"\
	".\ProgressBar.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEditDoc.obj" : $(SOURCE) $(DEP_CPP_COLORED) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\ColorEditView.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_COLOREDI=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\memdc.h"\
	".\RegExp.h"\
	".\Search.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEditView.obj" : $(SOURCE) $(DEP_CPP_COLOREDI) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_COLOREDI=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\memdc.h"\
	".\RegExp.h"\
	".\Search.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\ColorEditView.obj" : $(SOURCE) $(DEP_CPP_COLOREDI) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\ColorString.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_COLORS=\
	".\ClockStatusBar.h"\
	".\ColorString.h"\
	".\StringEx.h"\
	

"$(INTDIR)\ColorString.obj" : $(SOURCE) $(DEP_CPP_COLORS) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_COLORS=\
	".\ClockStatusBar.h"\
	".\ColorString.h"\
	".\StringEx.h"\
	

"$(INTDIR)\ColorString.obj" : $(SOURCE) $(DEP_CPP_COLORS) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\CreditStatic.cpp
DEP_CPP_CREDI=\
	".\ClockStatusBar.h"\
	

"$(INTDIR)\CreditStatic.obj" : $(SOURCE) $(DEP_CPP_CREDI) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\ClockStatusBar.h"\
	".\MainFrm.h"\
	".\ToolBarEx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


SOURCE=.\ProgressBar.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_PROGR=\
	".\ClockStatusBar.h"\
	".\ProgressBar.h"\
	

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_PROGR=\
	".\ClockStatusBar.h"\
	".\ProgressBar.h"\
	

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\RegExp.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_REGEX=\
	".\ClockStatusBar.h"\
	".\RegExp.h"\
	".\StringEx.h"\
	

"$(INTDIR)\RegExp.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_REGEX=\
	".\ClockStatusBar.h"\
	".\RegExp.h"\
	".\StringEx.h"\
	

"$(INTDIR)\RegExp.obj" : $(SOURCE) $(DEP_CPP_REGEX) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\Search.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_SEARC=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\memdc.h"\
	".\RegExp.h"\
	".\Search.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\Search.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_SEARC=\
	".\ClockStatusBar.h"\
	".\ColorEditDoc.h"\
	".\ColorEditView.h"\
	".\ColorString.h"\
	".\memdc.h"\
	".\RegExp.h"\
	".\Search.h"\
	".\StringEx.h"\
	".\undo.h"\
	

"$(INTDIR)\Search.obj" : $(SOURCE) $(DEP_CPP_SEARC) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\splash255.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_SPLAS=\
	".\ClockStatusBar.h"\
	".\splash255.h"\
	

"$(INTDIR)\splash255.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_SPLAS=\
	".\ClockStatusBar.h"\
	".\splash255.h"\
	

"$(INTDIR)\splash255.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\StatusMessage.cpp
DEP_CPP_STATU=\
	".\ClockStatusBar.h"\
	".\StatusMessage.h"\
	

"$(INTDIR)\StatusMessage.obj" : $(SOURCE) $(DEP_CPP_STATU) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_STDAF=\
	".\ClockStatusBar.h"\
	".\ColorEdit.h"\
	".\CreditStatic.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\ColorEdit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ColorEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_STDAF=\
	".\ClockStatusBar.h"\
	".\ColorEdit.h"\
	".\CreditStatic.h"\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\ColorEdit.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ColorEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StringEx.cpp

!IF  "$(CFG)" == "ColorEdit - Win32 Release"

DEP_CPP_STRIN=\
	".\ClockStatusBar.h"\
	".\StringEx.h"\
	

"$(INTDIR)\StringEx.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ELSEIF  "$(CFG)" == "ColorEdit - Win32 Debug"

DEP_CPP_STRIN=\
	".\ClockStatusBar.h"\
	".\StringEx.h"\
	

"$(INTDIR)\StringEx.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"


!ENDIF 

SOURCE=.\ToolBarEx.cpp
DEP_CPP_TOOLB=\
	".\ClockStatusBar.h"\
	".\ToolBarEx.h"\
	

"$(INTDIR)\ToolBarEx.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\ColorEdit.pch"



!ENDIF 

