========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : Msdi
========================================================================


AppWizard has created this Msdi application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your Msdi application.

Msdi.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMsdiApp application class.

Msdi.cpp
    This is the main application source file that contains the application
    class CMsdiApp.

Msdi.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Developer Studio.

res\Msdi.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file Msdi.rc.

res\Msdi.rc2
    This file contains resources that are not edited by Microsoft 
	Developer Studio.  You should place all resources not
	editable by the resource editor in this file.

Msdi.reg
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.

Msdi.clw
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

MsdiDoc.h, MsdiDoc.cpp - the document
    These files contain your CMsdiDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CMsdiDoc::Serialize).

MsdiView.h, MsdiView.cpp - the view of the document
    These files contain your CMsdiView class.
    CMsdiView objects are used to view CMsdiDoc objects.

res\MsdiView.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CMsdiDoc class. This icon is included by the main
    resource file Msdi.rc.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Msdi.pch and a precompiled types file named StdAfx.obj.

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
MSDI notes:

MsdiApp.cpp, MsdiApp.h.
	This is the standard MSDI application interface. Use this in place
	of CWinApp.

MSDIFrm.cpp, MSDIFrm.h
	This is the frame for the first view. Use this to close all views whith
	the system menu or the close button of the main view.

ViewFrm.cpp, ViewFrm.h
	This is the frame for all other views except the main view. Use this to
	create new windows of this type and correct the title. These views can be
	closed separatly with the system menu or close button.

