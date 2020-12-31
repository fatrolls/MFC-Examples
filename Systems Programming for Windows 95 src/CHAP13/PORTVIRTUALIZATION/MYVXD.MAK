# MYVXD.MAK -- Make file for MYVXD.VXD

all: myvxd.vxd

myvxd.obj: $*.asm
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -Zm -Zi -DMASM6 -DDEBUG $*.asm

myvxd.vxd: $*.obj $*.def
   link @<<
/vxd /nod
/debug /debugtype:map
/map:$*.map
/def:$*.def
$*.obj
<<
    \winice95\msym $*
