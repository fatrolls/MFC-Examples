# Microsoft Developer Studio Generated NMAKE File, Based on KbdMac.dsp
!IF "$(CFG)" == ""
CFG=KbdMac - Win32 Debug
!MESSAGE No configuration specified. Defaulting to KbdMac - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "KbdMac - Win32 Debug" && "$(CFG)" !=\
 "KbdMac - Win32 Unicode Debug" && "$(CFG)" != "KbdMac - Win32 Release MinSize"\
 && "$(CFG)" != "KbdMac - Win32 Release MinDependency" && "$(CFG)" !=\
 "KbdMac - Win32 Unicode Release MinSize" && "$(CFG)" !=\
 "KbdMac - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "KbdMac.mak" CFG="KbdMac - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "KbdMac - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KbdMac - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KbdMac - Win32 Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KbdMac - Win32 Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KbdMac - Win32 Unicode Release MinSize" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "KbdMac - Win32 Unicode Release MinDependency" (based on\
 "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "KbdMac - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.ilk"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OUTDIR)\KbdMac.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /Fp"$(INTDIR)\KbdMac.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /debug /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" /pdbtype:sept 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\KbdMac.dll
InputPath=.\Debug\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.ilk"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OUTDIR)\KbdMac.pdb"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\KbdMac.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /debug /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" /pdbtype:sept 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\KbdMac.dll
InputPath=.\DebugU\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\KbdMac.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\KbdMac.dll
InputPath=.\ReleaseMinSize\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\KbdMac.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\KbdMac.dll
InputPath=.\ReleaseMinDependency\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\KbdMac.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\ReleaseUMinSize/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\KbdMac.dll
InputPath=.\ReleaseUMinSize\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ELSE 

ALL : "$(OUTDIR)\KbdMac.dll" "$(OutDir)\regsvr32.trg"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\KbdMac.obj"
	-@erase "$(INTDIR)\KbdMac.pch"
	-@erase "$(INTDIR)\KbdMac.res"
	-@erase "$(INTDIR)\KMAddIn.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\KbdMac.dll"
	-@erase "$(OUTDIR)\KbdMac.exp"
	-@erase "$(OUTDIR)\KbdMac.lib"
	-@erase "$(OutDir)\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL"\
 /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\KbdMac.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\ReleaseUMinDependency/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x809 /fo"$(INTDIR)\KbdMac.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\KbdMac.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\KbdMac.pdb" /machine:I386 /def:".\KbdMac.def"\
 /out:"$(OUTDIR)\KbdMac.dll" /implib:"$(OUTDIR)\KbdMac.lib" 
DEF_FILE= \
	".\KbdMac.def"
LINK32_OBJS= \
	"$(INTDIR)\KbdMac.obj" \
	"$(INTDIR)\KbdMac.res" \
	"$(INTDIR)\KMAddIn.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\KbdMac.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\KbdMac.dll
InputPath=.\ReleaseUMinDependency\KbdMac.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	

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


!IF "$(CFG)" == "KbdMac - Win32 Debug" || "$(CFG)" ==\
 "KbdMac - Win32 Unicode Debug" || "$(CFG)" == "KbdMac - Win32 Release MinSize"\
 || "$(CFG)" == "KbdMac - Win32 Release MinDependency" || "$(CFG)" ==\
 "KbdMac - Win32 Unicode Release MinSize" || "$(CFG)" ==\
 "KbdMac - Win32 Unicode Release MinDependency"
SOURCE=.\KbdMac.cpp

!IF  "$(CFG)" == "KbdMac - Win32 Debug"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h" ".\KbdMac_i.c"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Debug"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h" ".\KbdMac_i.c"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinSize"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h" ".\KbdMac_i.c"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinDependency"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac_i.c" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinSize"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h" ".\KbdMac_i.c"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinDependency"

DEP_CPP_KBDMA=\
	".\KbdMac.h"\
	".\KbdMac_i.c"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KbdMac.obj" : $(SOURCE) $(DEP_CPP_KBDMA) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h" ".\KbdMac_i.c"


!ENDIF 

SOURCE=.\KbdMac.idl

!IF  "$(CFG)" == "KbdMac - Win32 Debug"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Debug"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinSize"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinDependency"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinSize"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinDependency"

InputPath=.\KbdMac.idl

".\KbdMac.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /h "KbdMac.h" /iid "KbdMac_i.c" "KbdMac.idl"

!ENDIF 

SOURCE=.\KbdMac.rc
DEP_RSC_KBDMAC=\
	".\bmp00001.bmp"\
	".\KbdMac.tlb"\
	".\KMAddIn.rgs"\
	".\toolbar_.bmp"\
	

"$(INTDIR)\KbdMac.res" : $(SOURCE) $(DEP_RSC_KBDMAC) "$(INTDIR)" ".\KbdMac.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\KMAddIn.cpp

!IF  "$(CFG)" == "KbdMac - Win32 Debug"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Debug"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinSize"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinDependency"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinSize"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinDependency"

DEP_CPP_KMADD=\
	".\KbdMac.h"\
	".\KMAddIn.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\KMAddIn.obj" : $(SOURCE) $(DEP_CPP_KMADD) "$(INTDIR)"\
 "$(INTDIR)\KbdMac.pch" ".\KbdMac.h"


!ENDIF 

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "KbdMac - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\KbdMac.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\KbdMac.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\KbdMac.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\KbdMac.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\KbdMac.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "KbdMac - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT"\
 /Fp"$(INTDIR)\KbdMac.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\KbdMac.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

