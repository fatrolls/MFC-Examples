# filename : hello.mak
# make file for hello.exe (MFC 4.2 Application)
# usage : nmake hello.mak (Visual C++ 5.0)

Hello.exe : StdAfx.obj Hello.obj Hello.res
  link.exe /nologo /subsystem:windows /incremental:no \
           /machine:I386 /out:"Hello.exe" \
           Hello.obj StdAfx.obj Hello.res \
           msvcrt.lib kernel32.lib user32.lib gdi32.lib mfc42.lib

StdAfx.obj : StdAfx.cpp StdAfx.h
  cl.exe /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" \
         /D "_AFXDLL" /D "_MBCS" /Fp"Hello.pch" /Yc"stdafx.h"  \
         /c StdAfx.cpp

Hello.obj : Hello.cpp Hello.h StdAfx.h
  cl.exe /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" \
         /D "_AFXDLL" /D "_MBCS" /Fp"Hello.pch" /Yu"stdafx.h"  \
         /c Hello.cpp

Hello.res : Hello.rc Hello.ico jjhour.ico
  rc.exe /l 0x404 /Fo"Hello.res" /D "NDEBUG" /D "_AFXDLL" Hello.rc

