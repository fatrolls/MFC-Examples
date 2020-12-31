// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PopupBar.h"

#include "OXColorPickerCtrl.h"

#include "BorderPickerCtrl.h"
#include "LineStylePickerCtrl.h"
#include "DashStylePickerCtrl.h"

#include "PopupBarDoc.h"
#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_TEXT_COLOR, OnUpdateCustomizeButtons)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_BORDER_COLOR, OnUpdateCustomizeButtons)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_BORDER_STYLE, OnUpdateCustomizeButtons)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_DASH_STYLE, OnUpdateCustomizeButtons)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_FILL_COLOR, OnUpdateCustomizeButtons)
	ON_UPDATE_COMMAND_UI(ID_CUSTOMIZE_LINE_STYLE, OnUpdateCustomizeButtons)
	ON_COMMAND(ID_WINDOW_MODAL, OnWindowModal)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_MODAL, OnUpdateWindowModal)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLBAR_FILE, ID_TOOLBAR_CUSTOMIZE, 
		OnUpdateViewToolbars)
	ON_COMMAND_RANGE(ID_TOOLBAR_FILE, ID_TOOLBAR_CUSTOMIZE, OnViewToolbars)
	ON_NOTIFY(TBN_DROPDOWN, ID_TOOLBAR_FILE, OnDropDownFileOpen)
	ON_NOTIFY(TBN_DROPDOWN, ID_TOOLBAR_CUSTOMIZE, OnDropDownCustomizeToolbar)
#if _MFC_VER>=0x0420
	// reflect message to provide custom draw functionality
	ON_NOTIFY(OXCTBN_CUSTOMDRAW,ID_TOOLBAR_CUSTOMIZE,OnCustomDraw)
#endif
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bModal=FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBarFile.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER, 
		ID_TOOLBAR_FILE) || !m_wndToolBarFile.LoadToolBar(IDR_TOOLBAR_FILE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBarFile.SetButtonStyle(2,m_wndToolBarFile.GetButtonStyle(2)|TBSTYLE_DROPDOWN);
	m_wndToolBarFile.SetDropDownArrow(TRUE);
	m_wndToolBarFile.UpdateSizes();

	if (!m_wndToolBarWindow.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER, 
		ID_TOOLBAR_WINDOW) || !m_wndToolBarWindow.LoadToolBar(IDR_TOOLBAR_WINDOW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBarWindow.IniSizes(CSize(16,16));
	m_wndToolBarWindow.SetList();
	m_wndToolBarWindow.SetDefaultTextColor(RGB(0,0,128));
	m_wndToolBarWindow.SetHotTextColor(RGB(0,0,255));
	// we want to use tooltips text in our CoolToolBar
	m_wndToolBarWindow.SetMaxTextRows(1);
	m_wndToolBarWindow.SetButtonTextFromID(COXCoolToolBar::TTID_TOOLTIP);
	m_wndToolBarWindow.UpdateSizes();

	if (!m_wndToolBarCustomize.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP, 
		ID_TOOLBAR_CUSTOMIZE) || !m_wndToolBarCustomize.LoadToolBar(IDR_TOOLBAR_CUSTOMIZE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	for (int nIndex=0; nIndex<m_wndToolBarCustomize.GetToolBarCtrl().GetButtonCount(); nIndex++)
	{
		m_wndToolBarCustomize.SetButtonStyle(nIndex,
			m_wndToolBarCustomize.GetButtonStyle(nIndex)|TBSTYLE_DROPDOWN);
	}
	m_wndToolBarCustomize.SetDropDownArrow(TRUE);
	m_wndToolBarCustomize.UpdateSizes();

	m_nFirstBorderStyleImage=m_wndToolBarCustomize.GetToolBarCtrl().
		AddBitmap(BORDERPICK_DEFINEDSTYLES,IDB_BORDER_TYPES);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBarFile.SetBarStyle(m_wndToolBarFile.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarWindow.SetBarStyle(m_wndToolBarWindow.GetBarStyle() |
		CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBarCustomize.SetBarStyle(m_wndToolBarCustomize.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these lines if you don't want the toolbar to
	// be dockable
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarFile.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndToolBarFile);
	m_wndToolBarWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarWindow);
	m_wndToolBarCustomize.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarCustomize.DockControlBarLeftOf(&m_wndToolBarFile);

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbars with corresponding items in menu
	Organizer.AutoSetMenuImage();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnDropDownFileOpen(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	// this function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBarFile.GetItemRect(m_wndToolBarFile.CommandToIndex(pNMToolBar->iItem), &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());
	if(pNMToolBar->iItem == ID_FILE_OPEN)
	{
		CMenu menu;
		CMenu* pPopup;

		// the font popup is stored in a resource
		menu.LoadMenu(IDR_MAINFRAME);
		pPopup = menu.GetSubMenu(0);
		pPopup->RemoveMenu(ID_FILE_NEW,MF_BYCOMMAND);
		pPopup->RemoveMenu(ID_APP_EXIT,MF_BYCOMMAND);
		pPopup->RemoveMenu(pPopup->GetMenuItemCount()-1,MF_BYPOSITION);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, 
			rect.top + 1, AfxGetMainWnd());
	}
	*pResult = TBDDRET_DEFAULT; 
}

void CMainFrame::OnViewToolbars(UINT nID) 
{
	// TODO: Add your command handler code here
	
	CControlBar* pBar = GetControlBar(nID);
	if (pBar != NULL)
	{
		ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE) == 0, FALSE);
	}
}

void CMainFrame::OnUpdateViewToolbars(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar* pBar=GetControlBar(pCmdUI->m_nID);
	if(pBar!=NULL)
	{
		pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
		return;
	}
}


void CMainFrame::OnDropDownCustomizeToolbar(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	CFrameWnd* pFrame=GetActiveFrame();
	ASSERT(pFrame);
	CPopupBarDoc* pDoc = (CPopupBarDoc*)pFrame->GetActiveDocument();
	ASSERT(pDoc);
	ASSERT_VALID(pDoc);

	// this function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	COXCoolToolBar* pToolBar=GetCustomizeToolBar();

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	pToolBar->GetItemRect(pToolBar->CommandToIndex(pNMToolBar->iItem), &rect);
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.BottomRight());

	COLORREF clr;
	COXColorPickerCtrl colorPicker;
	switch(pNMToolBar->iItem)
	{
	case ID_CUSTOMIZE_TEXT_COLOR:
		{
			if(::IsWindow(colorPicker.m_hWnd) || colorPicker.Create(pToolBar))
			{
				clr=pDoc->GetTextColor();
				colorPicker.SetSelectedColor(clr);
				colorPicker.SetDefaultColor(pDoc->GetDefaultTextColor());
				if(colorPicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					clr=colorPicker.GetSelectedColor();
					pDoc->SetTextColor(clr);
				}
			}
			break;
		}
	case ID_CUSTOMIZE_FILL_COLOR:
		{
			if(::IsWindow(colorPicker.m_hWnd) || colorPicker.Create(pToolBar))
			{
				clr=pDoc->GetFillColor();
				colorPicker.SetSelectedColor(clr);
				colorPicker.SetDefaultColor(pDoc->GetDefaultFillColor());
				if(colorPicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					clr=colorPicker.GetSelectedColor();
					pDoc->SetFillColor(clr);
				}
			}
			break;
		}
	case ID_CUSTOMIZE_BORDER_COLOR:
		{
			if(::IsWindow(colorPicker.m_hWnd) || colorPicker.Create(pToolBar))
			{
				clr=pDoc->GetBorderColor();
				colorPicker.SetSelectedColor(clr);
				colorPicker.SetDefaultColor(pDoc->GetDefaultBorderColor());
				if(colorPicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					clr=colorPicker.GetSelectedColor();
					pDoc->SetBorderColor(clr);
				}
			}
			break;
		}
	case ID_CUSTOMIZE_BORDER_STYLE:
		{
			CBorderPickerCtrl borderPicker;
			if(::IsWindow(borderPicker.m_hWnd) || borderPicker.Create(pToolBar))
			{
				int nBorderStyle=pDoc->GetBorderStyle();
				borderPicker.SetSelectedStyle(nBorderStyle);
				borderPicker.SetStylesImages(IDB_BORDER_TYPES,16,
					BORDERPICK_DEFINEDSTYLES,RGB(192,192,192));
				if(borderPicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					nBorderStyle=borderPicker.GetSelectedStyle();
					pDoc->SetBorderStyle(nBorderStyle);
				}
			}
			break;
		}
	case ID_CUSTOMIZE_LINE_STYLE:
		{
			CLineStylePickerCtrl lineStylePicker;
			if(::IsWindow(lineStylePicker.m_hWnd) || lineStylePicker.Create(pToolBar))
			{
				int nLineStyle=pDoc->GetLineStyle();
				lineStylePicker.SetSelectedStyle(nLineStyle);
				if(lineStylePicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					nLineStyle=lineStylePicker.GetSelectedStyle();
					pDoc->SetLineStyle(nLineStyle);
				}
			}
			break;
		}
	case ID_CUSTOMIZE_DASH_STYLE:
		{
			CDashStylePickerCtrl dashStylePicker;
			if(::IsWindow(dashStylePicker.m_hWnd) || dashStylePicker.Create(pToolBar))
			{
				int nDashStyle=pDoc->GetDashStyle();
				dashStylePicker.SetSelectedStyle(nDashStyle);
				if(dashStylePicker.Pick(ID_POPUPBAR_ALIGNBOTTOM,&rect))
				{
					nDashStyle=dashStylePicker.GetSelectedStyle();
					pDoc->SetDashStyle(nDashStyle);
				}
			}
			break;
		}
	}


	pToolBar->InvalidateRect(rect);

	pDoc->UpdateAllViews(NULL);

	*pResult = TBDDRET_DEFAULT; 
}

#if _MFC_VER>=0x0420
//////////////////////
// custom draw of a toolbar is available since MFC 4.2
afx_msg void CMainFrame::OnCustomDraw(NMHDR* pNotify, LRESULT* pResult)
{
	*pResult=0;

	COXCoolToolBar* pToolBar=GetCustomizeToolBar();

	LPOXCTB_CUSTOMDRAW phdr=(LPOXCTB_CUSTOMDRAW)pNotify;
	// in new version of comctl32.dll(4.71)
	// we use toolbar specific custom draw structure 
	LPNMTBCUSTOMDRAW pTBCDRW;
	LPNMCUSTOMDRAW pCDRW;

	DWORD dwComCtlVersion=pToolBar->GetComCtlVersion();

	if(dwComCtlVersion>=_IE40_COMCTL_VERSION)
	{
		pTBCDRW=(LPNMTBCUSTOMDRAW)phdr->pCustomDraw;
		pCDRW=&pTBCDRW->nmcd;
	}
	else
	{
		pCDRW=(LPNMCUSTOMDRAW)phdr->pCustomDraw;
	}

	phdr->result = CDRF_DODEFAULT;

	if(pCDRW->dwDrawStage==CDDS_ITEMPOSTPAINT)
	{
		CPopupBarDoc* pDoc = NULL;
		CFrameWnd* pFrame=GetActiveFrame();
		if(pFrame)
		{
			pDoc = (CPopupBarDoc*)pFrame->GetActiveDocument();
			if(pDoc)
			{
				ASSERT_VALID(pDoc);
			}
		}

		COLORREF clr;
		switch(pCDRW->dwItemSpec)
		{
		case ID_CUSTOMIZE_TEXT_COLOR:
			{
				clr=pDoc!=NULL ? pDoc->GetTextColor() : ::GetSysColor(COLOR_BTNSHADOW);
				break;
			}
		case ID_CUSTOMIZE_FILL_COLOR:
			{
				clr=pDoc!=NULL ? pDoc->GetFillColor() : ::GetSysColor(COLOR_BTNSHADOW);
				break;
			}
		case ID_CUSTOMIZE_BORDER_COLOR:
			{
				clr=pDoc!=NULL ? pDoc->GetBorderColor() : ::GetSysColor(COLOR_BTNSHADOW);
				break;
			}
		default:
			return;
		}

		if(pCDRW->uItemState&CDIS_DISABLED || pCDRW->uItemState&CDIS_GRAYED)
		{
			clr=::GetSysColor(COLOR_BTNSHADOW);
		}

		int nIndex=pToolBar->CommandToIndex(pCDRW->dwItemSpec);

		CRect rect;
		pToolBar->GetItemRect(nIndex,rect);
		rect.DeflateRect(2,2);
		rect.top=rect.bottom-5;
		rect.right-=pToolBar->GetDropDownArrowWidth()+1;

		if(pCDRW->uItemState&CDIS_SELECTED || pCDRW->uItemState&CDIS_CHECKED)
		{
			rect.OffsetRect(1,1);
		}

		CDC dc;
		dc.Attach(pCDRW->hdc);
		COLORREF clrShadow=::GetSysColor(COLOR_BTNSHADOW);
		CBrush brushFrame(clrShadow);
		dc.FrameRect(&rect,&brushFrame);
		rect.DeflateRect(1,1);

		if(clr!=ID_CLRPICK_COLOR_NONE)
		{
			CBrush brush(clr);
			dc.FillRect(&rect,&brush);
		}
		dc.Detach();

		phdr->bDoDefault=FALSE;
	}
}
//////////////////////
#endif


void CMainFrame::OnUpdateCustomizeButtons(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPopupBarDoc* pDoc = NULL;
	CFrameWnd* pFrame=GetActiveFrame();
	if(pFrame)
	{
		pDoc = (CPopupBarDoc*)pFrame->GetActiveDocument();
		if(pDoc)
		{
			ASSERT_VALID(pDoc);
		}
	}

	pCmdUI->Enable(pDoc!=NULL);

	if(pCmdUI->m_nID==ID_CUSTOMIZE_BORDER_STYLE)
	{
		int nBorderStyle=pDoc==NULL ? CPopupBarDoc::GetDefaultBorderStyle() :
			pDoc->GetBorderStyle();
		int nIndex=CBorderPickerCtrl::FindImageIndexFromStyle(nBorderStyle);
		if(nIndex!=-1)
		{
			int nImageIndex=nIndex+m_nFirstBorderStyleImage;
			TBBUTTON button;
			int nButtonIndex=m_wndToolBarCustomize.CommandToIndex(pCmdUI->m_nID);
			VERIFY(m_wndToolBarCustomize.GetToolBarCtrl().GetButton(nButtonIndex,&button));
			if(button.iBitmap!=nImageIndex)
			{
				m_wndToolBarCustomize.GetToolBarCtrl().DeleteButton(nButtonIndex);
				button.iBitmap=nImageIndex;
				VERIFY(m_wndToolBarCustomize.GetToolBarCtrl().
					InsertButton(nButtonIndex,&button));
			}
		}
	}

	return;
}


void CMainFrame::OnWindowModal() 
{
	// TODO: Add your command handler code here
	m_bModal=!m_bModal;
	((CChildFrame*)GetActiveFrame())->SetModal(m_bModal);
}

void CMainFrame::OnUpdateWindowModal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bModal);
}
