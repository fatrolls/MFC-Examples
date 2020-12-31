# Microsoft Developer Studio Generated NMAKE File, Based on TurboDLL.dsp
!IF "$(CFG)" == ""
CFG=TurboDLL - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TurboDLL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TurboDLL - Win32 Release" && "$(CFG)" != "TurboDLL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TurboDLL.mak" CFG="TurboDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TurboDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TurboDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TurboDLL - Win32 Release"

OUTDIR=.\..\..\lib\release
INTDIR=.\..\..\temp\sdk\TurboDLL\Release

ALL : "..\..\bin\release\TurboDLL.dll"


CLEAN :
	-@erase "$(INTDIR)\PaneColInfo.obj"
	-@erase "$(INTDIR)\PaneInfo.obj"
	-@erase "$(INTDIR)\PaneRowInfo.obj"
	-@erase "$(INTDIR)\SplitterCtrl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TLCDragWnd.obj"
	-@erase "$(INTDIR)\TLCDropWnd.obj"
	-@erase "$(INTDIR)\TLHDragWnd.obj"
	-@erase "$(INTDIR)\TLHDropWnd.obj"
	-@erase "$(INTDIR)\TreeListColumnInfo.obj"
	-@erase "$(INTDIR)\TreeListComboCtrl.obj"
	-@erase "$(INTDIR)\TreeListCtrl.obj"
	-@erase "$(INTDIR)\TreeListDC.obj"
	-@erase "$(INTDIR)\TreeListEditCtrl.obj"
	-@erase "$(INTDIR)\TreeListHeaderCtrl.obj"
	-@erase "$(INTDIR)\TreeListItem.obj"
	-@erase "$(INTDIR)\TreeListStaticCtrl.obj"
	-@erase "$(INTDIR)\TreeListTipCtrl.obj"
	-@erase "$(INTDIR)\TurboDLL.obj"
	-@erase "$(INTDIR)\TurboDLL.pch"
	-@erase "$(INTDIR)\TurboDLL.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TurboDLL.exp"
	-@erase "$(OUTDIR)\TurboDLL.lib"
	-@erase "..\..\bin\release\TurboDLL.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\TurboDLL.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\TurboDLL.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TurboDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\TurboDLL.pdb" /machine:I386 /def:".\TurboDLL.def" /out:"..\..\bin\release/TurboDLL.dll" /implib:"$(OUTDIR)\TurboDLL.lib" 
DEF_FILE= \
	".\TurboDLL.def"
LINK32_OBJS= \
	"$(INTDIR)\PaneColInfo.obj" \
	"$(INTDIR)\PaneInfo.obj" \
	"$(INTDIR)\PaneRowInfo.obj" \
	"$(INTDIR)\SplitterCtrl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TLCDragWnd.obj" \
	"$(INTDIR)\TLCDropWnd.obj" \
	"$(INTDIR)\TLHDragWnd.obj" \
	"$(INTDIR)\TLHDropWnd.obj" \
	"$(INTDIR)\TreeListColumnInfo.obj" \
	"$(INTDIR)\TreeListComboCtrl.obj" \
	"$(INTDIR)\TreeListCtrl.obj" \
	"$(INTDIR)\TreeListDC.obj" \
	"$(INTDIR)\TreeListEditCtrl.obj" \
	"$(INTDIR)\TreeListHeaderCtrl.obj" \
	"$(INTDIR)\TreeListItem.obj" \
	"$(INTDIR)\TreeListStaticCtrl.obj" \
	"$(INTDIR)\TreeListTipCtrl.obj" \
	"$(INTDIR)\TurboDLL.obj" \
	"$(INTDIR)\TurboDLL.res"

"..\..\bin\release\TurboDLL.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "..\..\bin\release\TurboDLL.dll"
   @echo off
	@copy ..\..\bin\release\TurboDLL.* ..\..\test\bin\release
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "TurboDLL - Win32 Debug"

OUTDIR=.\..\..\lib\debug
INTDIR=.\..\..\temp\sdk\TurboDLL\Debug

ALL : "..\..\bin\debug\TurboDLLD.dll"


CLEAN :
	-@erase "$(INTDIR)\PaneColInfo.obj"
	-@erase "$(INTDIR)\PaneInfo.obj"
	-@erase "$(INTDIR)\PaneRowInfo.obj"
	-@erase "$(INTDIR)\SplitterCtrl.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TLCDragWnd.obj"
	-@erase "$(INTDIR)\TLCDropWnd.obj"
	-@erase "$(INTDIR)\TLHDragWnd.obj"
	-@erase "$(INTDIR)\TLHDropWnd.obj"
	-@erase "$(INTDIR)\TreeListColumnInfo.obj"
	-@erase "$(INTDIR)\TreeListComboCtrl.obj"
	-@erase "$(INTDIR)\TreeListCtrl.obj"
	-@erase "$(INTDIR)\TreeListDC.obj"
	-@erase "$(INTDIR)\TreeListEditCtrl.obj"
	-@erase "$(INTDIR)\TreeListHeaderCtrl.obj"
	-@erase "$(INTDIR)\TreeListItem.obj"
	-@erase "$(INTDIR)\TreeListStaticCtrl.obj"
	-@erase "$(INTDIR)\TreeListTipCtrl.obj"
	-@erase "$(INTDIR)\TurboDLL.obj"
	-@erase "$(INTDIR)\TurboDLL.pch"
	-@erase "$(INTDIR)\TurboDLL.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TurboDLLD.exp"
	-@erase "$(OUTDIR)\TurboDLLD.lib"
	-@erase "$(OUTDIR)\TurboDLLD.pdb"
	-@erase "..\..\bin\debug\TurboDLLD.dll"
	-@erase "..\..\bin\debug\TurboDLLD.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\TurboDLL.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\TurboDLL.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TurboDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\TurboDLLD.pdb" /debug /machine:I386 /def:".\TurboDLLD.def" /out:"..\..\bin\debug/TurboDLLD.dll" /implib:"$(OUTDIR)\TurboDLLD.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\PaneColInfo.obj" \
	"$(INTDIR)\PaneInfo.obj" \
	"$(INTDIR)\PaneRowInfo.obj" \
	"$(INTDIR)\SplitterCtrl.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TLCDragWnd.obj" \
	"$(INTDIR)\TLCDropWnd.obj" \
	"$(INTDIR)\TLHDragWnd.obj" \
	"$(INTDIR)\TLHDropWnd.obj" \
	"$(INTDIR)\TreeListColumnInfo.obj" \
	"$(INTDIR)\TreeListComboCtrl.obj" \
	"$(INTDIR)\TreeListCtrl.obj" \
	"$(INTDIR)\TreeListDC.obj" \
	"$(INTDIR)\TreeListEditCtrl.obj" \
	"$(INTDIR)\TreeListHeaderCtrl.obj" \
	"$(INTDIR)\TreeListItem.obj" \
	"$(INTDIR)\TreeListStaticCtrl.obj" \
	"$(INTDIR)\TreeListTipCtrl.obj" \
	"$(INTDIR)\TurboDLL.obj" \
	"$(INTDIR)\TurboDLL.res"

"..\..\bin\debug\TurboDLLD.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "..\..\bin\debug\TurboDLLD.dll"
   @echo off
	@copy ..\..\bin\debug\TurboDLLD.* ..\..\test\bin\debug
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TurboDLL.dep")
!INCLUDE "TurboDLL.dep"
!ELSE 
!MESSAGE Warning: cannot find "TurboDLL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TurboDLL - Win32 Release" || "$(CFG)" == "TurboDLL - Win32 Debug"
SOURCE=.\PaneColInfo.cpp

"$(INTDIR)\PaneColInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\PaneInfo.cpp

"$(INTDIR)\PaneInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\PaneRowInfo.cpp

"$(INTDIR)\PaneRowInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\SplitterCtrl.cpp

"$(INTDIR)\SplitterCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TurboDLL - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\TurboDLL.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TurboDLL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TurboDLL - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)\TurboDLL.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TurboDLL.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TLCDragWnd.cpp

"$(INTDIR)\TLCDragWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TLCDropWnd.cpp

"$(INTDIR)\TLCDropWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TLHDragWnd.cpp

"$(INTDIR)\TLHDragWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TLHDropWnd.cpp

"$(INTDIR)\TLHDropWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListColumnInfo.cpp

"$(INTDIR)\TreeListColumnInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListComboCtrl.cpp

"$(INTDIR)\TreeListComboCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListCtrl.cpp

"$(INTDIR)\TreeListCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListDC.cpp

"$(INTDIR)\TreeListDC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListEditCtrl.cpp

"$(INTDIR)\TreeListEditCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListHeaderCtrl.cpp

"$(INTDIR)\TreeListHeaderCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListItem.cpp

"$(INTDIR)\TreeListItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListStaticCtrl.cpp

"$(INTDIR)\TreeListStaticCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TreeListTipCtrl.cpp

"$(INTDIR)\TreeListTipCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TurboDLL.cpp

"$(INTDIR)\TurboDLL.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TurboDLL.pch"


SOURCE=.\TurboDLL.rc

"$(INTDIR)\TurboDLL.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

