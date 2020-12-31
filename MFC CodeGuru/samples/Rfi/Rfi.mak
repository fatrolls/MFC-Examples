# Microsoft Developer Studio Generated NMAKE File, Based on Rfi.dsp
!IF "$(CFG)" == ""
CFG=Rfi - Win32 Release
!MESSAGE No configuration specified. Defaulting to Rfi - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "Rfi - Win32 Release" && "$(CFG)" != "Rfi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Rfi.mak" CFG="Rfi - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Rfi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Rfi - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Rfi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Rfi.exe"

!ELSE 

ALL : "$(OUTDIR)\Rfi.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddRepeatersDlg.obj"
	-@erase "$(INTDIR)\CompleteSet.obj"
	-@erase "$(INTDIR)\DeleteRepeatersDlg.obj"
	-@erase "$(INTDIR)\EditRepeaterDlg.obj"
	-@erase "$(INTDIR)\lbctrl.obj"
	-@erase "$(INTDIR)\ntray.obj"
	-@erase "$(INTDIR)\Rfi.obj"
	-@erase "$(INTDIR)\Rfi.pch"
	-@erase "$(INTDIR)\Rfi.res"
	-@erase "$(INTDIR)\RfiDlg.obj"
	-@erase "$(INTDIR)\Splash1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Rfi.exe"
	-@erase "$(OUTDIR)\Rfi.ilk"
	-@erase "$(OUTDIR)\Rfi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\Rfi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Rfi.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rfi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Rfi.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Rfi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddRepeatersDlg.obj" \
	"$(INTDIR)\CompleteSet.obj" \
	"$(INTDIR)\DeleteRepeatersDlg.obj" \
	"$(INTDIR)\EditRepeaterDlg.obj" \
	"$(INTDIR)\lbctrl.obj" \
	"$(INTDIR)\ntray.obj" \
	"$(INTDIR)\Rfi.obj" \
	"$(INTDIR)\Rfi.res" \
	"$(INTDIR)\RfiDlg.obj" \
	"$(INTDIR)\Splash1.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Rfi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Rfi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Rfi.exe"

!ELSE 

ALL : "$(OUTDIR)\Rfi.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AddRepeatersDlg.obj"
	-@erase "$(INTDIR)\CompleteSet.obj"
	-@erase "$(INTDIR)\DeleteRepeatersDlg.obj"
	-@erase "$(INTDIR)\EditRepeaterDlg.obj"
	-@erase "$(INTDIR)\lbctrl.obj"
	-@erase "$(INTDIR)\ntray.obj"
	-@erase "$(INTDIR)\Rfi.obj"
	-@erase "$(INTDIR)\Rfi.pch"
	-@erase "$(INTDIR)\Rfi.res"
	-@erase "$(INTDIR)\RfiDlg.obj"
	-@erase "$(INTDIR)\Splash1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Rfi.exe"
	-@erase "$(OUTDIR)\Rfi.ilk"
	-@erase "$(OUTDIR)\Rfi.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\Rfi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Rfi.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Rfi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\Rfi.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Rfi.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AddRepeatersDlg.obj" \
	"$(INTDIR)\CompleteSet.obj" \
	"$(INTDIR)\DeleteRepeatersDlg.obj" \
	"$(INTDIR)\EditRepeaterDlg.obj" \
	"$(INTDIR)\lbctrl.obj" \
	"$(INTDIR)\ntray.obj" \
	"$(INTDIR)\Rfi.obj" \
	"$(INTDIR)\Rfi.res" \
	"$(INTDIR)\RfiDlg.obj" \
	"$(INTDIR)\Splash1.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Rfi.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Rfi - Win32 Release" || "$(CFG)" == "Rfi - Win32 Debug"
SOURCE=.\AddRepeatersDlg.cpp
DEP_CPP_ADDRE=\
	".\AddRepeatersDlg.h"\
	".\CompleteSet.h"\
	".\Rfi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AddRepeatersDlg.obj" : $(SOURCE) $(DEP_CPP_ADDRE) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\CompleteSet.cpp
DEP_CPP_COMPL=\
	".\CompleteSet.h"\
	".\Rfi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\CompleteSet.obj" : $(SOURCE) $(DEP_CPP_COMPL) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\DeleteRepeatersDlg.cpp
DEP_CPP_DELET=\
	".\CompleteSet.h"\
	".\DeleteRepeatersDlg.h"\
	".\lbctrl.h"\
	".\Rfi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DeleteRepeatersDlg.obj" : $(SOURCE) $(DEP_CPP_DELET) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\EditRepeaterDlg.cpp
DEP_CPP_EDITR=\
	".\EditRepeaterDlg.h"\
	".\Rfi.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\EditRepeaterDlg.obj" : $(SOURCE) $(DEP_CPP_EDITR) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\lbctrl.cpp
DEP_CPP_LBCTR=\
	".\lbctrl.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\lbctrl.obj" : $(SOURCE) $(DEP_CPP_LBCTR) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\ntray.cpp
DEP_CPP_NTRAY=\
	".\ntray.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ntray.obj" : $(SOURCE) $(DEP_CPP_NTRAY) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\Rfi.cpp
DEP_CPP_RFI_C=\
	".\CompleteSet.h"\
	".\lbctrl.h"\
	".\ntray.h"\
	".\Rfi.h"\
	".\RfiDlg.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Rfi.obj" : $(SOURCE) $(DEP_CPP_RFI_C) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\Rfi.rc
DEP_RSC_RFI_R=\
	".\res\arrow.bmp"\
	".\res\reptr.ico"\
	".\res\Rfi.ico"\
	".\res\Rfi.rc2"\
	".\res\rfiicon.ico"\
	".\res\tray.ico"\
	".\Splsh16.bmp"\
	

"$(INTDIR)\Rfi.res" : $(SOURCE) $(DEP_RSC_RFI_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\RfiDlg.cpp
DEP_CPP_RFIDL=\
	".\AddRepeatersDlg.h"\
	".\CompleteSet.h"\
	".\DeleteRepeatersDlg.h"\
	".\EditRepeaterDlg.h"\
	".\lbctrl.h"\
	".\ntray.h"\
	".\Rfi.h"\
	".\RfiDlg.h"\
	".\Splash1.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\RfiDlg.obj" : $(SOURCE) $(DEP_CPP_RFIDL) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\Splash1.cpp
DEP_CPP_SPLAS=\
	".\Splash1.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Splash1.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\Rfi.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Rfi - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\Rfi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Rfi.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Rfi - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\Rfi.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Rfi.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

