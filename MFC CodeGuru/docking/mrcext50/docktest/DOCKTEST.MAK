# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Docktest - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Docktest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Docktest - Win32 Debug" && "$(CFG)" !=\
 "Docktest - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Docktest.mak" CFG="Docktest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Docktest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Docktest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Docktest - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Docktest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\Docktest.exe" "$(OUTDIR)\Docktest.bsc"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\Docktest.pch"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\Docktest.bsc"
	-@erase ".\WinDebug\dockchil.sbr"
	-@erase ".\WinDebug\STDAFX.SBR"
	-@erase ".\WinDebug\mainfrm.sbr"
	-@erase ".\WinDebug\DOCKTDOC.SBR"
	-@erase ".\WinDebug\DOCKTVW.SBR"
	-@erase ".\WinDebug\videocli.sbr"
	-@erase ".\WinDebug\mysizeba.sbr"
	-@erase ".\WinDebug\docktest.sbr"
	-@erase ".\WinDebug\Docktest.exe"
	-@erase ".\WinDebug\dockchil.obj"
	-@erase ".\WinDebug\STDAFX.OBJ"
	-@erase ".\WinDebug\mainfrm.obj"
	-@erase ".\WinDebug\DOCKTDOC.OBJ"
	-@erase ".\WinDebug\DOCKTVW.OBJ"
	-@erase ".\WinDebug\videocli.obj"
	-@erase ".\WinDebug\mysizeba.obj"
	-@erase ".\WinDebug\docktest.obj"
	-@erase ".\WinDebug\DOCKTEST.res"
	-@erase ".\WinDebug\Docktest.ilk"
	-@erase ".\WinDebug\Docktest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Docktest.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DOCKTEST.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Docktest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/dockchil.sbr" \
	"$(INTDIR)/STDAFX.SBR" \
	"$(INTDIR)/mainfrm.sbr" \
	"$(INTDIR)/DOCKTDOC.SBR" \
	"$(INTDIR)/DOCKTVW.SBR" \
	"$(INTDIR)/videocli.sbr" \
	"$(INTDIR)/mysizeba.sbr" \
	"$(INTDIR)/docktest.sbr"

"$(OUTDIR)\Docktest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Docktest.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Docktest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/dockchil.obj" \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/DOCKTDOC.OBJ" \
	"$(INTDIR)/DOCKTVW.OBJ" \
	"$(INTDIR)/videocli.obj" \
	"$(INTDIR)/mysizeba.obj" \
	"$(INTDIR)/docktest.obj" \
	"$(INTDIR)/DOCKTEST.res"

"$(OUTDIR)\Docktest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Docktest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\Docktest.exe" "$(OUTDIR)\Docktest.bsc"

CLEAN : 
	-@erase ".\WinRel\Docktest.bsc"
	-@erase ".\WinRel\STDAFX.SBR"
	-@erase ".\WinRel\dockchil.sbr"
	-@erase ".\WinRel\Docktest.pch"
	-@erase ".\WinRel\mysizeba.sbr"
	-@erase ".\WinRel\DOCKTVW.SBR"
	-@erase ".\WinRel\docktest.sbr"
	-@erase ".\WinRel\mainfrm.sbr"
	-@erase ".\WinRel\DOCKTDOC.SBR"
	-@erase ".\WinRel\videocli.sbr"
	-@erase ".\WinRel\Docktest.exe"
	-@erase ".\WinRel\DOCKTDOC.OBJ"
	-@erase ".\WinRel\videocli.obj"
	-@erase ".\WinRel\STDAFX.OBJ"
	-@erase ".\WinRel\dockchil.obj"
	-@erase ".\WinRel\mysizeba.obj"
	-@erase ".\WinRel\DOCKTVW.OBJ"
	-@erase ".\WinRel\docktest.obj"
	-@erase ".\WinRel\mainfrm.obj"
	-@erase ".\WinRel\DOCKTEST.res"
	-@erase ".\WinRel\Docktest.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Docktest.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DOCKTEST.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Docktest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/STDAFX.SBR" \
	"$(INTDIR)/dockchil.sbr" \
	"$(INTDIR)/mysizeba.sbr" \
	"$(INTDIR)/DOCKTVW.SBR" \
	"$(INTDIR)/docktest.sbr" \
	"$(INTDIR)/mainfrm.sbr" \
	"$(INTDIR)/DOCKTDOC.SBR" \
	"$(INTDIR)/videocli.sbr"

"$(OUTDIR)\Docktest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /map /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Docktest.pdb" /map:"$(INTDIR)/Docktest.map" /machine:I386\
 /out:"$(OUTDIR)/Docktest.exe" 
LINK32_OBJS= \
	"$(INTDIR)/DOCKTDOC.OBJ" \
	"$(INTDIR)/videocli.obj" \
	"$(INTDIR)/STDAFX.OBJ" \
	"$(INTDIR)/dockchil.obj" \
	"$(INTDIR)/mysizeba.obj" \
	"$(INTDIR)/DOCKTVW.OBJ" \
	"$(INTDIR)/docktest.obj" \
	"$(INTDIR)/mainfrm.obj" \
	"$(INTDIR)/DOCKTEST.res"

"$(OUTDIR)\Docktest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

MTL_PROJ=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Docktest - Win32 Debug"
# Name "Docktest - Win32 Release"

!IF  "$(CFG)" == "Docktest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Docktest - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\STDAFX.CPP
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	".\Mrcext.h"\
	

!IF  "$(CFG)" == "Docktest - Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Docktest.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Docktest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Docktest - Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Docktest.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\STDAFX.OBJ" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\STDAFX.SBR" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Docktest.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\docktest.cpp
DEP_CPP_DOCKT=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Videocli.h"\
	".\Mainfrm.h"\
	".\Docktdoc.h"\
	".\Docktvw.h"\
	".\Dockchil.h"\
	".\Mrcext.h"\
	".\mysizeba.h"\
	

"$(INTDIR)\docktest.obj" : $(SOURCE) $(DEP_CPP_DOCKT) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\docktest.sbr" : $(SOURCE) $(DEP_CPP_DOCKT) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Mainfrm.h"\
	".\Mrcext.h"\
	".\mysizeba.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\mainfrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOCKTDOC.CPP
DEP_CPP_DOCKTD=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Docktdoc.h"\
	".\Mrcext.h"\
	

"$(INTDIR)\DOCKTDOC.OBJ" : $(SOURCE) $(DEP_CPP_DOCKTD) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\DOCKTDOC.SBR" : $(SOURCE) $(DEP_CPP_DOCKTD) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOCKTVW.CPP
DEP_CPP_DOCKTV=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Docktdoc.h"\
	".\Docktvw.h"\
	".\Mrcext.h"\
	

"$(INTDIR)\DOCKTVW.OBJ" : $(SOURCE) $(DEP_CPP_DOCKTV) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\DOCKTVW.SBR" : $(SOURCE) $(DEP_CPP_DOCKTV) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DOCKTEST.RC
DEP_RSC_DOCKTE=\
	".\DOCKTEST.ICO"\
	".\DOCKTDOC.ICO"\
	".\TOOLBAR.BMP"\
	".\256.bmp"\
	".\BUTTON.bmp"\
	".\16.bmp"\
	".\DOCKTEST.RC2"\
	

"$(INTDIR)\DOCKTEST.res" : $(SOURCE) $(DEP_RSC_DOCKTE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\README.TXT

!IF  "$(CFG)" == "Docktest - Win32 Debug"

!ELSEIF  "$(CFG)" == "Docktest - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mysizeba.cpp
DEP_CPP_MYSIZ=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\mysizeba.h"\
	".\Mrcext.h"\
	

"$(INTDIR)\mysizeba.obj" : $(SOURCE) $(DEP_CPP_MYSIZ) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\mysizeba.sbr" : $(SOURCE) $(DEP_CPP_MYSIZ) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\videocli.cpp
DEP_CPP_VIDEO=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Videocli.h"\
	".\Mrcext.h"\
	

"$(INTDIR)\videocli.obj" : $(SOURCE) $(DEP_CPP_VIDEO) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\videocli.sbr" : $(SOURCE) $(DEP_CPP_VIDEO) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dockchil.cpp
DEP_CPP_DOCKC=\
	".\Stdafx.h"\
	".\Docktest.h"\
	".\Dockchil.h"\
	".\Mrcext.h"\
	

"$(INTDIR)\dockchil.obj" : $(SOURCE) $(DEP_CPP_DOCKC) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"

"$(INTDIR)\dockchil.sbr" : $(SOURCE) $(DEP_CPP_DOCKC) "$(INTDIR)"\
 "$(INTDIR)\Docktest.pch"


# End Source File
# End Target
# End Project
################################################################################
