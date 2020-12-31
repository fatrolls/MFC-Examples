# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MSDIDao - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MSDIDao - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MSDIDao - Win32 Release" && "$(CFG)" !=\
 "MSDIDao - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MSDIDao.mak" CFG="MSDIDao - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MSDIDao - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MSDIDao - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MSDIDao - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
F90=fl32.exe
RSC=rc.exe

!IF  "$(CFG)" == "MSDIDao - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\MSDIDao.exe"

CLEAN : 
	-@erase "$(INTDIR)\CategSet.obj"
	-@erase "$(INTDIR)\CategTbl.obj"
	-@erase "$(INTDIR)\CategVw.obj"
	-@erase "$(INTDIR)\Crack.obj"
	-@erase "$(INTDIR)\CustSet.obj"
	-@erase "$(INTDIR)\CustTbl.obj"
	-@erase "$(INTDIR)\DaoBmp.obj"
	-@erase "$(INTDIR)\DaoDoc.obj"
	-@erase "$(INTDIR)\DaoSet.obj"
	-@erase "$(INTDIR)\DaoView.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\DIBView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Msdiapp.obj"
	-@erase "$(INTDIR)\MSDIDao.obj"
	-@erase "$(INTDIR)\MSDIDao.pch"
	-@erase "$(INTDIR)\MSDIDao.res"
	-@erase "$(INTDIR)\Msdifrm.obj"
	-@erase "$(INTDIR)\Msdivfrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TblFrame.obj"
	-@erase "$(INTDIR)\TblView.obj"
	-@erase "$(INTDIR)\Util.obj"
	-@erase "$(OUTDIR)\MSDIDao.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo
# ADD F90 /Ox /I "Release/" /c /nologo
F90_PROJ=/Ox /I "Release/" /c /nologo /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MSDIDao.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x100c /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/MSDIDao.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSDIDao.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MSDIDao.pdb" /machine:I386 /out:"$(OUTDIR)/MSDIDao.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CategSet.obj" \
	"$(INTDIR)\CategTbl.obj" \
	"$(INTDIR)\CategVw.obj" \
	"$(INTDIR)\Crack.obj" \
	"$(INTDIR)\CustSet.obj" \
	"$(INTDIR)\CustTbl.obj" \
	"$(INTDIR)\DaoBmp.obj" \
	"$(INTDIR)\DaoDoc.obj" \
	"$(INTDIR)\DaoSet.obj" \
	"$(INTDIR)\DaoView.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\DIBView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Msdiapp.obj" \
	"$(INTDIR)\MSDIDao.obj" \
	"$(INTDIR)\MSDIDao.res" \
	"$(INTDIR)\Msdifrm.obj" \
	"$(INTDIR)\Msdivfrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TblFrame.obj" \
	"$(INTDIR)\TblView.obj" \
	"$(INTDIR)\Util.obj"

"$(OUTDIR)\MSDIDao.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MSDIDao - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\MSDIDao.exe"

CLEAN : 
	-@erase "$(INTDIR)\CategSet.obj"
	-@erase "$(INTDIR)\CategTbl.obj"
	-@erase "$(INTDIR)\CategVw.obj"
	-@erase "$(INTDIR)\Crack.obj"
	-@erase "$(INTDIR)\CustSet.obj"
	-@erase "$(INTDIR)\CustTbl.obj"
	-@erase "$(INTDIR)\DaoBmp.obj"
	-@erase "$(INTDIR)\DaoDoc.obj"
	-@erase "$(INTDIR)\DaoSet.obj"
	-@erase "$(INTDIR)\DaoView.obj"
	-@erase "$(INTDIR)\dibapi.obj"
	-@erase "$(INTDIR)\DIBView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Msdiapp.obj"
	-@erase "$(INTDIR)\MSDIDao.obj"
	-@erase "$(INTDIR)\MSDIDao.pch"
	-@erase "$(INTDIR)\MSDIDao.res"
	-@erase "$(INTDIR)\Msdifrm.obj"
	-@erase "$(INTDIR)\Msdivfrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TblFrame.obj"
	-@erase "$(INTDIR)\TblView.obj"
	-@erase "$(INTDIR)\Util.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MSDIDao.exe"
	-@erase "$(OUTDIR)\MSDIDao.ilk"
	-@erase "$(OUTDIR)\MSDIDao.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo
# ADD F90 /Zi /I "Debug/" /c /nologo
F90_PROJ=/Zi /I "Debug/" /c /nologo /Fo"Debug/" /Fd"Debug/MSDIDao.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MSDIDao.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x100c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x100c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x100c /fo"$(INTDIR)/MSDIDao.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MSDIDao.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MSDIDao.pdb" /debug /machine:I386 /out:"$(OUTDIR)/MSDIDao.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CategSet.obj" \
	"$(INTDIR)\CategTbl.obj" \
	"$(INTDIR)\CategVw.obj" \
	"$(INTDIR)\Crack.obj" \
	"$(INTDIR)\CustSet.obj" \
	"$(INTDIR)\CustTbl.obj" \
	"$(INTDIR)\DaoBmp.obj" \
	"$(INTDIR)\DaoDoc.obj" \
	"$(INTDIR)\DaoSet.obj" \
	"$(INTDIR)\DaoView.obj" \
	"$(INTDIR)\dibapi.obj" \
	"$(INTDIR)\DIBView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Msdiapp.obj" \
	"$(INTDIR)\MSDIDao.obj" \
	"$(INTDIR)\MSDIDao.res" \
	"$(INTDIR)\Msdifrm.obj" \
	"$(INTDIR)\Msdivfrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TblFrame.obj" \
	"$(INTDIR)\TblView.obj" \
	"$(INTDIR)\Util.obj"

"$(OUTDIR)\MSDIDao.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "MSDIDao - Win32 Release"
# Name "MSDIDao - Win32 Debug"

!IF  "$(CFG)" == "MSDIDao - Win32 Release"

!ELSEIF  "$(CFG)" == "MSDIDao - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MSDIDao - Win32 Release"

!ELSEIF  "$(CFG)" == "MSDIDao - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSDIDao.cpp
DEP_CPP_MSDID=\
	".\CategTbl.h"\
	".\CategVw.h"\
	".\Crack.h"\
	".\CustTbl.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\DaoView.h"\
	".\DIBApi.h"\
	".\DIBView.h"\
	".\MainFrm.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\MSDIFrm.h"\
	".\MSDIvFrm.h"\
	".\StdAfx.h"\
	".\TblFrame.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\MSDIDao.obj" : $(SOURCE) $(DEP_CPP_MSDID) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Crack.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

!IF  "$(CFG)" == "MSDIDao - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MSDIDao.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSDIDao.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MSDIDao - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MSDIDao.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MSDIDao.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Crack.h"\
	".\DIBApi.h"\
	".\DIBView.h"\
	".\MainFrm.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoDoc.cpp
DEP_CPP_DAODO=\
	".\CategSet.h"\
	".\CategTbl.h"\
	".\CategVw.h"\
	".\Crack.h"\
	".\CustSet.h"\
	".\CustTbl.h"\
	".\DaoBmp.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\DaoDoc.obj" : $(SOURCE) $(DEP_CPP_DAODO) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoView.cpp
DEP_CPP_DAOVI=\
	".\Crack.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\DaoView.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\DaoView.obj" : $(SOURCE) $(DEP_CPP_DAOVI) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSDIDao.rc
DEP_RSC_MSDIDA=\
	".\res\DaoDoc.ico"\
	".\res\MSDIDao.ico"\
	".\res\MSDIDao.rc2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\MSDIDao.res" : $(SOURCE) $(DEP_RSC_MSDIDA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdiapp.cpp
DEP_CPP_MSDIA=\
	".\Crack.h"\
	".\MSDIApp.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\Msdiapp.obj" : $(SOURCE) $(DEP_CPP_MSDIA) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdifrm.cpp
DEP_CPP_MSDIF=\
	".\Crack.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\MSDIFrm.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\Msdifrm.obj" : $(SOURCE) $(DEP_CPP_MSDIF) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Msdivfrm.cpp
DEP_CPP_MSDIV=\
	".\Crack.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\MSDIvFrm.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\Msdivfrm.obj" : $(SOURCE) $(DEP_CPP_MSDIV) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TblView.cpp
DEP_CPP_TBLVI=\
	".\Crack.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\TblView.obj" : $(SOURCE) $(DEP_CPP_TBLVI) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CategVw.cpp
DEP_CPP_CATEG=\
	".\CategSet.h"\
	".\CategVw.h"\
	".\Crack.h"\
	".\DaoBmp.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\CategVw.obj" : $(SOURCE) $(DEP_CPP_CATEG) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CategSet.cpp
DEP_CPP_CATEGS=\
	".\CategSet.h"\
	".\Crack.h"\
	".\DaoBmp.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\CategSet.obj" : $(SOURCE) $(DEP_CPP_CATEGS) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoSet.cpp
DEP_CPP_DAOSE=\
	".\Crack.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\DaoSet.obj" : $(SOURCE) $(DEP_CPP_DAOSE) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Crack.cpp
DEP_CPP_CRACK=\
	".\Crack.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\Crack.obj" : $(SOURCE) $(DEP_CPP_CRACK) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TblFrame.cpp
DEP_CPP_TBLFR=\
	".\Crack.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\MSDIvFrm.h"\
	".\StdAfx.h"\
	".\TblFrame.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\TblFrame.obj" : $(SOURCE) $(DEP_CPP_TBLFR) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Util.cpp
DEP_CPP_UTIL_=\
	".\Crack.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\Util.obj" : $(SOURCE) $(DEP_CPP_UTIL_) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CustSet.cpp
DEP_CPP_CUSTS=\
	".\Crack.h"\
	".\CustSet.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\CustSet.obj" : $(SOURCE) $(DEP_CPP_CUSTS) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CategTbl.cpp
DEP_CPP_CATEGT=\
	".\CategSet.h"\
	".\CategTbl.h"\
	".\CategVw.h"\
	".\Crack.h"\
	".\DaoBmp.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\CategTbl.obj" : $(SOURCE) $(DEP_CPP_CATEGT) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CustTbl.cpp
DEP_CPP_CUSTT=\
	".\Crack.h"\
	".\CustSet.h"\
	".\CustTbl.h"\
	".\DaoDoc.h"\
	".\DaoSet.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\TblView.h"\
	".\Util.h"\
	

"$(INTDIR)\CustTbl.obj" : $(SOURCE) $(DEP_CPP_CUSTT) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoBmp.cpp
DEP_CPP_DAOBM=\
	".\Crack.h"\
	".\DaoBmp.h"\
	".\DIBApi.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\DaoBmp.obj" : $(SOURCE) $(DEP_CPP_DAOBM) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIBView.cpp
DEP_CPP_DIBVI=\
	".\Crack.h"\
	".\DIBApi.h"\
	".\DIBView.h"\
	".\MainFrm.h"\
	".\MSDIApp.h"\
	".\MSDIDao.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\DIBView.obj" : $(SOURCE) $(DEP_CPP_DIBVI) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dibapi.cpp
DEP_CPP_DIBAP=\
	".\Crack.h"\
	".\DIBApi.h"\
	".\StdAfx.h"\
	".\Util.h"\
	

"$(INTDIR)\dibapi.obj" : $(SOURCE) $(DEP_CPP_DIBAP) "$(INTDIR)"\
 "$(INTDIR)\MSDIDao.pch"


# End Source File
# End Target
# End Project
################################################################################
