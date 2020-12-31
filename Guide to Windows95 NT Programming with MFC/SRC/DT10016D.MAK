# Microsoft Visual C++ generated build script - Do not modify

PROJ = DT10016D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\MSDEV\PROJECTS\DTIME\SRC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DATETIME.CPP
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W4 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"DTIM16.PDB"
CFLAGS_R_WDLL = /nologo /W4 /ALw /O1 /D "NDEBUG" /D "_AFXDLL" /GD /GEf 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = mfc250d oldnames libw ldllcew commdlg.lib shell.lib 
LIBS_R_WDLL = mfc250 oldnames libw ldllcew commdlg.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DTIME16D.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DATETIME.SBR \
		DENTRY.SBR \
		DTIME.SBR \
		PUSHPIN.SBR \
		STDAFX.SBR \
		WIN32SUP.SBR \
		DTWINVER.SBR


DATETIME_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h


DENTRY_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\dentry.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\dtimeres.h


DTIME_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\dtime.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\dentry.h \
	e:\msdev\projects\dtime\include\dtwinver.h


PUSHPIN_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\pushpin.h


STDAFX_DEP = e:\msdev\projects\dtime\src\stdafx.h


WIN32SUP_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h


DTIME16_RCDEP = e:\msdev\projects\dtime\src\res\datentry.ico \
	e:\msdev\projects\dtime\src\res\pushpind.bmp \
	e:\msdev\projects\dtime\src\res\pushpinu.bmp \
	e:\msdev\projects\dtime\src\dtime.rc2


DTWINVER_DEP = e:\msdev\projects\dtime\src\stdafx.h \
	e:\msdev\projects\dtime\include\dtwinver.h \
	e:\msdev\projects\dtime\include\win32sup.h


all:	$(PROJ).DLL

DATETIME.OBJ:	DATETIME.CPP $(DATETIME_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DATETIME.CPP

DENTRY.OBJ:	DENTRY.CPP $(DENTRY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DENTRY.CPP

DTIME.OBJ:	DTIME.CPP $(DTIME_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DTIME.CPP

PUSHPIN.OBJ:	PUSHPIN.CPP $(PUSHPIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PUSHPIN.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP

WIN32SUP.OBJ:	WIN32SUP.CPP $(WIN32SUP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WIN32SUP.CPP

DTIME16.RES:	DTIME16.RC $(DTIME16_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DTIME16.RC

DTWINVER.OBJ:	DTWINVER.CPP $(DTWINVER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DTWINVER.CPP


$(PROJ).DLL::	DTIME16.RES

$(PROJ).DLL::	DATETIME.OBJ DENTRY.OBJ DTIME.OBJ PUSHPIN.OBJ STDAFX.OBJ WIN32SUP.OBJ \
	DTWINVER.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DATETIME.OBJ +
DENTRY.OBJ +
DTIME.OBJ +
PUSHPIN.OBJ +
STDAFX.OBJ +
WIN32SUP.OBJ +
DTWINVER.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
e:\msvc\lib\+
e:\msvc\mfc\lib\+
e:\msdev\projects\dtime\src\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DTIME16.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	DTIME16.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DTIME16.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
