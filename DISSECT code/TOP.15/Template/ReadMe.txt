========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : $$Root$$
========================================================================


$$IF(PROJTYPE_DLL)
AppWizard has created this $$Root$$ DLL for you.  This DLL not only
demonstrates the basics of using the Microsoft Foundation classes but
is also a starting point for writing your DLL.

This file contains a summary of what you will find in each of the files that
make up your $$Root$$ DLL.
$$ELSE
AppWizard has created this $$Root$$ application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your $$Root$$ application.
$$ENDIF //PROJTYPE_DLL

$$IF(PROJTYPE_DLL)
$$IF(EXTDLL)
$$Root$$.cpp
    This is the main DLL source file that contains the definition of
	DllMain().
$$ELSE //!EXTDLL
$$Root$$.h
	This is the main header file for the DLL.  It declares the
	$$APP_CLASS$$ class.

$$Root$$.cpp
	This is the main DLL source file.  It contains the class $$APP_CLASS$$.
$$IF(AUTOMATION)
	It also contains the OLE entry points required of inproc servers.
$$ENDIF //AUTOMATION
$$ENDIF //EXTDLL

$$IF(AUTOMATION)
$$Root$$.odl
    This file contains the Object Description Language source code for the
    type library of your DLL.
$$ENDIF //AUTOMATION
$$ELSE //!PROJTYPE_DLL
$$Root$$.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    $$APP_CLASS$$ application class.

$$Root$$.cpp
    This is the main application source file that contains the application
    class $$APP_CLASS$$.
$$ENDIF //PROJTYPE_DLL

$$Root$$.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Developer Studio.
$$IF(TARGET_MAC)

$$R_FILE$$.r
    This file contains all of the Macintosh-specific resources for
$$IF(PROJTYPE_DLL)
    your DLL.
$$ELSE //!PROJTYPE_DLL
    your application.  For example, it contains the SIZE resource which you
    can edit if you wish to change the memory partition size.  You can
    also edit the FREF and BNDL resources when adding new document
    types.
$$ENDIF //PROJTYPE_DLL
$$ENDIF //TARGET_MAC
$$IF(!PROJTYPE_DLL)

res\$$Root$$.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file $$Root$$.rc.
$$ENDIF //!PROJTYPE_DLL

res\$$Root$$.rc2
    This file contains resources that are not edited by Microsoft 
	Developer Studio.  You should place all resources not
	editable by the resource editor in this file.
$$IF(!PROJTYPE_DLL)
$$IF(CONTAINER_SERVER || FULL_SERVER || MINI_SERVER || AUTOMATION || HAS_SUFFIX)

$$Root$$.reg
    This is an example .REG file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .REG
$$IF(PROJTYPE_DLG)
    file to go along with your application.
$$ELSE //!DLG
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.
$$ENDIF //PROJTYPE_DLG
$$ENDIF //OLE || HAS_SUFFIX
$$IF(TARGET_MAC)
$$IF(CONTAINER_SERVER || FULL_SERVER || MINI_SERVER || AUTOMATION)

$$root$$Mac.reg
    This is an example Macintosh registration file that shows you the kind
    of settings the framework will set for you.  You'll notice this contains
    mainly the same information as $$Root$$.reg, with some small exceptions
    and with a slightly different format.  If you wish, you may copy it over
    to your Macintosh with mfile:
        mfile copy -l -t TEXT -c RgEd $$root$$Mac.reg ":<MacintoshPath>"
    You may then double-click on the Macintosh file you just copied over, and
    that will launch the Macintosh registration database editor and merge the
    file into the database.  Remember, the framework will automatically enter
    this information into the Macintosh registration database the first time
    your application is run.  Still, your setup program should enter this
    information into the database when your application is installed.
$$ENDIF //SERVERS,AUTOMATION
$$ENDIF //TARGET_MAC
$$ENDIF //!PROJTYPE_DLL
$$IF(AUTOMATION)

$$Root$$.odl
    This file contains the Object Description Language source code for the
    type library of your application.
$$ENDIF //AUTOMATION
$$IF(PROJTYPE_DLL)

$$Root$$.def
    This file contains information about the DLL that must be
    provided to run with Microsoft Windows.  It defines parameters
    such as the name and description of the DLL.  It also exports
	functions from the DLL.
$$ENDIF //PROJTYPE_DLL

$$Root$$.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

$$IF(!PROJTYPE_DLL)
$$IF(!PROJTYPE_DLG)
/////////////////////////////////////////////////////////////////////////////

For the main frame window:

$$FRAME_HFILE$$.h, $$FRAME_IFILE$$.cpp
    These files contain the frame class $$FRAME_CLASS$$, which is derived from
$$IF(PROJTYPE_MDI)
    CMDIFrameWnd and controls all MDI frame features.
$$ELSE
    CFrameWnd and controls all SDI frame features.
$$ENDIF

$$IF(TOOLBAR)
res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the
    $$FRAME_CLASS$$ class.  Edit this toolbar bitmap along with the
    array in $$FRAME_IFILE$$.cpp to add more toolbar buttons.
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)

res\IToolbar.bmp
	This bitmap file is used to create tiled images for the toolbar
	when your server application is in-place activated inside another
	container.  This toolbar is constructed in the $$IPFRAME_CLASS$$
	class.  This bitmap is similar to the bitmap in res\Toolbar.bmp
	except that it has many non-server commands removed.
$$ENDIF
$$ENDIF //TOOLBAR

/////////////////////////////////////////////////////////////////////////////

$$IF(!DB_NO_FILE)
AppWizard creates one document type and one view:

$$DOC_HFILE$$.h, $$DOC_IFILE$$.cpp - the document
    These files contain your $$DOC_CLASS$$ class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via $$DOC_CLASS$$::Serialize).
$$ELSE
AppWizard creates one view:
$$ENDIF

$$VIEW_HFILE$$.h, $$VIEW_IFILE$$.cpp - the view of the document
    These files contain your $$VIEW_CLASS$$ class.
$$IF(!DB_NO_FILE)
    $$VIEW_CLASS$$ objects are used to view $$DOC_CLASS$$ objects.
$$ENDIF
$$IF(CRecordView)
$$RECSET_HFILE$$.h, $$RECSET_IFILE$$.cpp - the recordset
	These files contain your $$RECSET_CLASS$$ class.
$$ENDIF

$$IF(PROJTYPE_MDI)
res\$$DOC_IFILE$$.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the $$DOC_CLASS$$ class.  This icon is included by the main
    resource file $$Root$$.rc.
$$ENDIF //MDI

$$IF(CONTAINER || FULL_SERVER || MINI_SERVER || CONTAINER_SERVER)
/////////////////////////////////////////////////////////////////////////////

AppWizard has also created classes specific to OLE

$$IF(CONTAINER || CONTAINER_SERVER)
$$CNTRITEM_HFILE$$.h, $$CNTRITEM_IFILE$$.cpp - this class is used to
	manipulate OLE objects.  They are usually displayed by your
	$$VIEW_CLASS$$ class and serialized as part of your $$DOC_CLASS$$ class.

$$ENDIF
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
$$SRVRITEM_HFILE$$.h, $$SRVRITEM_IFILE$$.cpp - this class is used to
	connect your $$DOC_CLASS$$ class to the OLE system, and optionally
	provide links to your document.
$$IPFRAME_HFILE$$.h, $$IPFRAME_IFILE$$.cpp - this class is derived
	from COleIPFrameWnd and controls all frame features during
	in-place activation.
$$ENDIF
$$ENDIF
$$ELSE //!!PROJTYPE_DLG

/////////////////////////////////////////////////////////////////////////////

$$IF(AUTOMATION)
AppWizard creates one dialog class and automation proxy class:
$$ELSE //!AUTOMATION
AppWizard creates one dialog class:
$$ENDIF //AUTOMATION

$$DLG_HFILE$$.h, $$DLG_IFILE$$.cpp - the dialog
    These files contain your $$DLG_CLASS$$ class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in $$Root$$.rc, which can be edited in Microsoft
	Developer Studio.
$$IF(AUTOMATION)

$$DLGAUTOPROXY_HFILE$$.h, $$DLGAUTOPROXY_IFILE$$.cpp - the automation object
    These files contain your $$DLGAUTOPROXY_CLASS$$ class.  This class
    is called the "automation proxy" class for your dialog, because it
    takes care of exposing the automation methods and properties that
    automation controllers can use to access your dialog.  These methods
    and properties are not exposed from the dialog class directly, because
    in the case of a modal dialog-based MFC application it is cleaner and
    easier to keep the OLE automation object separate from the user interface.
$$ENDIF //AUTOMATION

$$ENDIF //!PROJTYPE_DLG
$$IF(HELP)
/////////////////////////////////////////////////////////////////////////////

Help Support:

MakeHelp.bat
    Use this batch file to create your application's Help file, hlp\$$Root$$.hLP.

hlp\$$Root$$.hpj
    This file is the Help Project file used by the Help compiler to create
    your application's Help file.

hlp\*.bmp
    These are bitmap files required by the standard Help file topics for
    Microsoft Foundation Class Library standard commands.

hlp\*.rtf
    This file contains the standard help topics for standard MFC
    commands and screen objects.
$$ENDIF //HELP

$$ENDIF //!PROJTYPE_DLL
/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named $$Root$$.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Developer Studio reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.
$$IF(PROJTYPE_MDI || PROJTYPE_SDI || PROJTYPE_DLG)

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC40XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC40DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.
$$ENDIF //MDI,SDI,DLG

/////////////////////////////////////////////////////////////////////////////
