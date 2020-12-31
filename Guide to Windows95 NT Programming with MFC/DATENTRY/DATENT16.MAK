# Microsoft Visual C++ generated build script - Do not modify

PROJ = DATENT16
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\MSDEV\PROJECTS\DTIME\DATENTRY\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /D "_AFXDLL" /GA /GEf /Fd"DATENT16.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /D "_AFXDLL" /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mfc250d llibcew oldnames libw dt10016d ctl3ds commdlg.lib shell.lib 
LIBS_R_WEXE = mfc250 oldnames libw llibcew dt10016 ctl3ds commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DATENT16.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		DATENTRY.SBR \
		DATEDLG.SBR


STDAFX_DEP = e:\msdev\projects\dtime\datentry\stdafx.h


DATENTRY_DEP = e:\msdev\projects\dtime\datentry\stdafx.h \
	e:\msdev\projects\dtime\datentry\datentry.h \
	e:\msdev\projects\dtime\datentry\datedlg.h \
	e:\msdev\projects\dtime\include\dtime.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\dentry.h \
	e:\msvc\include\ctl3d.h


DATEDLG_DEP = e:\msdev\projects\dtime\datentry\stdafx.h \
	e:\msdev\projects\dtime\include\dtime.h \
	e:\msdev\projects\dtime\include\win32sup.h \
	e:\msdev\projects\dtime\include\datetime.h \
	e:\msdev\projects\dtime\include\pushpin.h \
	e:\msdev\projects\dtime\include\dentry.h \
	e:\msdev\projects\dtime\datentry\datedlg.h


DATENT16_RCDEP = e:\msdev\projects\dtime\datentry\res\datentry.ico \
	e:\msdev\projects\dtime\datentry\res\datentry.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DATENTRY.OBJ:	DATENTRY.CPP $(DATENTRY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DATENTRY.CPP

DATEDLG.OBJ:	DATEDLG.CPP $(DATEDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DATEDLG.CPP

DATENT16.RES:	DATENT16.RC $(DATENT16_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DATENT16.RC


$(PROJ).EXE::	DATENT16.RES

$(PROJ).EXE::	STDAFX.OBJ DATENTRY.OBJ DATEDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DATENTRY.OBJ +
DATEDLG.OBJ +
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
	$(RC) $(RESFLAGS) DATENT16.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DATENT16.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DATENT16.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
