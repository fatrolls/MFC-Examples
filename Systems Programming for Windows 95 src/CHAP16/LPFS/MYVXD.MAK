all: lpfs.vxd

.asm.obj:
   ml -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -Zi -DDEBUG $*.asm

.c.obj:
   cl -c -Gs -Zdpl -Od -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.c

.cpp.obj:
   cl -c -Gs -Zdpl -Odb2 -D_X86_ -YX -W3 -DDEBLEVEL=1 -DBLD_COFF -DDEBUG -DIS_32 $*.cpp

FileSystem.obj:      $*.cpp $*.h ifs.h ifsmgr.h
LocalFileSystem.obj: $*.cpp $*.h ifs.h ifsmgr.h FileSystem.h
lpfs.obj:	     $*.cpp $*.h ifs.h ifsmgr.h FileSystem.h LocalFileSystem.h

lpfs.vxd : devdcl.obj lpfs.obj $*.def FileSystem.obj LocalFileSystem.obj
   c:\ddk\bin\link @<<
-machine:i386 -def:$*.def -out:$@
-debug -debugtype:map
-map:$*.map -vxd vxdwraps.clb -nodefaultlib
devdcl.obj lpfs.obj FileSystem.obj LocalFileSystem.obj
<<
   ..\..\fixmap $*
   c:\winice95\msym $*
