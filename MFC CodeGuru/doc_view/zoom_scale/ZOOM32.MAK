# Microsoft Visual C++ generated build script - Do not modify

PROJ = ZOOM32
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
ORIGIN = MSVCNT
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
FIRSTCPP = 
RC = rc
CFLAGS_D_WEXE32 = /nologo /D_X86_ /W3 /FR /YX /D_DEBUG /Zi /D_WINDOWS /Fd"ZOOM32.PDB" /Fp"ZOOM32.PCH"
CFLAGS_R_WEXE32 = /nologo /D_X86_ /W3 /FR /YX /O2 /DNDEBUG /D_WINDOWS /Fp"ZOOM32.PCH"
LFLAGS_D_WEXE32 = /NOLOGO /DEBUG /DEBUGTYPE:cv /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib nafxcwd.lib
LFLAGS_R_WEXE32 = /NOLOGO /SUBSYSTEM:windows user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib olecli32.lib olesvr32.lib shell32.lib nafxcw.lib
LFLAGS_D_LIB32 = /NOLOGO
LFLAGS_R_LIB32 = /NOLOGO
LIBS_D_WEXE32 = 
LIBS_R_WEXE32 = 
RCFLAGS32 = 
D_RCDEFINES32 = -d_DEBUG
R_RCDEFINES32 = -dNDEBUG
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE32)
LFLAGS = $(LFLAGS_D_WEXE32)
LIBS = $(LIBS_D_WEXE32)
LFLAGS_LIB=$(LFLAGS_D_LIB32)
MAPFILE_OPTION = 
RCDEFINES = $(D_RCDEFINES32)
!else
CFLAGS = $(CFLAGS_R_WEXE32)
LFLAGS = $(LFLAGS_R_WEXE32)
LIBS = $(LIBS_R_WEXE32)
MAPFILE_OPTION = 
LFLAGS_LIB=$(LFLAGS_R_LIB32)
RCDEFINES = $(R_RCDEFINES32)
!endif
SBRS = MAINFRM.SBR \
		STDAFX.SBR \
		TEST.SBR \
		TESTDOC.SBR \
		TESTVIEW.SBR \
		ZOOMVIEW.SBR


MAINFRM_DEP =  \
	c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\mainfrm.h


STDAFX_DEP =  \
	c:\zoom_wdj\stdafx.h


TEST_DEP =  \
	c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\zoomview.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\mainfrm.h \
	c:\zoom_wdj\testdoc.h \
	c:\zoom_wdj\testview.h


TESTDOC_DEP =  \
	c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\testdoc.h


TESTVIEW_DEP =  \
	c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\mainfrm.h \
	c:\zoom_wdj\zoomview.h \
	c:\zoom_wdj\test.h \
	c:\zoom_wdj\testdoc.h \
	c:\zoom_wdj\testview.h


ZOOMVIEW_DEP =  \
	c:\zoom_wdj\stdafx.h \
	c:\zoom_wdj\zoomview.h


TEST_RCDEP =  \
	c:\zoom_wdj\res\test.ico \
	c:\zoom_wdj\res\testdoc.ico \
	c:\zoom_wdj\res\zoomcurs.cur \
	c:\zoom_wdj\res\test.rc2


all:	$(PROJ).EXE $(PROJ).BSC

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP

TEST.OBJ:	TEST.CPP $(TEST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEST.CPP

TESTDOC.OBJ:	TESTDOC.CPP $(TESTDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTDOC.CPP

TESTVIEW.OBJ:	TESTVIEW.CPP $(TESTVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTVIEW.CPP

ZOOMVIEW.OBJ:	ZOOMVIEW.CPP $(ZOOMVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ZOOMVIEW.CPP

TEST.RES:	TEST.RC $(TEST_RCDEP)
	$(RC) $(RCFLAGS32) $(RCDEFINES) -r TEST.RC


$(PROJ).EXE:	TEST.RES

$(PROJ).EXE:	MAINFRM.OBJ STDAFX.OBJ TEST.OBJ TESTDOC.OBJ TESTVIEW.OBJ ZOOMVIEW.OBJ $(OBJS_EXT) $(LIBS_EXT)
	echo >NUL @<<$(PROJ).CRF
MAINFRM.OBJ 
STDAFX.OBJ 
TEST.OBJ 
TESTDOC.OBJ 
TESTVIEW.OBJ 
ZOOMVIEW.OBJ 
$(OBJS_EXT)
-OUT:$(PROJ).EXE
$(MAPFILE_OPTION)
TEST.RES
$(LIBS)
$(LIBS_EXT)
$(DEFFILE_OPTION) -implib:$(PROJ).lib
<<
	link $(LFLAGS) @$(PROJ).CRF

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
