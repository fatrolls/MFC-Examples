all: myvxd.vxd

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

myvxd.vxd : devdcl.obj $*.obj $*.def
   link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
devdcl.obj $*.obj
<<
   c:\winice95\msym $*
