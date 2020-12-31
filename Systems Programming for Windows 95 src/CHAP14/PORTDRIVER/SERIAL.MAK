all: serial.vxd

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 -I. $*.c

.cpp.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 -I. $*.cpp

myvxd.obj: $*.cpp stdvxd.h vport.h serial.h
serial.obj: $*.cpp stdvxd.h  vport.h serial.h
vport.obj: $*.cpp stdvxd.h vport.h

OBJECTS = devdcl.obj myvxd.obj vport.obj serial.obj

serial.vxd : $*.def $(OBJECTS)
   c:\ddk\bin\link @<<
-machine:i386 -def:$*.def -out:$@
-merge:_CRT$$XCU=.CRT$$XCU
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
$(OBJECTS)
<<
   fixmap $*
   c:\winice95\msym $*
