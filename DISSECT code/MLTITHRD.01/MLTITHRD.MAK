# filename : mltithrd.mak
# make file for mltithrd.exe  (Multiple Threads Demo in Win32)
# usage : nmake mltithrd.mak cpu=i386 (Microsoft C/C++ 9.00) (Visual C++ 2.0)
# usage : nmake mltithrd.mak  (Microsoft C/C++ 10.00) (Visual C++ 4.0)

# NMAKE macros for Win32 apps
!include <ntwin32.mak>

all: mltithrd.exe

# Update the resource.
mltithrd.res: mltithrd.rc mltithrd.h
    rc mltithrd.rc

# Update the object file -- use the $(cvarsmt) macro.
mltithrd.obj: mltithrd.c mltithrd.h
    $(cc) $(cflags) $(cvarsmt) mltithrd.c

# Update the executable file and add the resource file.
mltithrd.exe: mltithrd.obj mltithrd.res
    $(link) $(guilflags) -out:mltithrd.exe mltithrd.obj mltithrd.res \
            $(guilibsmt)
