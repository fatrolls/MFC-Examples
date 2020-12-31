# Microsoft Developer Studio Generated NMAKE File, Based on MvTest.dsp
!IF "$(CFG)" == ""
CFG=MvTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MvTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MvTest - Win32 Release" && "$(CFG)" != "MvTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MvTest.mak" CFG="MvTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MvTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MvTest - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "MvTest - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MvTest.exe" "$(OUTDIR)\MvTest.tlb"

!ELSE 

ALL : "$(OUTDIR)\MvTest.exe" "$(OUTDIR)\MvTest.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrame1.obj"
	-@erase "$(INTDIR)\ChildFrame2.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MvTest.obj"
	-@erase "$(INTDIR)\MvTest.pch"
	-@erase "$(INTDIR)\MvTest.res"
	-@erase "$(INTDIR)\MvTest.tlb"
	-@erase "$(INTDIR)\MvTestDoc.obj"
	-@erase "$(INTDIR)\SdimvDocTemplate.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\View1.obj"
	-@erase "$(INTDIR)\View2.obj"
	-@erase "$(INTDIR)\View3.obj"
	-@erase "$(INTDIR)\View4.obj"
	-@erase "$(OUTDIR)\MvTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\MvTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MvTest.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MvTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\MvTest.pdb" /machine:I386 /out:"$(OUTDIR)\MvTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrame1.obj" \
	"$(INTDIR)\ChildFrame2.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MvTest.obj" \
	"$(INTDIR)\MvTest.res" \
	"$(INTDIR)\MvTestDoc.obj" \
	"$(INTDIR)\SdimvDocTemplate.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\View1.obj" \
	"$(INTDIR)\View2.obj" \
	"$(INTDIR)\View3.obj" \
	"$(INTDIR)\View4.obj"

"$(OUTDIR)\MvTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\MvTest.exe" "$(OUTDIR)\MvTest.tlb"

!ELSE 

ALL : "$(OUTDIR)\MvTest.exe" "$(OUTDIR)\MvTest.tlb"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrame1.obj"
	-@erase "$(INTDIR)\ChildFrame2.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MvTest.obj"
	-@erase "$(INTDIR)\MvTest.pch"
	-@erase "$(INTDIR)\MvTest.res"
	-@erase "$(INTDIR)\MvTest.tlb"
	-@erase "$(INTDIR)\MvTestDoc.obj"
	-@erase "$(INTDIR)\SdimvDocTemplate.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\View1.obj"
	-@erase "$(INTDIR)\View2.obj"
	-@erase "$(INTDIR)\View3.obj"
	-@erase "$(INTDIR)\View4.obj"
	-@erase "$(OUTDIR)\MvTest.exe"
	-@erase "$(OUTDIR)\MvTest.ilk"
	-@erase "$(OUTDIR)\MvTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\MvTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MvTest.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MvTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\MvTest.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MvTest.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrame1.obj" \
	"$(INTDIR)\ChildFrame2.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MvTest.obj" \
	"$(INTDIR)\MvTest.res" \
	"$(INTDIR)\MvTestDoc.obj" \
	"$(INTDIR)\SdimvDocTemplate.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\View1.obj" \
	"$(INTDIR)\View2.obj" \
	"$(INTDIR)\View3.obj" \
	"$(INTDIR)\View4.obj"

"$(OUTDIR)\MvTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "MvTest - Win32 Release" || "$(CFG)" == "MvTest - Win32 Debug"
SOURCE=.\ChildFrame1.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_CHILD=\
	".\ChildFrame1.h"\
	".\MvTest.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrame1.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_CHILD=\
	".\ChildFrame1.h"\
	".\MvTest.h"\
	

"$(INTDIR)\ChildFrame1.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\ChildFrame2.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_CHILDF=\
	".\ChildFrame2.h"\
	".\MvTest.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrame2.obj" : $(SOURCE) $(DEP_CPP_CHILDF) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_CHILDF=\
	".\ChildFrame2.h"\
	".\MvTest.h"\
	

"$(INTDIR)\ChildFrame2.obj" : $(SOURCE) $(DEP_CPP_CHILDF) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\MvTest.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\MvTest.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\MvTest.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_MVTES=\
	".\ChildFrame1.h"\
	".\ChildFrame2.h"\
	".\MainFrm.h"\
	".\MvTest.h"\
	".\MvTestDoc.h"\
	".\SdimvDocTemplate.h"\
	".\StdAfx.h"\
	".\View1.h"\
	".\View2.h"\
	".\View3.h"\
	".\View4.h"\
	

"$(INTDIR)\MvTest.obj" : $(SOURCE) $(DEP_CPP_MVTES) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_MVTES=\
	".\ChildFrame1.h"\
	".\ChildFrame2.h"\
	".\MainFrm.h"\
	".\MvTest.h"\
	".\MvTestDoc.h"\
	".\SdimvDocTemplate.h"\
	".\View1.h"\
	".\View2.h"\
	".\View3.h"\
	".\View4.h"\
	

"$(INTDIR)\MvTest.obj" : $(SOURCE) $(DEP_CPP_MVTES) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\MvTest.odl

!IF  "$(CFG)" == "MvTest - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\MvTest.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\MvTest.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\MvTest.tlb" /mktyplib203 /o\
 NUL /win32 

"$(OUTDIR)\MvTest.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MvTest.rc
DEP_RSC_MVTEST=\
	".\res\idr_mv2.ico"\
	".\res\idr_mv3.ico"\
	".\res\idr_mv4.ico"\
	".\res\idr_mvte.ico"\
	".\res\MvTest.ico"\
	".\res\MvTest.rc2"\
	".\res\Toolbar.bmp"\
	

!IF  "$(CFG)" == "MvTest - Win32 Release"


"$(INTDIR)\MvTest.res" : $(SOURCE) $(DEP_RSC_MVTEST) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MvTest.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"


"$(INTDIR)\MvTest.res" : $(SOURCE) $(DEP_RSC_MVTEST) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\MvTest.res" /i "Debug" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

SOURCE=.\MvTestDoc.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_MVTESTD=\
	".\MvTest.h"\
	".\MvTestDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MvTestDoc.obj" : $(SOURCE) $(DEP_CPP_MVTESTD) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_MVTESTD=\
	".\MvTest.h"\
	".\MvTestDoc.h"\
	

"$(INTDIR)\MvTestDoc.obj" : $(SOURCE) $(DEP_CPP_MVTESTD) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\SdimvDocTemplate.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_SDIMV=\
	".\SdimvDocTemplate.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\SdimvDocTemplate.obj" : $(SOURCE) $(DEP_CPP_SDIMV) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_SDIMV=\
	".\SdimvDocTemplate.h"\
	

"$(INTDIR)\SdimvDocTemplate.obj" : $(SOURCE) $(DEP_CPP_SDIMV) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MvTest - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\MvTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MvTest.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\MvTest.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MvTest.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\View1.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_VIEW1=\
	".\MvTest.h"\
	".\StdAfx.h"\
	".\View1.h"\
	

"$(INTDIR)\View1.obj" : $(SOURCE) $(DEP_CPP_VIEW1) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_VIEW1=\
	".\MvTest.h"\
	".\View1.h"\
	

"$(INTDIR)\View1.obj" : $(SOURCE) $(DEP_CPP_VIEW1) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\View2.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_VIEW2=\
	".\MvTest.h"\
	".\StdAfx.h"\
	".\View2.h"\
	

"$(INTDIR)\View2.obj" : $(SOURCE) $(DEP_CPP_VIEW2) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_VIEW2=\
	".\MvTest.h"\
	".\View2.h"\
	

"$(INTDIR)\View2.obj" : $(SOURCE) $(DEP_CPP_VIEW2) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\View3.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_VIEW3=\
	".\MvTest.h"\
	".\StdAfx.h"\
	".\View3.h"\
	

"$(INTDIR)\View3.obj" : $(SOURCE) $(DEP_CPP_VIEW3) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_VIEW3=\
	".\MvTest.h"\
	".\View3.h"\
	

"$(INTDIR)\View3.obj" : $(SOURCE) $(DEP_CPP_VIEW3) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 

SOURCE=.\View4.cpp

!IF  "$(CFG)" == "MvTest - Win32 Release"

DEP_CPP_VIEW4=\
	".\MvTest.h"\
	".\StdAfx.h"\
	".\View4.h"\
	

"$(INTDIR)\View4.obj" : $(SOURCE) $(DEP_CPP_VIEW4) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ELSEIF  "$(CFG)" == "MvTest - Win32 Debug"

DEP_CPP_VIEW4=\
	".\MvTest.h"\
	".\View4.h"\
	

"$(INTDIR)\View4.obj" : $(SOURCE) $(DEP_CPP_VIEW4) "$(INTDIR)"\
 "$(INTDIR)\MvTest.pch"


!ENDIF 


!ENDIF 

