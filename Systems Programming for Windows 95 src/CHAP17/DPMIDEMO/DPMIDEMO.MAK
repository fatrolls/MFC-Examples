all: dpmidemo.exe

.asm.obj:
    ml -c -Zi $*.asm

.c.obj:
    cl -c -Zi -AS -G2 $*.c

dpmidemo.exe: $*.obj loader.obj
    link /noe /co /map loader dpmidemo, dpmidemo, dpmidemo;
