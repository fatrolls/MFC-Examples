# Microsoft Visual C++ generated build script - Do not modify

PROJ = MSDI
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = F:\WINDEV\MSDI\
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
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"MSDI.PDB"
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = MSDI.DEF
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
		MSDI.SBR \
		MAINFRM.SBR \
		MSDIDOC.SBR \
		MSDIVIEW.SBR \
		GRAFVIEW.SBR \
		MSDIAPP.SBR \
		MSDIFRM.SBR \
		OUTVIEW.SBR \
		VIEWFRM.SBR


MSDI_RCDEP = f:\windev\msdi\res\msdi.ico \
	f:\windev\msdi\res\msdiview.ico \
	f:\windev\msdi\res\grafview.ico \
	f:\windev\msdi\res\outview.ico \
	f:\windev\msdi\res\msdi.rc2


STDAFX_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h


MSDI_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\msdi.h \
	f:\windev\msdi\mainfrm.h \
	f:\windev\msdi\msdidoc.h \
	f:\windev\msdi\msdiview.h \
	f:\windev\msdi\grafview.h \
	f:\windev\msdi\outview.h


MAINFRM_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\msdi.h \
	f:\windev\msdi\mainfrm.h \
	f:\windev\msdi\outview.h


MSDIDOC_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\msdi.h \
	f:\windev\msdi\msdidoc.h \
	f:\windev\msdi\grafview.h \
	f:\windev\msdi\outview.h


MSDIVIEW_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\msdi.h \
	f:\windev\msdi\msdidoc.h \
	f:\windev\msdi\msdiview.h


GRAFVIEW_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\msdi.h \
	f:\windev\msdi\msdidoc.h \
	f:\windev\msdi\grafview.h


MSDIAPP_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h


MSDIFRM_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h


OUTVIEW_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h \
	f:\windev\msdi\mainfrm.h \
	f:\windev\msdi\outview.h


VIEWFRM_DEP = f:\windev\msdi\stdafx.h \
	f:\windev\msdi\msdiapp.h \
	f:\windev\msdi\msdifrm.h \
	f:\windev\msdi\viewfrm.h


all:	$(PROJ).EXE $(PROJ).BSC

MSDI.RES:	MSDI.RC $(MSDI_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r MSDI.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MSDI.OBJ:	MSDI.CPP $(MSDI_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSDI.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

MSDIDOC.OBJ:	MSDIDOC.CPP $(MSDIDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSDIDOC.CPP

MSDIVIEW.OBJ:	MSDIVIEW.CPP $(MSDIVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSDIVIEW.CPP

GRAFVIEW.OBJ:	GRAFVIEW.CPP $(GRAFVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GRAFVIEW.CPP

MSDIAPP.OBJ:	MSDIAPP.CPP $(MSDIAPP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSDIAPP.CPP

MSDIFRM.OBJ:	MSDIFRM.CPP $(MSDIFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MSDIFRM.CPP

OUTVIEW.OBJ:	OUTVIEW.CPP $(OUTVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OUTVIEW.CPP

VIEWFRM.OBJ:	VIEWFRM.CPP $(VIEWFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEWFRM.CPP


$(PROJ).EXE::	MSDI.RES

$(PROJ).EXE::	STDAFX.OBJ MSDI.OBJ MAINFRM.OBJ MSDIDOC.OBJ MSDIVIEW.OBJ GRAFVIEW.OBJ \
	MSDIAPP.OBJ MSDIFRM.OBJ OUTVIEW.OBJ VIEWFRM.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MSDI.OBJ +
MAINFRM.OBJ +
MSDIDOC.OBJ +
MSDIVIEW.OBJ +
GRAFVIEW.OBJ +
MSDIAPP.OBJ +
MSDIFRM.OBJ +
OUTVIEW.OBJ +
VIEWFRM.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
f:\windev\lib\+
c:\gsw4\c\lib\+
c:\gsw4\c\cgraph\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) MSDI.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	MSDI.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) MSDI.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
