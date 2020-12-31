# Microsoft Visual C++ generated build script - Do not modify

PROJ = DTESTDOS
DEBUG = 1
PROGTYPE = 6
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\MSDEV\PROJECTS\DTIME\DATETEST\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DATETEST.CPP
RC = rc
CFLAGS_D_DEXE = /nologo /G2 /W4 /Zi /AM /Od /D "_DEBUG" /D "_DOS" /Fd"DTESTDOS.PDB"
CFLAGS_R_DEXE = /nologo /Gs /G2 /W4 /AM /Ox /D "NDEBUG" /D "_DOS" 
LFLAGS_D_DEXE = /NOLOGO /NOE /NOI /STACK:5120 /ONERROR:NOEXE /CO 
LFLAGS_R_DEXE = /NOLOGO /NOE /NOI /STACK:5120 /ONERROR:NOEXE 
LIBS_D_DEXE = mafxcrd oldnames mlibce 
LIBS_R_DEXE = mafxcr oldnames mlibce 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_DEXE)
LFLAGS = $(LFLAGS_D_DEXE)
LIBS = $(LIBS_D_DEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_DEXE)
LFLAGS = $(LFLAGS_R_DEXE)
LIBS = $(LIBS_R_DEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DATETEST.SBR \
		STDAFX.SBR \
		WIN32SUP.SBR \
		DTWINVER.SBR \
		DTIME.SBR \
		DATETIME.SBR


DATETEST_DEP = e:\msdev\projects\dtime\datetest\stdafx.h \
	e:\msdev\projects\dtime\include\dtime.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\dentry.h


STDAFX_DEP = e:\msdev\projects\dtime\src\stdafx.h


WIN32SUP_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h


DTWINVER_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\dtwinver.h \
	e:\msdev\projects\dtime\include\win32sup.h


DTIME_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\dtime.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\dentry.h \
	e:\msdev\projects\dtime\datetest\stdafx.h \
	e:\msdev\projects\dtime\include\dtwinver.h


DATETIME_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h


all:	$(PROJ).EXE

DATETEST.OBJ:	DATETEST.CPP $(DATETEST_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DATETEST.CPP

STDAFX.OBJ:	..\SRC\STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\SRC\STDAFX.CPP

WIN32SUP.OBJ:	..\SRC\WIN32SUP.CPP $(WIN32SUP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\SRC\WIN32SUP.CPP

DTWINVER.OBJ:	..\SRC\DTWINVER.CPP $(DTWINVER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\SRC\DTWINVER.CPP

DTIME.OBJ:	..\SRC\DTIME.CPP $(DTIME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\SRC\DTIME.CPP

DATETIME.OBJ:	..\SRC\DATETIME.CPP $(DATETIME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\SRC\DATETIME.CPP

$(PROJ).EXE::	DATETEST.OBJ STDAFX.OBJ WIN32SUP.OBJ DTWINVER.OBJ DTIME.OBJ DATETIME.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DATETEST.OBJ +
STDAFX.OBJ +
WIN32SUP.OBJ +
DTWINVER.OBJ +
DTIME.OBJ +
DATETIME.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
e:\msvc\lib\+
e:\msvc\mfc\lib\+
e:\msdev\projects\dtime\src\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
