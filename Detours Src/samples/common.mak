##############################################################################
##
##  Common makefile for Detours test programs.
##
##  Microsoft Research Detours Package.  Version 1.5 (Build 46)
##
##  Copyright 1995-2001, Microsoft Corporation
##
!IFNDEF CLIB
CLIB=/MD
!ENDIF

DTRLIBD = ..\..\lib
DTRINCD = ..\..\include

LIBD = ..\lib
BIND = ..\bin
INCD = ..\include

CFLAGS = /nologo /Zi $(CLIB) /Gi- /Gm- /W4 /WX /FR "/I$(DTRINCD)" "/I$(INCD)"
LIBS = "$(LIBD)\syelog.lib" "$(DTRLIBD)\detours.lib" \
		kernel32.lib gdi32.lib user32.lib shell32.lib
##
################################################################# End of File.
