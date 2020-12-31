# Microsoft Visual C++ generated build script - Do not modify

PROJ = ZOOM16
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\ZOOM_WDJ\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"ZOOM16.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AL /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /ALIGN:16 /STACK:10240
LFLAGS_R_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /ALIGN:16 /STACK:10240
LIBS_D_WEXE = lafxcwd oldnames libw commdlg shell olecli olesvr llibcew
LIBS_R_WEXE = lafxcw oldnames libw commdlg shell olecli olesvr llibcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = ZOOM16.DEF
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
		MAINFRM.SBR \
		TEST.SBR \
		TESTDOC.SBR \
		TESTVIEW.SBR \
		ZOOMVIEW.SBR


STDAFX_DEP = c:\zoom_wdj\stdafx.h


MAINFRM_DEP = c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\mainfrm.h


TEST_DEP = c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\zoomview.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\mainfrm.h \
	c:\zoom_wdj\testdoc.h \
	c:\zoom_wdj\testview.h


TESTDOC_DEP = c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\testdoc.h


TESTVIEW_DEP = c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\mainfrm.h \
	c:\zoom_wdj\zoomview.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\testdoc.h \
	c:\zoom_wdj\testview.h


ZOOMVIEW_DEP = c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\zoomview.h


TEST_RCDEP = c:\zoom_wdj\res\test.ico \
	c:\zoom_wdj\res\testdoc.ico \
	c:\zoom_wdj\res\zoomcurs.cur \
	c:\zoom_wdj\res\test.rc2


all:	$(PROJ).EXE $(PROJ).BSC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

TEST.OBJ:	TEST.CPP $(TEST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEST.CPP

TESTDOC.OBJ:	TESTDOC.CPP $(TESTDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTDOC.CPP

TESTVIEW.OBJ:	TESTVIEW.CPP $(TESTVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTVIEW.CPP

ZOOMVIEW.OBJ:	ZOOMVIEW.CPP $(ZOOMVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ZOOMVIEW.CPP

TEST.RES:	TEST.RC $(TEST_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r TEST.RC


$(PROJ).EXE::	TEST.RES

$(PROJ).EXE::	STDAFX.OBJ MAINFRM.OBJ TEST.OBJ TESTDOC.OBJ TESTVIEW.OBJ ZOOMVIEW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MAINFRM.OBJ +
TEST.OBJ +
TESTDOC.OBJ +
TESTVIEW.OBJ +
ZOOMVIEW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
p:\msvc\lib\+
p:\msvc\mfc\lib\+
v:\cae\test-4\lib32s\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) TEST.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	TEST.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) TEST.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
