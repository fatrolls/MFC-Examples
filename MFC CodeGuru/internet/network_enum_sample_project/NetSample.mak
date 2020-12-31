# Microsoft Developer Studio Generated NMAKE File, Based on NetSample.dsp
!IF "$(CFG)" == ""
CFG=NetSample - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NetSample - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NetSample - Win32 Release" && "$(CFG)" !=\
 "NetSample - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetSample.mak" CFG="NetSample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetSample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NetSample - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "NetSample - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NetSample.exe"

!ELSE 

ALL : "$(OUTDIR)\NetSample.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\NetSample.obj"
	-@erase "$(INTDIR)\NetSample.pch"
	-@erase "$(INTDIR)\NetSample.res"
	-@erase "$(INTDIR)\NetSampleDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\NetSample.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\NetSample.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\NetSample.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\NetSample.pdb" /machine:I386 /out:"$(OUTDIR)\NetSample.exe" 
LINK32_OBJS= \
	"$(INTDIR)\NetSample.obj" \
	"$(INTDIR)\NetSample.res" \
	"$(INTDIR)\NetSampleDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\NetSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NetSample - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NetSample.exe"

!ELSE 

ALL : "$(OUTDIR)\NetSample.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\NetSample.obj"
	-@erase "$(INTDIR)\NetSample.pch"
	-@erase "$(INTDIR)\NetSample.res"
	-@erase "$(INTDIR)\NetSampleDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\NetSample.exe"
	-@erase "$(OUTDIR)\NetSample.ilk"
	-@erase "$(OUTDIR)\NetSample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\NetSample.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\NetSample.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NetSample.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\NetSample.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\NetSample.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\NetSample.obj" \
	"$(INTDIR)\NetSample.res" \
	"$(INTDIR)\NetSampleDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\NetSample.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "NetSample - Win32 Release" || "$(CFG)" ==\
 "NetSample - Win32 Debug"
SOURCE=.\NetSample.cpp
DEP_CPP_NETSA=\
	".\NetSample.h"\
	".\NetSampleDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NetSample.obj" : $(SOURCE) $(DEP_CPP_NETSA) "$(INTDIR)"\
 "$(INTDIR)\NetSample.pch"


SOURCE=.\NetSample.rc
DEP_RSC_NETSAM=\
	".\res\NetSample.ico"\
	".\res\NetSample.rc2"\
	

"$(INTDIR)\NetSample.res" : $(SOURCE) $(DEP_RSC_NETSAM) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\NetSampleDlg.cpp
DEP_CPP_NETSAMP=\
	".\NetSample.h"\
	".\NetSampleDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\NetSampleDlg.obj" : $(SOURCE) $(DEP_CPP_NETSAMP) "$(INTDIR)"\
 "$(INTDIR)\NetSample.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "NetSample - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /Fp"$(INTDIR)\NetSample.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NetSample.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "NetSample - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\NetSample.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NetSample.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

