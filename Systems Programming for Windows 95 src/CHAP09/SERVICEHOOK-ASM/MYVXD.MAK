all: myvxd.vxd

myvxd.obj: $*.asm
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -Zm -Zi -DMASM6 -DDEBUG -DDEBLEVEL=1 $*.asm

myvxd.vxd: $*.obj $*.def
   link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd
myvxd.obj
<<
    \winice95\msym $*
