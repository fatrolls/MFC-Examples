all: myvxd.vxd

OBJECTS = devdcl.obj myvxd.obj

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -DMASM6 -Zd -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

.cpp.obj:
   cl -c -Gs -Zdpl -Odb2 -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.cpp

myvxd.vxd: $*.def $(OBJECTS)
   c:\ddk\bin\link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
$(OBJECTS)
<<
