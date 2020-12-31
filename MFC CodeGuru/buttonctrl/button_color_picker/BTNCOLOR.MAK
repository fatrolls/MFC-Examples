# Microsoft Visual C++ generated build script - Do not modify

PROJ = BTNCOLOR
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = E:\TEMP\BTNCOLOR\
USEMFC = 1
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"BTNCOLOR.PDB"
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = BTNCOLOR.DEF
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
		BTNCOLOR.SBR \
		MAINFRM.SBR \
		BTNCODOC.SBR \
		BTNCOVW.SBR \
		COMBOBTN.SBR


BTNCOLOR_RCDEP = e:\temp\btncolor\res\btncolor.ico \
	e:\temp\btncolor\res\btncodoc.ico \
	e:\temp\btncolor\res\chart.bmp \
	e:\temp\btncolor\res\btncolor.rc2


STDAFX_DEP = e:\temp\btncolor\stdafx.h


BTNCOLOR_DEP = e:\temp\btncolor\stdafx.h \
	e:\temp\btncolor\btncolor.h \
	e:\temp\btncolor\mainfrm.h \
	e:\temp\btncolor\combobtn.h \
	e:\temp\btncolor\btncodoc.h \
	e:\temp\btncolor\btncovw.h


MAINFRM_DEP = e:\temp\btncolor\stdafx.h \
	e:\temp\btncolor\btncolor.h \
	e:\temp\btncolor\mainfrm.h \
	e:\temp\btncolor\combobtn.h


BTNCODOC_DEP = e:\temp\btncolor\stdafx.h \
	e:\temp\btncolor\btncolor.h \
	e:\temp\btncolor\btncodoc.h


BTNCOVW_DEP = e:\temp\btncolor\stdafx.h \
	e:\temp\btncolor\btncolor.h \
	e:\temp\btncolor\btncodoc.h \
	e:\temp\btncolor\btncovw.h


COMBOBTN_DEP = e:\temp\btncolor\stdafx.h \
	e:\temp\btncolor\combobtn.h


all:	$(PROJ).EXE $(PROJ).BSC

BTNCOLOR.RES:	BTNCOLOR.RC $(BTNCOLOR_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r BTNCOLOR.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

BTNCOLOR.OBJ:	BTNCOLOR.CPP $(BTNCOLOR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BTNCOLOR.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

BTNCODOC.OBJ:	BTNCODOC.CPP $(BTNCODOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BTNCODOC.CPP

BTNCOVW.OBJ:	BTNCOVW.CPP $(BTNCOVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BTNCOVW.CPP

COMBOBTN.OBJ:	COMBOBTN.CPP $(COMBOBTN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMBOBTN.CPP


$(PROJ).EXE::	BTNCOLOR.RES

$(PROJ).EXE::	STDAFX.OBJ BTNCOLOR.OBJ MAINFRM.OBJ BTNCODOC.OBJ BTNCOVW.OBJ COMBOBTN.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
BTNCOLOR.OBJ +
MAINFRM.OBJ +
BTNCODOC.OBJ +
BTNCOVW.OBJ +
COMBOBTN.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
D:\MSVC152\CDK16\LIB\+
d:\msvc152\lib\+
d:\msvc152\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) BTNCOLOR.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	BTNCOLOR.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) BTNCOLOR.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
