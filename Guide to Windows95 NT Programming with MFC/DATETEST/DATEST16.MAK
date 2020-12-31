# Microsoft Visual C++ generated build script - Do not modify

PROJ = DATEST16
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = F:\MSDEV\PROJECTS\DTIME\DATETEST\
USEMFC = 0
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
CFLAGS_D_WEXE = /nologo /G2 /W4 /Zi /AL /YX /Od /D "_AFXDLL" /D "_DEBUG" /GA /GEf /Fd"DATEST16.PDB" /Fp"DATEST16.PCH"
CFLAGS_R_WEXE = /nologo /W4 /AL /YX /O1 /D "_AFXDLL" /D "NDEBUG" /GA /GEf /Fp"DATEST16.PCH"
LFLAGS_D_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /NOE /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mfc250d oldnames libw llibcew dt10016d commdlg.lib shell.lib 
LIBS_R_WEXE = mfc250 oldnames libw llibcew dt10016 commdlg.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DATEST16.DEF
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
SBRS = DATETEST.SBR \
		STDAFX.SBR


DATETEST_DEP = f:\msdev\projects\dtime\datetest\stdafx.h \
	f:\msdev\mfc\include\afxdao.h \
	f:\msdev\include\dbdaoint.h \
	f:\msvc\include\tchar.h \
	f:\msdev\include\daogetrw.h \
	f:\msdev\include\dbdaoid.h \
	f:\msdev\include\dbdaoerr.h \
	f:\msdev\mfc\include\afxdb_.h \
	f:\msdev\mfc\include\afxdao.inl \
	f:\msdev\mfc\include\afxcmn.h \
	f:\msdev\include\richedit.h \
	f:\msdev\include\pshpack4.h \
	f:\msdev\include\poppack.h \
	f:\msdev\include\richole.h \
	f:\msdev\mfc\include\afxcmn.inl \
	f:\msdev\projects\dtime\include\dtime.h \
	f:\msdev\projects\dtime\include\win32sup.h \
	f:\msdev\projects\dtime\include\datetime.h \
	f:\msdev\projects\dtime\include\pushpin.h \
	f:\msdev\projects\dtime\include\dentry.h


STDAFX_DEP = f:\msdev\projects\dtime\datetest\stdafx.h \
	f:\msdev\mfc\include\afxdao.h \
	f:\msdev\include\dbdaoint.h \
	f:\msvc\include\tchar.h \
	f:\msdev\include\daogetrw.h \
	f:\msdev\include\dbdaoid.h \
	f:\msdev\include\dbdaoerr.h \
	f:\msdev\mfc\include\afxdb_.h \
	f:\msdev\mfc\include\afxdao.inl \
	f:\msdev\mfc\include\afxcmn.h \
	f:\msdev\include\richedit.h \
	f:\msdev\include\pshpack4.h \
	f:\msdev\include\poppack.h \
	f:\msdev\include\richole.h \
	f:\msdev\mfc\include\afxcmn.inl


all:	$(PROJ).EXE

DATETEST.OBJ:	DATETEST.CPP $(DATETEST_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DATETEST.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP


$(PROJ).EXE::	DATETEST.OBJ STDAFX.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DATETEST.OBJ +
STDAFX.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
F:\MSVC\LIB\+
F:\MSVC\MFC\LIB\+
F:\MSDEV\LIB\+
F:\MSDEV\MFC\LIB\+
f:\msdev\projects\dtime\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@


run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
