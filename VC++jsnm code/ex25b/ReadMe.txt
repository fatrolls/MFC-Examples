========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : ex25b
========================================================================


AppWizard has created this ex25b application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your ex25b application.

ex25b.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CEx25bApp application class.

ex25b.cpp
    This is the main application source file that contains the application
    class CEx25bApp.

ex25b.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Developer Studio.

res\ex25b.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file ex25b.rc.

res\ex25b.rc2
    This file contains resources that are not edited by Microsoft 
	Developer Studio.  You should place all resources not
	editable by the resource editor in this file.

ex25b.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the
    CMainFrame class.  Edit this toolbar bitmap along with the
    array in MainFrm.cpp to add more toolbar buttons.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

ex25bDoc.h, ex25bDoc.cpp - the document
    These files contain your CEx25bDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CEx25bDoc::Serialize).

ex25bView.h, ex25bView.cpp - the view of the document
    These files contain your CEx25bView class.
    CEx25bView objects are used to view CEx25bDoc objects.

res\ex25bDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CEx25bDoc class.  This icon is included by the main
    resource file ex25b.rc.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ex25b.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Developer Studio reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC40XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC40DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
