This code disc accompanies Systems Programming for Windows 95 by Walter Oney.

Long Filenames:
--------------
Real-mode CD-ROM drivers under Windows 95 truncate all long filenames on 
a CD.  If your CD-ROM drive uses a real-mode driver, you will not be able 
to see all of the directories or files on this disc.  (If this is the case, 
you should contact your CD-ROM drive manufacturer for an updated Windows 95 
driver.)  You can still use the companion disc, however, by following the 
installation instructions below; files will be copied from a special SETUP 
directory on the companion CD to your hard disk, being renamed with the 
appropriate long file name in the process.  You can then browse the files 
on your hard disk.  Alternatively, you can browse the files using their 
8.3 aliases from within the SETUP directory on the CD.

Installing the Companion CD files on your hard disk:
---------------------------------------------------
To install the program files on your hard disk, run SETUP.EXE in the root
directory of the CD. Then follow the onscreen instructions.  The DDK help 
files and annotation files will not be copied to your hard disk.

Help Files:
----------
On this disc, you will find a copy of the help file that accompanies
the Microsoft Windows 95 Device Driver Kit (the DDK). You'll also find
the author's annotations (a .ANN file) for that help file. You should
copy the .ANN file into your own \<Windows>\Help directory. You can leave
the help files (DDPR.HLP and DDPR.CNT) on the CD-ROM, or you can copy 
them to your hard disk, as you please.  Please note that the help files
are from the April, 1996 version of the DDK.  More current versions are
available quarterly from MSDN, but the annotations file may not be 
usable for versions other than the ones included on this disc.  When 
the help file is updated on the DDK, new versions of the annotations 
file will be made available through the World Wide Web at the following 
address:
	http://www.tiac.net/users/waltoney


Also note that if you have existing annotations of your own for the 
DDPR.HLP file, you should not overwrite your DDPR.ANN file.  A complete
list of the contents of the DDPR.ANN file is included in the DDPRANN.TXT
file.

README Files for Samples:
------------------------
This disc also contains sample programs for most of the chapters in the
book. Each subdirectory has a README.TXT that explains which samples are
in that subdirectory, and each sample directory below that has its own
README.TXT explaining how to build and test that sample.

Building Samples:
----------------
Most of the sample programs rely on the DDK and on Microsoft Visual C++ 
version 4.0. (See the note below on MSVC 4.1.) Install both products
according to their respective directions. When you install the DDK,
modify the instructions you find in READVXD.TXT by copying the LINK.*
and ML.* files into the DDK\BIN directory you end up with after
installing the DDK. Do *NOT* overwrite the MSVC linker as suggested
by READVXD.TXT, or you won't be able to build Win32 applications anymore.

The MAK files for the samples use absolute pathnames for three tools.
You will have to modify each MAK file to correspond to your own
configuration. Specifically:

    1.  My MAK files reference C:\DDK\BIN\LINK. Change this to point
        to wherever the DDK version of LINK.EXE ends up on your
        system.

    2.  My MAK files run a utility named FIXMAP, which you'll find in the
        root directory of this disc. FIXMAP compensates for a bug in the
        linker that causes line number information for C++ files to end
        up incorrectly attributed to header files. If you copy FIXMAP
        to someplace on the path, you can just leave these commands
        alone. Otherwise, or if you don't care about debugging samples
        built from C++ files, remove them from the MAK files.

        FIXMAP is not a perfect tool, so please don't try to use it beyond
        its limited purpose of fixing up maps for C++ VxDs.

    3.  My MAK files reference C:\WINICE95\MSYM. If you own a copy of
        Soft-Ice/W for Windows 95, change the pathname to match your
        setup. Otherwise, remove the commands.

You can most easily use the Microsoft Developer Studio for building the
sample VxDs if you modify the Directory paths to point to the DDK
BIN, INC32, and LIB directories, but make sure you leave the MSDEV\BIN 
directory ahead of the DDK\BIN directory--otherwise, you will have to 
reset the Directory path in order to build Win32 applications. To modify
the Directory paths in Developer Studio, choose the Tools Options command,
then select the Directories tab in the Options dialog box. In the Show
Directories For listbox, select Executable Files to add the \DDK\BIN 
directory, select Include Files to add the \DDK\INC32 directory, and 
select Library Files to add the \DDK\LIB directory. (Some projects also 
require \DDK\BLOCK\INC in the Include Files list.)

If you prefer to build the projects from a command prompt, you will 
need to set the PATH, INCLUDE, and LIB environment variables first, using
a Set command. In general:

    PATH should be set to include \MSDEV\BIN;\DDK\BIN plus anything else 
    your system needs to function.

    INCLUDE should be set to include \DDK\INC32;\MSDEV\INCLUDE plus 
    anything else you normally need.  Some projects also require
    \DDK\BLOCK\INC.

    LIB should be set to include \DDK\LIB. Nothing else is needed for 
    building VxDs.

MSVC 4.1:
--------
WARNING: Version 4.1 of Microsoft Visual C++ cannot be used for building
VxDs. It contains a bug that causes incorrect code to be generated for 
inline assembler references to enumerated constants. This bug means that
every VxDCall macro or variant generates bad code that will cause a 
run-time crash.  In other words, you can't use MSVC 4.1 to build VxDs with
the DDK.  A fix is planned for a later version of MSVC.

VtoolsD Samples:
---------------
A few of the sample programs require VtoolsD for Windows 95 from Vireo
Software, Inc. If you don't own that product, you can probably adapt
many of those samples to the DDK by following this procedure:

    1.  Replace the single #include statement in the VxD main program
        with a series of #include statements for DDK headers. Chapter
        7 lists the headers you're likely to need.

    2.  Remove the device control procedure and associated declarations
        from the VxD main program. Create a DevCtrl.asm to contain
        the Declare_Virtual_Device macro and the device control procedure.
        Once again, Chapter 7 shows you how to do this.

In any case, you can probably glean the instructional meat of the VtoolsD
samples without ever building and testing them.
