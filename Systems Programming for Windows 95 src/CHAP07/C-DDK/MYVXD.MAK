# MYVXD.MAK -- MAKE file for sample VxD

all: myvxd.vxd

devdcl.obj: $*.asm
   ml -coff -DBLD_COFF -DIS_32 -W2 -c -Cx -DMASM6 -Zd -DDEBUG $*.asm

myvxd.obj: $*.c
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

myvxd.vxd: devdcl.obj $*.obj $*.def
   c:\ddk\bin\link @<<
-machine:i386 -debug:none -pdb:none -def:$*.def -out:$@
-map:$*.map -vxd vxdwraps.clb
devdcl.obj myvxd.obj
<<
