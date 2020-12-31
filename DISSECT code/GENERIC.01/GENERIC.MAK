# filename : generic.mak
# make file for generic.exe (Generic Windows Application)
# usage : nmake generic.mak (Microsoft C/C++ 9.00) (Visual C++ 2.0)
# usage : nmake generic.mak (Microsoft C/C++ 10.00) (Visual C++ 4.0)

all: generic.exe

generic.res : generic.rc generic.h
    rc generic.rc

generic.obj : generic.c generic.h
    cl -c -W3 -Gz -D_X86_ -DWIN32 generic.c

generic.exe : generic.obj generic.res
    link /MACHINE:I386 -subsystem:windows generic.res generic.obj \
         libc.lib kernel32.lib user32.lib gdi32.lib

