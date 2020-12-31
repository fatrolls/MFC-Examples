// DkToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "DkToolBar.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDkToolBar
// DKTODO:
// In the implementation file(s) of the owner(s) of your toolbars, you must
// add an array of static CToolBarInfo objects.  The CToolBarInfo array must
// be populated as follows:
// CToolBarInfo CParentWnd::toolBarInfoTable[] =
// {{ TBBUTTON }, Text to be displayed in customize dialog for this button},
// {{ TBBUTTON }, Text to be displayed in customize dialog for this button},
// ...

// stolen from somewhere in BarTool.cpp
struct CToolBarData
{
	WORD wVersion;
	WORD wWidth;
	WORD wHeight;
	WORD wItemCount;
	//WORD aItems[wItemCount]

	WORD* items()
		{ return (WORD*)(this+1); }
};

/////////////////////////////////////////////////////////////////////////////
// CDkToolBar message map
BEGIN_MESSAGE_MAP(CDkToolBar, CToolBar)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDkToolBar)
	ON_COMMAND(ID_POPUP_CUSTOMIZE, OnPopupCustomize)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_BEGINADJUST, OnToolBarBeginAdjust)
	ON_NOTIFY_REFLECT(TBN_BEGINDRAG, OnToolBarBeginDrag)
	ON_NOTIFY_REFLECT(TBN_CUSTHELP, OnToolBarCustomHelp)
	ON_NOTIFY_REFLECT(TBN_ENDADJUST, OnToolBarEndAdjust)
	ON_NOTIFY_REFLECT(TBN_ENDDRAG, OnToolBarEndDrag)
	ON_NOTIFY_REFLECT(TBN_GETBUTTONINFO, OnToolBarGetButtonInfo)
	ON_NOTIFY_REFLECT(TBN_QUERYDELETE, OnToolBarQueryDelete)
	ON_NOTIFY_REFLECT(TBN_QUERYINSERT, OnToolBarQueryInsert)
	ON_NOTIFY_REFLECT(TBN_RESET, OnToolBarReset)
	ON_NOTIFY_REFLECT(TBN_TOOLBARCHANGE, OnToolBarChange)
END_MESSAGE_MAP()

// This function calculates the number of buttons on the toolbar.
int CDkToolBar::NButtons()
{
	return nButtons;
}

CDkToolBar::CDkToolBar()
{
	// CDkToolBar TODO:  add extra initialization code here
}

CDkToolBar::~CDkToolBar()
{
	// CDkToolBar TODO:  add extra uninitialization code here
}

// This function creates the toolbar and associates it with its parent.  Also,
// the registry key to be used for saving and restoring the toolbar's state is
// stored for later use.
BOOL CDkToolBar::Create(CWnd *pParentWnd, DWORD dwStyle, UINT nID,
						CToolBarInfo *tbInfo, CString regSubKey,
						CString regValue, HKEY regKey)
{
		BOOL		 success;		// indicates if the toolbar was created

	// if default processing is ok
	if (CToolBar::Create(pParentWnd, dwStyle, nID))
	{
		// indicate success
		success = TRUE;

		// modify the style to include adjustable
		ModifyStyle(0, CCS_ADJUSTABLE);

		// keep the pointer to the toolbar information
		toolBarInfo = tbInfo;
		
		// if there aren't any buttons to customize
		if (!tbInfo)
		{
			nButtons = 0;
		}
	}

	// else default processing failed
	else
	{
		TRACE0("Failed to create toolbar\n");
		success = FALSE;
	}

	// keep record of where our registry entry lives
	registryKey = regKey;
	registrySubKey = regSubKey;
	registryValue = regValue;

	// indicate success
	return success;
}

// This function saves the state (visible buttons, toolbar position, etc.)
// of the toolbar, using the registry key provided to the Create(...) function.
void CDkToolBar::SaveState()
{
	// if there is an associated registry subkey
	if (registrySubKey.GetLength())
	{
		// save the toolbar state to the registry
		GetToolBarCtrl().SaveState(registryKey, registrySubKey, registryValue);
	}
}

// This function restores the state (visible buttons, toolbar position, etc.)
// of the toolbar, using the registry key provided to the Create(...) function.
void CDkToolBar::RestoreState()
{
	// if there is an associated registry subkey
	if (registrySubKey.GetLength())
	{
		// restore the toolbar state from the registry
		GetToolBarCtrl().RestoreState(registryKey, registrySubKey, registryValue);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDkToolBar message handlers

// This function is called when the user begins dragging a toolbar
// button or when the customization dialog is being populated with
// toolbar information.  Basically, *result should be populated with
// your answer to the question, "is the user allowed to delete this
// button?".
void CDkToolBar::OnToolBarQueryDelete(NMHDR *notify, LRESULT *result)
{
	// if we're not floating - user can delete anything
	*result = !IsFloating();
}

// This function is called when the user begins dragging a toolbar
// button or when the customization dialog is being populated with
// toolbar information.  Basically, *result should be populated with
// your answer to the question, "is the user allowed to insert a
// button to the left of this one?".
void CDkToolBar::OnToolBarQueryInsert(NMHDR *notify, LRESULT *result)
{
	// if we're not floating - user can insert anywhere
	*result = !IsFloating();
}

// This function is called whenever the user makes a change to the
// layout of the toolbar.  Calling the mainframe's RecalcLayout forces
// the toolbar to repaint itself.
void CDkToolBar::OnToolBarChange(NMHDR *notify, LRESULT *result)
{
	// force the frame window to recalculate the size
	GetParentFrame()->RecalcLayout();
}

// This function is called when the user begins dragging a toolbar button.
void CDkToolBar::OnToolBarBeginDrag(NMHDR *notify, LRESULT *result)
{
}

// This function is called when the user has completed a dragging operation.
void CDkToolBar::OnToolBarEndDrag(NMHDR *notify, LRESULT *result)
{
}

// This function is called when the user initially calls up the toolbar
// customization dialog box.
void CDkToolBar::OnToolBarBeginAdjust(NMHDR *notify, LRESULT *result)
{
}

// This function is called when the user clicks on the help button on the
// toolbar customization dialog box.
void CDkToolBar::OnToolBarCustomHelp(NMHDR *notify, LRESULT *result)
{
}

// This function is called when the user dismisses the toolbar customization
// dialog box.
void CDkToolBar::OnToolBarEndAdjust(NMHDR *notify, LRESULT *result)
{
	// save the state of the toolbar for reinitialization
	SaveState();
}

// This function is called to populate the toolbar customization dialog box
// with information regarding all of the possible toolbar buttons.
void CDkToolBar::OnToolBarGetButtonInfo(NMHDR *notify, LRESULT *result)
{
		TBNOTIFY		*tbStruct;		// data needed by customize dialog box

	// init the pointer
	tbStruct = (TBNOTIFY *)notify;

	// if the index is valid
	if (0 <= tbStruct->iItem && tbStruct->iItem < NButtons())
	{
		// copy the stored button structure
		tbStruct->tbButton = toolBarInfo[tbStruct->iItem].tbButton;

		// copy the text for the button label in the dialog
		strcpy(tbStruct->pszText, toolBarInfo[tbStruct->iItem].btnText);

		// indicate valid data was sent
		*result = TRUE;
	}

	// else there is no button for this index
	else
	{
		*result = FALSE;
	}
}

// This function is called when the user clicks on the reset button on the
// toolbar customization dialog box.
void CDkToolBar::OnToolBarReset(NMHDR *notify, LRESULT *result)
{
	// restore the toolbar to the way it was before entering customization
	RestoreState();
}

// This function initializes and tracks the toolbar pop-up menu
void CDkToolBar::OnContextMenu(CWnd*, CPoint point)
{
		CMenu		 menu;		// toolbar right-click menu

	// if we have extensive information regarding the toolbar
	if (toolBarInfo && !IsFloating())
	{
		// load the menu from resources
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_DK_TOOL_BAR));

		/// track the menu as a pop-up
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		// force all message in this menu to be sent here
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			this);
	}
}

// This function checks for shift-F10 to pop-up the right-click menu in the
// toolbar.
BOOL CDkToolBar::PreTranslateMessage(MSG* pMsg)
{
		BOOL		 handled;		// indicates if message was handled

	// if user hit shift-F10 or if he hit the context menu key on his keyboard
	if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) &&
		(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||
		(pMsg->message == WM_CONTEXTMENU))
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		CPoint point = rect.TopLeft();
		point.Offset(5, 5);
		OnContextMenu(NULL, point);

		handled = TRUE;
	}

	// else let the base class handle this one
	else
	{
		handled = CToolBar::PreTranslateMessage(pMsg);
	}
	return handled;
}

// This function is called when the user clicks on the 'customize' menu item of
// the toolbar's right-click menu.
void CDkToolBar::OnPopupCustomize() 
{
	// let user play with customization dialog
	GetToolBarCtrl().Customize();
}

/*
void CDkToolBar::OnPopupIconsandtext() 
{
		int			 i;			// general index
		CRect		 box;		// box holding toolbar button

	// set the text labels for the buttons
	for (i = 0; i < NButtons(); i++)
	{
		// if this isn't a separator
		if (toolBarInfo[i].tbButton.idCommand != ID_SEPARATOR)
		{
			SetButtonText(CommandToIndex(toolBarInfo[i].tbButton.idCommand),
				toolBarInfo[i].btnText);
		}
	}

	// if we don't already know the button with text sizes
	if (txtBtnSize.cx == -1)
	{
		// calculate the width of the toolbar
		for (i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
		{
			// grab the size of this button
			GetItemRect(i, box);

			// if this is the first time through
			if (!i)
			{
				// keep this as the max sized button
				txtBtnSize.cx = box.Width();
				txtBtnSize.cy = box.Height();
			}

			// else this isn't the first time
			else
			{
				// if this button is bigger than the biggest so far
				if (box.Width() > txtBtnSize.cx)
				{
					txtBtnSize.cx = box.Width();
				}
				if (box.Height() > txtBtnSize.cy)
				{
					txtBtnSize.cy = box.Height();
				}
			}
		}
	}

	// set the new size of the toolbar and force a recalc
	SetSizes(txtBtnSize, defImgSize);

	// if we're floating
	if (IsFloating())
	{
		// force the miniframe window to recalculate the size
		((CMiniFrameWnd *)GetParentFrame())->RecalcLayout();
	}

	// else we're docked
	else
	{
		// force the frame window to recalculate the size
		((CMainFrame *)AfxGetMainWnd())->RecalcLayout();
	}

	// save the current state of the toolbar
	SaveState();
}

void CDkToolBar::OnPopupIconsonly() 
{
	// if there are any entries in the string map
	if (m_pStringMap)
	{
		m_pStringMap->RemoveAll();
		delete m_pStringMap;
		m_pStringMap = NULL;
	}

	// restore the toolbar sizes to their defaults
	SetSizes(defBtnSize, defImgSize);

	// if we're floating
	if (IsFloating())
	{
		// force the miniframe window to recalculate the size
		((CMiniFrameWnd *)GetParentFrame())->RecalcLayout();
	}

	// else we're docked
	else
	{
		// force the frame window to recalculate the size
		((CMainFrame *)AfxGetMainWnd())->RecalcLayout();
	}

	// save the current state of the toolbar
	SaveState();
}
*/

void CDkToolBar::OnDestroy() 
{
	// save the current state of the toolbar
	SaveState();

	// default processing
	CToolBar::OnDestroy();
}
