The DPMIDEMO sample illustrates a number of common DPMI calls. The sample
consists of two files:

    DPMIDEMO.C is the test program itself. It reads like the main program
    of any 16-bit real-mode program, except that it contains INT 31h calls
    that only work from protected mode.

    LOADER.ASM is a bootstrap loader that inserts itself into the normal
    C runtime startup sequence in order to switch to protected mode. Once
    in protected mode, LOADER uses DPMI and extended-DOS calls to relocate
    all the segment fixups in its EXE file to refer to equivalent selectors
    instead. Thus, LOADER is a general purpose module that will make any
    real-mode MSVC program into a DOS-extended program.

It's easiest to build this sample from an MS-DOS prompt. Set your path to
include MSVC 1.52 (i.e., the 16-bit compiler) and MASM 6.11. You'll also 
need to point your PATH, INCLUDE, and LIB environment variables to the appropriate MSVC 1.52 directories. Build by issuing the command "nmake -f
dpmidemo.mak".

Test by issuing the DPMIDEMO command from an MS-DOS prompt. After each
section of tests, the program pauses so you can see the results. One of
the tests involving hooking INT 1Bh (the BIOS Ctrl-Break interrupt); watch
for this and hit Ctrl-Break in time to see the hook actually operate.
