This is another way to draw a menu with bitmaps item.
Basically, this thing was created to let the user see visually the correspondence of
a menu item and a toolbar button, so that he can learn easily the meanings of sometime
strange button drawing.

Now, the Visual C++ give us that new nice toolbar resources .. why bother with icons or
bitmaps and link them to menus while we can automatically "connect" the toolbar resource
to them ?

So I wrote a small class, CMenuSpawn, which takes care with some help from FrameWnd of
menu remapping and drawing.


What has been updated, changed, added since the last version:
- fix some memory/resource leaks reported from BoundsChecker but not from Msdev (I'm not an owner of
  BoundsChecker - thanks to H.Tome, C. Schmidt, and all the others who rerport them
- added support for shortcut for menu items and popups
- added support for a user font for the menu
- added support for user defined color of menu items
- added support for using bitmap as menu background
- (hope to have) fixed the bug who sometimes make the text (especially of popups) disappear and/or
  enlarge VERY much the popup - however, yet to understand why it did so :)
- added a contructor with a boolean value to be used when creating popup menu (look at
  demo, in the view right mouse click)
- added some base classes for CFrameWnd, CMDIFrameWnd and CMDIChildFrameWnd to make it easier the work;
  you can now simply rederive your CMainFrame from CSpawnFrameWnd or CSpawnMDIFrameWnd and eventually
  your CChildFrame from CSpawnMDIChildWnd to get the WM_MEASUREITEM, WM_DRAWITEM, WM_INITMENU, WM_INITMENUPOPUP
  handled

Now I will explain how to use it in a MDI application:


Step 1: including files
We need to include the CSpawnMenu class in our application and the Bitmap resource named
IDB_MENUCHK from the sample application which comes along (it will be used to draw
"check marks" aside menu item which need it - you can freely change it).



Step 2: handling frame messages
We also need to manage some of the frame windows handler; we have 2 ways to do this. The
simplest is to derive the CMainFrame from the CSpawnMDIFrameWnd class instead of CMDIFrameWnd.
This means you have to (using Search/Replace) replace all istance of CMDIFrameWnd with
CSpawnMDIFrameWnd (and of course include in your project file the files
SpawnMDIFrameWnd.cpp and SpawnMDIFrameWnd.h). You will also need to do this for the
CChildFrame class, deriving from CSpawnMDIChildWnd and including SpawnMDIChildWnd.cpp/.h.
The other way is to look at how this CSpawnFramexxx classes are been made and copy it
(that means putting a CMenuSpawn member in the frame class header and handling the
WM_DRAWITEM, WM_MEASUREITEM, WM_MENUCHAR, WM_INITMENU and WM_INITMENUPOPUP).

If you are making an SDI application instead of an MDI, derive the CFrameWnd from
CSpawnFrameWnd and include the SpawnFrameWnd.cpp/.h files.



Step 3: initializing the CSpawnClass
We need to modify the CMainFrame class in this way:
- add a CMenuSpawn cSpawn instance in the include file
- initialize the CMenuSpawn class in the CMainFrame constructor (cSpawn.LoadToolBarResource(IDR_MAINFRAME))
  this will load the toolbar resource into the class; you can alse use the AddToolBarResource function
  to add more than toolbar resource to the class. In the demo app, I add a toolbar for the system menu

CMainFrame::CMainFrame()
{
	cSpawn.LoadToolBarResource(IDR_MAINFRAME);
}



Step 4: Note to Stingray Software's Objective Toolkit Pro users
If you are using the OT Pro, maybe along with the SECMenuBar to obtain Office97 menu
button look and feel, you will also need to override the WindowProc virtual of the
CMainFrame as noted below:

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message != WM_MEASUREITEM) return SECFrameWnd::WindowProc(message, wParam, lParam);
	else return CFrameWnd::WindowProc( message, wParam, lParam );	
}

If you are using another OTPro class other than SECFrameWnd as base class, change SECFrameWnd
to reflect your base class.

And that's all to have basic coolmenu support.


Looking at the demo application, which implements an MDI Edit application, you will find a way
to implement popup coolmenu.


Here follows a small description of the most useful function of the CSpawnMenu class:

bool MeasureItem(..)
  To be called from the CWnd OnMeasureItem(..); call the base class if it return false

bool DrawItem(..)
  To be called from the CWnd OnDrawItem(..); call the base class if it return false

bool LoadToolBarResource(unsigned int resId)
  Load a toolbar resource in the class; an array of command id will be created and
  mapped to index of an imagelist

bool AddToolBarResource(unsigned int resId)
  Add a toolbar resource to the class; works as the LoadToolBarResource

void RemapMenu(CMenu * pMenu)
  Makes all the items of the menu OwnerDraw, (eventually) maps them with the appropiate
  images index based on the item command id; has to be called from the WM_INITMENU and
  WM_INITPOPUPMENU and before the TrackPopupMenu function

void EnableMenuItems(CMenu * pMenu, CWnd * pWnd)
  Use the MFC command enabler mechanism to enable/disable menu items; need the pointer of
  the menu and the pointer of the CWnd of which the command enablers are to be used;
  it is designed to be used with popups menu from the right button click in Views
  (see the CEditView in sample apps for an example)

bool SetFont(LOGFONT * lf) *New*
  If someone, for evil pourpose, want to use a different font to draw the menu items,
  it is possible to call this function (before the menu are displayed, for example in the
  CMainFrame contructor after the LoadToolBarResource()). Look at the demo, there is commented
  code.

bool FindKeyboardShortcut(UINT nChar, UINT nFlags, CMenu * pMenu, LRESULT & lRes) *New*
  This is needed to handle the shortcuts when the menu is displayed (the &Letter shortcurs); you
  need to call it in response to WM_MENUCHAR messages of CMainFrame, CChildFrame if MDI app, and
  CView if using Spawn popups; the usage is a bit complex, look at demo and copy/paste the
  code.

void SetTextColor(const COLORREF crNormal, const COLORREF crSelected) *New*
  You can use this to specify different colors from default for the normal and
  selected menu items

void SetBackBitmap(const int iRes) *New*
void SetBackBitmap(const int iRes, COLORREF crBackColor) *New*
  Now you can use bitmaps as background for menu using one of this 2 function. The first
  simply set a bitmap, the second change the color you specify to the menu background
  obtaining a simple transparency. Pay attention to the bitmap you use, which can make
  the menu text unreadable; you may need to use SetFont to set a bold font to read the
  text and the SetTextColor to use brighter color if you use strange bitmaps.
  In the demo, bitmap are enabled in the app menu, and disabled in the popup of the view.
  To see how to disable it, comment the SetBackBitmap in the CMainFrame constructor of the
  demo.



The function for drawing disabled menu items has been stolen from the CToolbarEx of
Joerg Koenig (thanx!).

Very thanks to Craig Schmidt for support!


Feel free to use and modify this class with all your software - I will only be glad to know
for which apps it will be used and of any improvement you will do to it!

