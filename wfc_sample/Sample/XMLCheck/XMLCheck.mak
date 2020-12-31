# Microsoft Developer Studio Generated NMAKE File, Based on XMLCheck.dsp
!IF "$(CFG)" == ""
CFG=XMLCheck - Win32 Debug
!MESSAGE No configuration specified. Defaulting to XMLCheck - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "XMLCheck - Win32 Release" && "$(CFG)" != "XMLCheck - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMLCheck.mak" CFG="XMLCheck - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLCheck - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "XMLCheck - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "XMLCheck - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "c:\winnt\system32\XMLCheck.exe"

!ELSE 

ALL : "WFC - Win32 Release" "c:\winnt\system32\XMLCheck.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"WFC - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\check_xml_file.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "c:\winnt\system32\XMLCheck.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\XMLCheck.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /EHc /TP /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLCheck.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\XMLCheck.pdb" /machine:I386 /out:"c:\winnt\system32\XMLCheck.exe" 
LINK32_OBJS= \
	"$(INTDIR)\check_xml_file.obj" \
	"$(INTDIR)\main.obj" \
	"..\..\LIB\WFC.lib"

"c:\winnt\system32\XMLCheck.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "XMLCheck - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\XMLCheck.exe"

!ELSE 

ALL : "WFC - Win32 Debug" "$(OUTDIR)\XMLCheck.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"WFC - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\check_xml_file.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\XMLCheck.exe"
	-@erase "$(OUTDIR)\XMLCheck.ilk"
	-@erase "$(OUTDIR)\XMLCheck.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\XMLCheck.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /EHa /EHc /TP /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLCheck.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\XMLCheck.pdb" /debug /machine:I386 /out:"$(OUTDIR)\XMLCheck.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\check_xml_file.obj" \
	"$(INTDIR)\main.obj" \
	"..\..\LIB\DebugBuildOfWFC.lib"

"$(OUTDIR)\XMLCheck.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("XMLCheck.dep")
!INCLUDE "XMLCheck.dep"
!ELSE 
!MESSAGE Warning: cannot find "XMLCheck.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "XMLCheck - Win32 Release" || "$(CFG)" == "XMLCheck - Win32 Debug"

!IF  "$(CFG)" == "XMLCheck - Win32 Release"

"WFC - Win32 Release" : 
   cd "\WFC\LIB"
   $(MAKE) /$(MAKEFLAGS) /F .\WFC.mak CFG="WFC - Win32 Release" 
   cd "..\Sample\XMLCheck"

"WFC - Win32 ReleaseCLEAN" : 
   cd "\WFC\LIB"
   $(MAKE) /$(MAKEFLAGS) /F .\WFC.mak CFG="WFC - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Sample\XMLCheck"

!ELSEIF  "$(CFG)" == "XMLCheck - Win32 Debug"

"WFC - Win32 Debug" : 
   cd "\WFC\LIB"
   $(MAKE) /$(MAKEFLAGS) /F .\WFC.mak CFG="WFC - Win32 Debug" 
   cd "..\Sample\XMLCheck"

"WFC - Win32 DebugCLEAN" : 
   cd "\WFC\LIB"
   $(MAKE) /$(MAKEFLAGS) /F .\WFC.mak CFG="WFC - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Sample\XMLCheck"

!ENDIF 

SOURCE=.\check_xml_file.cpp

"$(INTDIR)\check_xml_file.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

