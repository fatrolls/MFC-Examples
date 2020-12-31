all: myvxd.vxd

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

.cpp.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.cpp

myvxd.obj: myvxd.h ifsmgr.h

myvxd.vxd : devdcl.obj myvxd.obj $*.def
   c:\ddk\bin\link @<<
-machine:i386 -def:$*.def -out:$@
-merge:_CRT$$XCU=.CRT$$XCU
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
devdcl.obj myvxd.obj
<<
   fixmap $*
   c:\winice95\msym $*
