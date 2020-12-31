# Microsoft Developer Studio Generated NMAKE File, Based on dynclass.dsp
!IF "$(CFG)" == ""
CFG=dynclass - Win32 Debug
!MESSAGE No configuration specified. Defaulting to dynclass - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dynclass - Win32 Release" && "$(CFG)" !=\
 "dynclass - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dynclass.mak" CFG="dynclass - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dynclass - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dynclass - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "dynclass - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dynclass.dll"

!ELSE 

ALL : "$(OUTDIR)\dynclass.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dynclass.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\dynclass.dll"
	-@erase "$(OUTDIR)\dynclass.exp"
	-@erase "$(OUTDIR)\dynclass.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\dynclass.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dynclass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\dynclass.pdb" /machine:I386 /def:".\dynclass.def"\
 /out:"$(OUTDIR)\dynclass.dll" /implib:"$(OUTDIR)\dynclass.lib" 
DEF_FILE= \
	".\dynclass.def"
LINK32_OBJS= \
	"$(INTDIR)\dynclass.obj"

"$(OUTDIR)\dynclass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dynclass - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dynclass.dll"

!ELSE 

ALL : "$(OUTDIR)\dynclass.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dynclass.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\dynclass.dll"
	-@erase "$(OUTDIR)\dynclass.exp"
	-@erase "$(OUTDIR)\dynclass.ilk"
	-@erase "$(OUTDIR)\dynclass.lib"
	-@erase "$(OUTDIR)\dynclass.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_DLL" /Fp"$(INTDIR)\dynclass.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dynclass.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\dynclass.pdb" /debug /machine:I386 /def:".\dynclass.def"\
 /out:"$(OUTDIR)\dynclass.dll" /implib:"$(OUTDIR)\dynclass.lib" /pdbtype:sept 
DEF_FILE= \
	".\dynclass.def"
LINK32_OBJS= \
	"$(INTDIR)\dynclass.obj"

"$(OUTDIR)\dynclass.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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


!IF "$(CFG)" == "dynclass - Win32 Release" || "$(CFG)" ==\
 "dynclass - Win32 Debug"
SOURCE=.\dynclass.cpp
DEP_CPP_DYNCL=\
	".\dynclass.h"\
	

"$(INTDIR)\dynclass.obj" : $(SOURCE) $(DEP_CPP_DYNCL) "$(INTDIR)"



!ENDIF 

