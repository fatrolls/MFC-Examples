# Microsoft Developer Studio Generated NMAKE File, Based on saver.dsp
!IF "$(CFG)" == ""
CFG=Saver - Win32 Release
!MESSAGE No configuration specified.  Defaulting to Saver - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Saver - Win32 Release" && "$(CFG)" != "Saver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "saver.mak" CFG="Saver - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Saver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Saver - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Saver - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Saver.scr"

CLEAN : 
	-@erase "$(INTDIR)\Drawwnd.obj"
	-@erase "$(INTDIR)\Saver.obj"
	-@erase "$(INTDIR)\saver.pch"
	-@erase "$(INTDIR)\Saver.res"
	-@erase "$(INTDIR)\Saverdlg.obj"
	-@erase "$(INTDIR)\Saverwnd.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(OUTDIR)\Saver.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/saver.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Saver.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/saver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Saver.pdb" /machine:I386 /out:"$(OUTDIR)/Saver.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Drawwnd.obj" \
	"$(INTDIR)\Saver.obj" \
	"$(INTDIR)\Saver.res" \
	"$(INTDIR)\Saverdlg.obj" \
	"$(INTDIR)\Saverwnd.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\Saver.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Saver.scr"

CLEAN : 
	-@erase "$(INTDIR)\Drawwnd.obj"
	-@erase "$(INTDIR)\Saver.obj"
	-@erase "$(INTDIR)\saver.pch"
	-@erase "$(INTDIR)\Saver.res"
	-@erase "$(INTDIR)\Saverdlg.obj"
	-@erase "$(INTDIR)\Saverwnd.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Saver.ilk"
	-@erase "$(OUTDIR)\Saver.pdb"
	-@erase "$(OUTDIR)\Saver.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/saver.pch" /Yu"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Saver.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/saver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Saver.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Saver.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Drawwnd.obj" \
	"$(INTDIR)\Saver.obj" \
	"$(INTDIR)\Saver.res" \
	"$(INTDIR)\Saverdlg.obj" \
	"$(INTDIR)\Saverwnd.obj" \
	"$(INTDIR)\Stdafx.obj"

"$(OUTDIR)\Saver.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  


!IF "$(CFG)" == "Saver - Win32 Release" || "$(CFG)" == "Saver - Win32 Debug"
SOURCE=.\Drawwnd.cpp
DEP_CPP_DRAWW=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Drawwnd.obj" : $(SOURCE) $(DEP_CPP_DRAWW) "$(INTDIR)"\
 "$(INTDIR)\saver.pch"


SOURCE=.\Saver.cpp
DEP_CPP_SAVER=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	".\saverwnd.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saver.obj" : $(SOURCE) $(DEP_CPP_SAVER) "$(INTDIR)"\
 "$(INTDIR)\saver.pch"


SOURCE=.\Saver.rc
DEP_RSC_SAVER_=\
	".\res\cursor1.cur"\
	".\res\Saver.ico"\
	".\res\Saver.rc2"\
	

"$(INTDIR)\Saver.res" : $(SOURCE) $(DEP_RSC_SAVER_) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Saverdlg.cpp
DEP_CPP_SAVERD=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\Saverdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saverdlg.obj" : $(SOURCE) $(DEP_CPP_SAVERD) "$(INTDIR)"\
 "$(INTDIR)\saver.pch"


SOURCE=.\Saverwnd.cpp
DEP_CPP_SAVERW=\
	".\drawwnd.h"\
	".\Saver.h"\
	".\saverwnd.h"\
	".\stdafx.h"\
	

"$(INTDIR)\Saverwnd.obj" : $(SOURCE) $(DEP_CPP_SAVERW) "$(INTDIR)"\
 "$(INTDIR)\saver.pch"


SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Saver - Win32 Release"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\saver.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/saver.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Saver - Win32 Debug"


"$(INTDIR)\Stdafx.obj"	"$(INTDIR)\saver.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/saver.pch" /Yc"Stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\drawwnd.h
SOURCE=.\Saver.h
SOURCE=.\Saverdlg.h
SOURCE=.\saverwnd.h
SOURCE=.\stdafx.h
SOURCE=.\res\cursor1.cur
SOURCE=.\res\Saver.ico
SOURCE=.\res\Saver.rc2

!ENDIF 

