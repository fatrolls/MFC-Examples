all: myvxd.vxd

devdcl.obj: $*.asm
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 $*.asm

myvxd.obj: $*.c
   cl -c -Zdp -Gs -Zl -W3 $*.c

myvxd.vxd: devdcl.obj $*.obj $*.def
   link @<<
-machine:i386 -debug:none -pdb:none -def:$*.def -out:$@
-map:$*.map -vxd vxdwraps.clb
devdcl.obj myvxd.obj
<<
