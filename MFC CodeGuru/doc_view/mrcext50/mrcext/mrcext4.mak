# Microsoft Developer Studio Generated NMAKE File, Based on mrcext4.dsp
!IF "$(CFG)" == ""
CFG=Mrcext - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Mrcext - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Mrcext - Win32 Debug" && "$(CFG)" != "Mrcext - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mrcext4.mak" CFG="Mrcext - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mrcext - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Mrcext - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Mrcext - Win32 Debug"

OUTDIR=.\..\bin
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\mrcex42d.dll" "$(OUTDIR)\mrcext4.bsc"

!ELSE 

ALL : "$(OUTDIR)\mrcex42d.dll" "$(OUTDIR)\mrcext4.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BMPBTN.OBJ"
	-@erase "$(INTDIR)\BMPBTN.SBR"
	-@erase "$(INTDIR)\cfgtbar.obj"
	-@erase "$(INTDIR)\cfgtbar.sbr"
	-@erase "$(INTDIR)\CLRLABEL.OBJ"
	-@erase "$(INTDIR)\CLRLABEL.SBR"
	-@erase "$(INTDIR)\DIB.OBJ"
	-@erase "$(INTDIR)\DIB.SBR"
	-@erase "$(INTDIR)\DRAGDOCK.OBJ"
	-@erase "$(INTDIR)\DRAGDOCK.SBR"
	-@erase "$(INTDIR)\FRAMEWND.OBJ"
	-@erase "$(INTDIR)\FRAMEWND.SBR"
	-@erase "$(INTDIR)\mdifloat.obj"
	-@erase "$(INTDIR)\mdifloat.sbr"
	-@erase "$(INTDIR)\MRCANIMA.OBJ"
	-@erase "$(INTDIR)\MRCANIMA.SBR"
	-@erase "$(INTDIR)\MRCEXT.OBJ"
	-@erase "$(INTDIR)\MRCEXT.res"
	-@erase "$(INTDIR)\MRCEXT.SBR"
	-@erase "$(INTDIR)\mrcext4.pch"
	-@erase "$(INTDIR)\mrcextx.idb"
	-@erase "$(INTDIR)\mrcextx.pdb"
	-@erase "$(INTDIR)\MRCSTAFX.OBJ"
	-@erase "$(INTDIR)\MRCSTAFX.SBR"
	-@erase "$(INTDIR)\SIZECONT.OBJ"
	-@erase "$(INTDIR)\SIZECONT.SBR"
	-@erase "$(INTDIR)\SIZEDLG.OBJ"
	-@erase "$(INTDIR)\SIZEDLG.SBR"
	-@erase "$(INTDIR)\SIZEDOCK.OBJ"
	-@erase "$(INTDIR)\SIZEDOCK.SBR"
	-@erase "$(INTDIR)\SZTOOLBA.OBJ"
	-@erase "$(INTDIR)\SZTOOLBA.SBR"
	-@erase "$(OUTDIR)\mrcex42d.dll"
	-@erase "$(OUTDIR)\mrcex42d.ilk"
	-@erase "$(OUTDIR)\mrcex42d.pdb"
	-@erase "$(OUTDIR)\mrcext4.bsc"
	-@erase "$(OUTDIR)\mrcext4d.exp"
	-@erase "$(OUTDIR)\mrcext4d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\mrcext4.pch" /Yu"mrcstafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\mrcextx.pdb" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MRCEXT.res" /i "..\inc" /d "_DEBUG" /d\
 "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mrcext4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BMPBTN.SBR" \
	"$(INTDIR)\cfgtbar.sbr" \
	"$(INTDIR)\CLRLABEL.SBR" \
	"$(INTDIR)\DIB.SBR" \
	"$(INTDIR)\DRAGDOCK.SBR" \
	"$(INTDIR)\FRAMEWND.SBR" \
	"$(INTDIR)\mdifloat.sbr" \
	"$(INTDIR)\MRCANIMA.SBR" \
	"$(INTDIR)\MRCEXT.SBR" \
	"$(INTDIR)\MRCSTAFX.SBR" \
	"$(INTDIR)\SIZECONT.SBR" \
	"$(INTDIR)\SIZEDLG.SBR" \
	"$(INTDIR)\SIZEDOCK.SBR" \
	"$(INTDIR)\SZTOOLBA.SBR"

"$(OUTDIR)\mrcext4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\mrcex42d.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\mrcex42d.dll" /implib:"$(OUTDIR)\mrcext4d.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BMPBTN.OBJ" \
	"$(INTDIR)\cfgtbar.obj" \
	"$(INTDIR)\CLRLABEL.OBJ" \
	"$(INTDIR)\DIB.OBJ" \
	"$(INTDIR)\DRAGDOCK.OBJ" \
	"$(INTDIR)\FRAMEWND.OBJ" \
	"$(INTDIR)\mdifloat.obj" \
	"$(INTDIR)\MRCANIMA.OBJ" \
	"$(INTDIR)\MRCEXT.OBJ" \
	"$(INTDIR)\MRCEXT.res" \
	"$(INTDIR)\MRCSTAFX.OBJ" \
	"$(INTDIR)\SIZECONT.OBJ" \
	"$(INTDIR)\SIZEDLG.OBJ" \
	"$(INTDIR)\SIZEDOCK.OBJ" \
	"$(INTDIR)\SZTOOLBA.OBJ"

"$(OUTDIR)\mrcex42d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Mrcext - Win32 Release"

OUTDIR=.\..\bin
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\bin
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Mrcex42.dll" "$(OUTDIR)\mrcext4.bsc"

!ELSE 

ALL : "$(OUTDIR)\Mrcex42.dll" "$(OUTDIR)\mrcext4.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\BMPBTN.OBJ"
	-@erase "$(INTDIR)\BMPBTN.SBR"
	-@erase "$(INTDIR)\cfgtbar.obj"
	-@erase "$(INTDIR)\cfgtbar.sbr"
	-@erase "$(INTDIR)\CLRLABEL.OBJ"
	-@erase "$(INTDIR)\CLRLABEL.SBR"
	-@erase "$(INTDIR)\DIB.OBJ"
	-@erase "$(INTDIR)\DIB.SBR"
	-@erase "$(INTDIR)\DRAGDOCK.OBJ"
	-@erase "$(INTDIR)\DRAGDOCK.SBR"
	-@erase "$(INTDIR)\FRAMEWND.OBJ"
	-@erase "$(INTDIR)\FRAMEWND.SBR"
	-@erase "$(INTDIR)\mdifloat.obj"
	-@erase "$(INTDIR)\mdifloat.sbr"
	-@erase "$(INTDIR)\MRCANIMA.OBJ"
	-@erase "$(INTDIR)\MRCANIMA.SBR"
	-@erase "$(INTDIR)\MRCEXT.OBJ"
	-@erase "$(INTDIR)\MRCEXT.res"
	-@erase "$(INTDIR)\MRCEXT.SBR"
	-@erase "$(INTDIR)\mrcext4.pch"
	-@erase "$(INTDIR)\mrcextx.idb"
	-@erase "$(INTDIR)\mrcextx.pdb"
	-@erase "$(INTDIR)\MRCSTAFX.OBJ"
	-@erase "$(INTDIR)\MRCSTAFX.SBR"
	-@erase "$(INTDIR)\SIZECONT.OBJ"
	-@erase "$(INTDIR)\SIZECONT.SBR"
	-@erase "$(INTDIR)\SIZEDLG.OBJ"
	-@erase "$(INTDIR)\SIZEDLG.SBR"
	-@erase "$(INTDIR)\SIZEDOCK.OBJ"
	-@erase "$(INTDIR)\SIZEDOCK.SBR"
	-@erase "$(INTDIR)\SZTOOLBA.OBJ"
	-@erase "$(INTDIR)\SZTOOLBA.SBR"
	-@erase "$(OUTDIR)\Mrcex42.dll"
	-@erase "$(OUTDIR)\mrcext4.bsc"
	-@erase "$(OUTDIR)\mrcext4.exp"
	-@erase "$(OUTDIR)\mrcext4.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /Zi /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\mrcext4.pch" /Yu"mrcstafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\mrcextx.pdb" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/

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
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\MRCEXT.res" /i "..\inc" /d "NDEBUG" /d\
 "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mrcext4.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BMPBTN.SBR" \
	"$(INTDIR)\cfgtbar.sbr" \
	"$(INTDIR)\CLRLABEL.SBR" \
	"$(INTDIR)\DIB.SBR" \
	"$(INTDIR)\DRAGDOCK.SBR" \
	"$(INTDIR)\FRAMEWND.SBR" \
	"$(INTDIR)\mdifloat.sbr" \
	"$(INTDIR)\MRCANIMA.SBR" \
	"$(INTDIR)\MRCEXT.SBR" \
	"$(INTDIR)\MRCSTAFX.SBR" \
	"$(INTDIR)\SIZECONT.SBR" \
	"$(INTDIR)\SIZEDLG.SBR" \
	"$(INTDIR)\SIZEDOCK.SBR" \
	"$(INTDIR)\SZTOOLBA.SBR"

"$(OUTDIR)\mrcext4.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\Mrcex42.pdb" /machine:I386 /out:"$(OUTDIR)\Mrcex42.dll"\
 /implib:"$(OUTDIR)\mrcext4.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BMPBTN.OBJ" \
	"$(INTDIR)\cfgtbar.obj" \
	"$(INTDIR)\CLRLABEL.OBJ" \
	"$(INTDIR)\DIB.OBJ" \
	"$(INTDIR)\DRAGDOCK.OBJ" \
	"$(INTDIR)\FRAMEWND.OBJ" \
	"$(INTDIR)\mdifloat.obj" \
	"$(INTDIR)\MRCANIMA.OBJ" \
	"$(INTDIR)\MRCEXT.OBJ" \
	"$(INTDIR)\MRCEXT.res" \
	"$(INTDIR)\MRCSTAFX.OBJ" \
	"$(INTDIR)\SIZECONT.OBJ" \
	"$(INTDIR)\SIZEDLG.OBJ" \
	"$(INTDIR)\SIZEDOCK.OBJ" \
	"$(INTDIR)\SZTOOLBA.OBJ"

"$(OUTDIR)\Mrcex42.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "Mrcext - Win32 Debug" || "$(CFG)" == "Mrcext - Win32 Release"
SOURCE=.\BMPBTN.CPP
DEP_CPP_BMPBT=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\BMPBTN.OBJ"	"$(INTDIR)\BMPBTN.SBR" : $(SOURCE) $(DEP_CPP_BMPBT)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\cfgtbar.cpp
DEP_CPP_CFGTB=\
	"..\inc\mrcext.h"\
	".\cfgTbar.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\cfgtbar.obj"	"$(INTDIR)\cfgtbar.sbr" : $(SOURCE) $(DEP_CPP_CFGTB)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\CLRLABEL.CPP
DEP_CPP_CLRLA=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\CLRLABEL.OBJ"	"$(INTDIR)\CLRLABEL.SBR" : $(SOURCE) $(DEP_CPP_CLRLA)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\DIB.CPP
DEP_CPP_DIB_C=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\DIB.OBJ"	"$(INTDIR)\DIB.SBR" : $(SOURCE) $(DEP_CPP_DIB_C)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\DRAGDOCK.CPP
DEP_CPP_DRAGD=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\DRAGDOCK.OBJ"	"$(INTDIR)\DRAGDOCK.SBR" : $(SOURCE) $(DEP_CPP_DRAGD)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\FRAMEWND.CPP
DEP_CPP_FRAME=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\FRAMEWND.OBJ"	"$(INTDIR)\FRAMEWND.SBR" : $(SOURCE) $(DEP_CPP_FRAME)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\mdifloat.cpp
DEP_CPP_MDIFL=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\mdifloat.obj"	"$(INTDIR)\mdifloat.sbr" : $(SOURCE) $(DEP_CPP_MDIFL)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\MRCANIMA.CPP
DEP_CPP_MRCAN=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\MRCANIMA.OBJ"	"$(INTDIR)\MRCANIMA.SBR" : $(SOURCE) $(DEP_CPP_MRCAN)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\MRCEXT.CPP
DEP_CPP_MRCEX=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\MRCEXT.OBJ"	"$(INTDIR)\MRCEXT.SBR" : $(SOURCE) $(DEP_CPP_MRCEX)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\MRCEXT.RC
DEP_RSC_MRCEXT=\
	".\MRCEXT.RC2"\
	

"$(INTDIR)\MRCEXT.res" : $(SOURCE) $(DEP_RSC_MRCEXT) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MRCSTAFX.CPP
DEP_CPP_MRCST=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

!IF  "$(CFG)" == "Mrcext - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mrcext4.pch" /Yc"mrcstafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\mrcextx.pdb" /FD /c 

"$(INTDIR)\MRCSTAFX.OBJ"	"$(INTDIR)\MRCSTAFX.SBR"	"$(INTDIR)\mrcext4.pch" : \
$(SOURCE) $(DEP_CPP_MRCST) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Mrcext - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /Zi /O2 /I "..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\mrcext4.pch" /Yc"mrcstafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\mrcextx.pdb" /FD /c 

"$(INTDIR)\MRCSTAFX.OBJ"	"$(INTDIR)\MRCSTAFX.SBR"	"$(INTDIR)\mrcext4.pch" : \
$(SOURCE) $(DEP_CPP_MRCST) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SIZECONT.CPP
DEP_CPP_SIZEC=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\SIZECONT.OBJ"	"$(INTDIR)\SIZECONT.SBR" : $(SOURCE) $(DEP_CPP_SIZEC)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\SIZEDLG.CPP
DEP_CPP_SIZED=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	".\occimpl.h"\
	".\ocdb.h"\
	".\ocdbid.h"\
	".\olebind.h"\
	

"$(INTDIR)\SIZEDLG.OBJ"	"$(INTDIR)\SIZEDLG.SBR" : $(SOURCE) $(DEP_CPP_SIZED)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\SIZEDOCK.CPP
DEP_CPP_SIZEDO=\
	"..\inc\mrcext.h"\
	".\Mrcpriv.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\SIZEDOCK.OBJ"	"$(INTDIR)\SIZEDOCK.SBR" : $(SOURCE) $(DEP_CPP_SIZEDO)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"


SOURCE=.\SZTOOLBA.CPP
DEP_CPP_SZTOO=\
	"..\inc\mrcext.h"\
	".\Mrcstafx.h"\
	

"$(INTDIR)\SZTOOLBA.OBJ"	"$(INTDIR)\SZTOOLBA.SBR" : $(SOURCE) $(DEP_CPP_SZTOO)\
 "$(INTDIR)" "$(INTDIR)\mrcext4.pch"



!ENDIF 

