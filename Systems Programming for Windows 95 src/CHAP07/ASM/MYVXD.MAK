# MYVXD.MAK -- MAKE file for MYVXD.VXD

all: myvxd.vxd

myvxd.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -DMASM6 -Zd -DDEBUG $*.asm

myvxd.vxd: $*.obj $*.def
   c:\ddk\bin\link @<<
/vxd /nod
/map:$*.map
/def:$*.def
$*.obj
<<
