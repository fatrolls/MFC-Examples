////////////////////////////////////////////////////////////////
// 1999 Microsoft Systems Journal
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
//  05/09/02  Lynn McGuire  updated with new code from Paul for arrow controls
//                             http://msdn.microsoft.com/msdnmag/issues/02/10/CQA/
//  09/22/03  Lynn McGuire  converted the selected tab font to the same as the 
//                            tab list (made bold also)
//  09/25/03  Lynn McGuire  added user editing to the sheet name tabs
//  09/29/03  Lynn McGuire  added a right mouse click popup menu
//  09/30/03  Lynn McGuire  added first and last arrow controls


#include "stdafx.h"
#include "ftab.h"


// #include "resource.h"
#define ID_EDIT_SHEETS                  34069
#define ID_EDIT_ADDSHEET                34071
#define ID_EDIT_DELETESHEET             34072
#define ID_EDIT_RENAMESHEET             34073

#define  EditBoxId  5555


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////
// Private class to represent one folder tab
//
class CFolderTab {
private:
	CString	m_sText; // tab text
	CRect		m_rect;			// bounding rect
	CRgn		m_rgn;			// polygon region to fill (trapezoid)

	int		ComputeRgn(CDC& dc, int x);
	int		Draw(CDC& dc, CFont& font, BOOL bSelected);
	BOOL		HitTest(CPoint pt)			{ return m_rgn.PtInRegion(pt); }
	CRect		GetRect() const				{ return m_rect; }
	void		GetTrapezoid(const CRect& rc, CPoint* pts) const;

	friend class CFolderTabCtrl;

public:
	CFolderTab(LPCTSTR lpszText) : m_sText(lpszText) { }
	LPCTSTR	GetText() const				{ return m_sText; }
	void  	SetText(LPCTSTR lpszText)	{ m_sText = lpszText; }
};


const CXOFFSET = 8;		// defined pitch of trapezoid slant
const CXMARGIN = 2;		// left/right text margin
const CYMARGIN = 1;		// top/bottom text margin
const CYBORDER = 1;		// top border thickness
const CXBUTTON = GetSystemMetrics(SM_CXVSCROLL);


//////////////////
// Compute the the points, rect and region for a tab.
// Input x is starting x pos.
//
int CFolderTab::ComputeRgn(CDC& dc, int x)
{
	m_rgn.DeleteObject();

	CRect& rc = m_rect;
	rc.SetRectEmpty();

	// calculate desired text rectangle
	dc.DrawText(m_sText, &rc, DT_CALCRECT);
	rc.right += 2 * CXOFFSET + 3 * CXMARGIN;	  // add margins
	rc.bottom = rc.top + GetSystemMetrics(SM_CYHSCROLL);	// ht = scrollbar height
	rc += CPoint(x,0);							// shift right

	// create trapezoid region
	CPoint pts[4];
	GetTrapezoid(rc, pts);
	m_rgn.CreatePolygonRgn(pts, 4, WINDING);

	return rc.Width();
}

//////////////////
// Given the boundint rect, compute trapezoid region.
// Note that the right and bottom edges not included in rect or
// trapezoid; these are normal rules of geometry. 
//
void CFolderTab::GetTrapezoid(const CRect& rc, CPoint* pts) const
{
	pts[0] = rc.TopLeft();
	pts[1] = CPoint(rc.left + CXOFFSET,   rc.bottom);
	pts[2] = CPoint(rc.right- CXOFFSET-1, rc.bottom);
	pts[3] = CPoint(rc.right-1, rc.top);
}


//////////////////
// Draw tab in normal or highlighted state
//
int CFolderTab::Draw(CDC& dc, CFont& font, BOOL bSelected)
{
	COLORREF bgColor = GetSysColor(bSelected ? COLOR_WINDOW     : COLOR_3DFACE);
	COLORREF fgColor = GetSysColor(bSelected ? COLOR_WINDOWTEXT : COLOR_BTNTEXT);

	CBrush brush(bgColor);					 // background brush
	dc.SetBkColor(bgColor);					 // text background
	dc.SetTextColor(fgColor);				 // text color = fg color

	CPen blackPen(PS_SOLID, 1, RGB(0,0,0));	// black
	CPen shadowPen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

	// Fill trapezoid
	CPoint pts[4];
	CRect rc = m_rect;
	GetTrapezoid(rc, pts);
	CPen* pOldPen = dc.SelectObject(&blackPen);
	dc.FillRgn(&m_rgn, &brush);

	// Draw edges. This is requires two corrections:
	// 1) Trapezoid dimensions don't include the right and bottom edges,
	// so must use one pixel less on bottom (cybottom)
	// 2) the endpoint of LineTo is not included when drawing the line, so
	// must add one pixel (cytop)
	//
	pts[1].y--;			// correction #1: true bottom edge y-coord
	pts[2].y--;			// ...ditto
	pts[3].y--;			// correction #2:	extend final LineTo
	dc.MoveTo(pts[0]);						// upper left
	dc.LineTo(pts[1]);						// bottom left
	dc.SelectObject(&shadowPen);			// bottom line is shadow color
	dc.MoveTo(pts[1]);						// line is inside trapezoid bottom
	dc.LineTo(pts[2]);						// ...
	dc.SelectObject(&blackPen);			// upstroke is black
	dc.LineTo(pts[3]);						// y-1 to include endpoint
	if (!bSelected) 
	{
		// if not highlighted, upstroke has a 3D shadow, one pixel inside
		pts[2].x--;		// offset left one pixel
		pts[3].x--;		// ...ditto
		dc.SelectObject(&shadowPen);
		dc.MoveTo(pts[2]);
		dc.LineTo(pts[3]);
	}
	dc.SelectObject(pOldPen);

	// draw text
	rc.DeflateRect(CXOFFSET + CXMARGIN, CYMARGIN);
	CFont* pOldFont = dc.SelectObject(&font);
	dc.DrawText(m_sText, &rc, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	dc.SelectObject(pOldFont);

	return m_rect.right;
}


//////////////////////////////////////////////////////////////////
// CFolderTabCtrl

IMPLEMENT_DYNAMIC(CFolderTabCtrl, CWnd)
BEGIN_MESSAGE_MAP(CFolderTabCtrl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(FTBFIRST,OnFirstTab)
	ON_BN_CLICKED(FTBPREV,OnPrevTab)
	ON_BN_CLICKED(FTBNEXT,OnNextTab)
	ON_BN_CLICKED(FTBLAST,OnLastTab)
	ON_EN_KILLFOCUS(EditBoxId,OnEditBoxKillFocus)
	ON_COMMAND(ID_EDIT_SHEETS,OnEditProperties)
	ON_COMMAND(ID_EDIT_ADDSHEET,OnEditAddSheet)
	ON_COMMAND(ID_EDIT_DELETESHEET,OnEditDeleteSheet)
	ON_COMMAND(ID_EDIT_RENAMESHEET,OnEditRenameSheet)
END_MESSAGE_MAP()


CFolderTabCtrl::CFolderTabCtrl()
{
	m_iCurItem =
	m_dwFtabStyle =
	m_cxDesired =
	m_cxButtons =
	m_iFirstTab = 0;
	m_editBox = NULL;
}


CFolderTabCtrl::~CFolderTabCtrl()
{
	while (!m_lsTabs.IsEmpty())
		delete (CFolderTab*)m_lsTabs.RemoveHead();

	if (m_editBox) 
		delete m_editBox;
}


//////////////////
// Create folder tab control from static control.
// Destroys the static control. This is convenient for dialogs
//
BOOL CFolderTabCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;
	if (!wndStatic.SubclassDlgItem(nID, pParent))
		return FALSE;
	CRect rc;
	wndStatic.GetWindowRect(&rc);
	pParent->ScreenToClient(&rc);
	wndStatic.DestroyWindow();
	rc.bottom = rc.top + GetDesiredHeight();
	return Create(WS_CHILD|WS_VISIBLE, rc, pParent, nID);
}


//////////////////
// Create folder tab control.
//
BOOL CFolderTabCtrl::Create(DWORD dwStyle, const RECT& rc,
	CWnd* pParent, UINT nID, DWORD dwFtabStyle)
{
	ASSERT(pParent);
	ASSERT(dwStyle & WS_CHILD);

	m_dwFtabStyle = dwFtabStyle;

	static LPCTSTR lpClassName = _T("PDFolderTab");
	static BOOL bRegistered = FALSE; // registered?
	if (!bRegistered) 
	{
		WNDCLASS wc;
		memset(&wc, 0, sizeof(wc));
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS | CS_DBLCLKS;
		wc.lpfnWndProc = (WNDPROC)::DefWindowProc; // will get hooked by MFC
		wc.hInstance = AfxGetInstanceHandle();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
		wc.lpszMenuName = NULL;
		wc.lpszClassName = lpClassName;
		if (!AfxRegisterClass(&wc)) 
		{
			TRACE("*** CFolderTabCtrl::AfxRegisterClass failed!\n");
			return FALSE;
		}
		bRegistered = TRUE;
	}
	if (!CWnd::CreateEx(0, lpClassName, NULL, dwStyle, rc, pParent, nID))
		return FALSE;

	// initialize fonts
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = GetSystemMetrics(SM_CYHSCROLL)-CYMARGIN;
	lf.lfWeight = FW_NORMAL;
	lf.lfCharSet = DEFAULT_CHARSET;
	_tcscpy(lf.lfFaceName, _T("Arial"));
	m_fontNormal.CreateFontIndirect(&lf);
	//      Lynn McGuire  9/19/03  dont make the selected font smaller
	//  lf.lfHeight -= 2;
	//      Lynn McGuire  9/19/03  make the selected font bold like Excel
	lf.lfWeight = FW_BOLD;
	m_fontSelected.CreateFontIndirect(&lf);

	return TRUE;
}


LPCTSTR CFolderTabCtrl::GetItemText(int iItem)
{
	CFolderTab* pft = GetTab(iItem);
	return pft ? pft->GetText() : NULL;
}


void CFolderTabCtrl::SetItemText(int iItem, LPCTSTR lpText)
{
	CFolderTab* pft = GetTab(iItem);
	if (pft) {
		pft->SetText(lpText);
	}
}


//////////////////
// copy a font
//
static void CopyFont(CFont& dst, CFont& src)
{
	dst.DeleteObject();
	LOGFONT lf;
	VERIFY(src.GetLogFont(&lf));
	dst.CreateFontIndirect(&lf);
}


//////////////////
// Set normal, selected fonts
//
void CFolderTabCtrl::SetFonts(CFont& fontNormal, CFont& fontSelected)
{
	CopyFont(m_fontNormal, fontNormal);
	CopyFont(m_fontSelected, fontSelected);
}


//////////////////
// Paint function
//
void CFolderTabCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CFolderTab* firstTab = GetTab(m_iFirstTab);
	int xOrigin = m_cxButtons;
	if (firstTab) 
		xOrigin -= firstTab->GetRect().left;
	dc.SetViewportOrg(xOrigin,0);

	CRect rc;
	GetClientRect(&rc);

	CFolderTab* pCurTab = NULL;

	// draw all the normal (non-selected) tabs
	int n = GetItemCount();
	for (int i=0; i<n; i++) 
	{
		CFolderTab* pTab = GetTab(i);
		ASSERT(pTab);
		if (i==m_iCurItem) {
			pCurTab = pTab;
		} else {
			pTab->Draw(dc, m_fontNormal, FALSE);
		}
	}
	// draw selected tab last so it will be "on top" of the others
	if (pCurTab)
		pCurTab->Draw(dc, m_fontSelected, TRUE);

	// draw border: line along the top edge, excluding selected tab
	CRect rcCurTab(0,0,0,0);
	if (pCurTab)
		rcCurTab = pCurTab->GetRect();

	rc.right -= xOrigin;
	CPen blackPen(PS_SOLID, 1, RGB(0,0,0));	// black
	CPen* pOldPen = dc.SelectObject(&blackPen);
	dc.MoveTo(rcCurTab.right, rcCurTab.top);
	dc.LineTo(rc.right, rc.top);
	if (m_dwFtabStyle & FTS_FULLBORDER) 
	{
		dc.MoveTo(rc.right-1, rc.top);
		dc.LineTo(rc.right-1, rc.bottom-1);
		dc.LineTo(rc.left,  rc.bottom-1);
		dc.LineTo(rc.left,  rc.top);
	} else {
		dc.MoveTo(rc.left, rc.top);
	}
	dc.LineTo(rcCurTab.TopLeft());
	dc.SelectObject(pOldPen);
}


//////////////////
// Handle mouse click: select new tab, if any. Notify parent, of course
//
void CFolderTabCtrl::OnLButtonDown(UINT nFlags, CPoint pt)
{
	int iTab = HitTest(pt);
	if (iTab>=0 && iTab!=m_iCurItem) 
	{
		SelectItem(iTab);
		NMFOLDERTAB nm;
		nm.hwndFrom = m_hWnd;
		nm.idFrom = GetDlgCtrlID();
		nm.code = FTN_TABCHANGED;
		nm.iItem = iTab;
		CWnd* pParent = GetParent();
		pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
	}
}


WNDPROC DefEditBoxProc = NULL; 

int UserPressedEnterOnTheEditBox = false;

HWND EditBoxHandle = 0;


LRESULT CALLBACK MyEditBoxProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message) 
	{
         case WM_CHAR:
              if ( VK_RETURN == wParam ) 
			  {
                  // User pressed ENTER -- do what you want here
				  UserPressedEnterOnTheEditBox = true;
				  // HWND editBoxHandle = GetDlgItem (hDlg, EditBoxId);
				  SendMessage (EditBoxHandle, WM_CLOSE, 0, 0);
                  return 0;
              }
              else if ( VK_ESCAPE == wParam ) 
			  {
                  // User pressed ESCAPE -- do what you want here
				  UserPressedEnterOnTheEditBox = false;
				  // HWND editBoxHandle = GetDlgItem (hDlg, EditBoxId);
				  SendMessage (EditBoxHandle, WM_CLOSE, 0, 0);
                  return 0;
              }
              else 
				  return (LRESULT) CallWindowProc 
							(DefEditBoxProc, hDlg, message, wParam, lParam);
         break;
         default:
              return (LRESULT) CallWindowProc 
						(DefEditBoxProc, hDlg, message, wParam, lParam);
         break;
    }
    return(0);
}


//////////////////
// Handle mouse click: select new tab, if any. Notify parent, of course
//
void CFolderTabCtrl::OnLButtonDblClk(UINT nFlags, CPoint pt)
{
	int iTab = HitTest(pt);
	if (iTab >= 0) 
	{
		SelectItem (iTab);
		OnEditRenameSheet ();
	}
}


void CFolderTabCtrl::OnEditBoxKillFocus()
{
	//MessageBox ("CFolderTabCtrl::OnEditBoxKillFocus - got here !");
	if (m_editBox)
	{
		if (UserPressedEnterOnTheEditBox)
		{
			char buffer [4096];
			m_editBox -> GetWindowText (buffer, sizeof (buffer) - 1);
			CFolderTab * pTab = GetTab (m_iCurItem);
			pTab -> SetText (buffer);
			Invalidate ();
			RecomputeLayout ();
			NMFOLDERTAB nm;
			nm.hwndFrom = m_hWnd;
			nm.idFrom = GetDlgCtrlID ();
			nm.code = FTN_TABNAMECHANGED;
			nm.iItem = m_iCurItem;
			nm.lpText = buffer;
			CWnd* pParent = GetParent ();
			pParent -> Invalidate ();
			pParent -> SendMessage (WM_NOTIFY, nm.idFrom, (LPARAM) & nm);
		}
		delete m_editBox;
		m_editBox = NULL;
		DefEditBoxProc = NULL;
		UserPressedEnterOnTheEditBox = false;
	}
}


//////////////////
// Handle right mouse click: Notify parent, of course
//
void CFolderTabCtrl::OnRButtonDown(UINT nFlags, CPoint pt)
{
	int iTab = HitTest(pt);
	if (iTab >= 0) 
	{
		SelectItem (iTab);
	}

		// Create the pop-up menu items.
	HMENU hmenu = CreatePopupMenu ();
	AppendMenu (hmenu, MF_ENABLED | MF_STRING, ID_EDIT_ADDSHEET, "Add");
	AppendMenu (hmenu, MF_ENABLED | MF_STRING, ID_EDIT_DELETESHEET, "Delete");
	AppendMenu (hmenu, MF_ENABLED | MF_STRING, ID_EDIT_RENAMESHEET, "Rename");
	AppendMenu (hmenu, MF_SEPARATOR, NULL, "");
	AppendMenu (hmenu, MF_ENABLED | MF_STRING, ID_EDIT_SHEETS, "Properties...");
		
		// display menu next to the selected tab
	ClientToScreen ( & pt);
	TrackPopupMenuEx (hmenu, TPM_RIGHTBUTTON, pt.x, pt.y, m_hWnd, NULL);
	
		// cleanup   
	DestroyMenu (hmenu);
}


//////////////////
// Find which tab is under mouse, -1 if none
//
int CFolderTabCtrl::HitTest(CPoint pt)
{
	CRect rc;
	GetClientRect(&rc);
	rc.left += m_cxButtons;
	if (rc.PtInRect(pt)) 
	{
		int xOrigin = m_cxButtons - GetTab(m_iFirstTab)->GetRect().left;
		pt.x -= xOrigin;
		int n = GetItemCount();
		for (int i=0; i<n; i++) 
		{
			if (GetTab(i)->HitTest(pt))
				return i;
		}
	}
	return -1;
}


//////////////////
// Select ith tab. Returns index selected
//
int CFolderTabCtrl::SelectItem(int iTab)
{
	int count = GetItemCount();
	if (iTab<0 || iTab>=count)
		return -1;		// bad
	if (iTab == m_iCurItem)
		return iTab;	// already selected

	if (m_iCurItem < count)
		InvalidateTab(m_iCurItem);		// invalidate old tab (repaint)

	m_iCurItem = iTab;				// set new selected tab
	InvalidateTab(m_iCurItem);		// repaint new tab
	
	return m_iCurItem;
}


//////////////////
/// Invalidate a tab: invaldate its rect
//
void CFolderTabCtrl::InvalidateTab(int iTab, BOOL bErase)
{
	CRect rc = GetTab(iTab)->GetRect();
	CFolderTab * tab = GetTab (m_iFirstTab);
	int xOrigin = 0;
	if (tab)
		xOrigin = m_cxButtons - tab -> GetRect().left;
	else
		xOrigin = m_cxButtons;
	rc += CPoint(xOrigin,0);
	InvalidateRect(rc, bErase);
}


BOOL CFolderTabCtrl::Load(UINT nIDRes)
{
	CString s;
	if (!s.LoadString(nIDRes))
		return FALSE;

	CString sTab;
	for (int i=0; AfxExtractSubString(sTab, s, i); i++) {
		AddItem(sTab);
	}
	return TRUE;
}


int CFolderTabCtrl::AddItem(LPCTSTR lpszText)
{
	m_lsTabs.AddTail(new CFolderTab(lpszText));
	RecomputeLayout();
	return m_lsTabs.GetCount() - 1;
}


BOOL CFolderTabCtrl::RemoveItem(int iPos)
{
	POSITION pos = m_lsTabs.FindIndex(iPos);
	if (pos) 
	{
		CFolderTab* pTab = (CFolderTab*)m_lsTabs.GetAt(pos);
		m_lsTabs.RemoveAt(pos);
		delete pTab;
	}
	RecomputeLayout();
	return pos!=NULL;
}


CFolderTab* CFolderTabCtrl::GetTab(int iPos)
{
	POSITION pos = m_lsTabs.FindIndex(iPos);
	return pos ? static_cast<CFolderTab*>(m_lsTabs.GetAt(pos)) : NULL;
}


void CFolderTabCtrl::RecomputeLayout()
{
	CClientDC dc(this);
	int x = 0;
	int n = GetItemCount();
	CFolderTab* pTab = NULL;
	for (int i=0; i<n; i++) 
	{
		pTab = GetTab(i);
		CFont* pOldFont = NULL;
			//  use the bigger of the two fonts for all extents since the 
			//  Selected font is bigger than the Normal font - elsewhise 
			//  some of the displayed selected tab characters are cut
		// if (i == m_iCurItem) 
			pOldFont = dc.SelectObject(&m_fontSelected);
		// else
		//	pOldFont = dc.SelectObject(&m_fontNormal);
		if (pTab) 
			x += pTab->ComputeRgn(dc, x) - CXOFFSET;
		dc.SelectObject(pOldFont);
	}

	m_cxDesired = m_cxButtons;
	if (pTab) 
	{
		CRect rc = pTab->GetRect();
		m_cxDesired += rc.right;
	}
}


int CFolderTabCtrl::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CWnd::OnCreate(lpcs)!=0)
		return -1;

	if (m_dwFtabStyle & FTS_BUTTONS) 
	{
		CRect rc;
		// for (int i=FTBPREV; i<=FTBNEXT; i++) 
		for (int i = FTBFIRST; i <= FTBLAST; i++) 
		{
			VERIFY (m_wndButton[i-1].Create (NULL,
					WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,rc,this,i));
		}
		m_cxButtons = FTS_NUMBUTTONS * CXBUTTON;
	}
	return 0;
}


void CFolderTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	if (m_wndButton[0].m_hWnd) 
	{
		int w = cy;
		CRect rc(0,0,w,cy);
		// for (int i = FTBPREV; i<=FTBNEXT; i++) 
		for (int i = FTBFIRST; i <= FTBLAST; i++) 
		{
			m_wndButton[i-1].MoveWindow(&rc);
			rc += CPoint(w,0);
		}
		UpdateButtons();
	}
}


void CFolderTabCtrl::UpdateButtons()
{
	for (int i = FTBFIRST; i <= FTBLAST; i++) 
	{
		m_wndButton [i - 1].EnableWindow (TRUE);
	}
}


void CFolderTabCtrl::OnFirstTab()
{
	m_iFirstTab = 0;
	Invalidate();
	UpdateButtons();
}


void CFolderTabCtrl::OnNextTab()
{
	if (m_iFirstTab < m_lsTabs.GetCount() - 1) 
	{
		m_iFirstTab++;
		Invalidate();
		UpdateButtons();
	}
}


void CFolderTabCtrl::OnPrevTab()
{
	if (m_iFirstTab > 0) 
	{
		m_iFirstTab--;
		Invalidate();
		UpdateButtons();
	}
}


void CFolderTabCtrl::OnLastTab()
{
	m_iFirstTab = m_lsTabs.GetCount() - 1;
	Invalidate();
	UpdateButtons();
}


void CFolderTabCtrl::OnEditProperties()
{
	NMFOLDERTAB nm;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();
	nm.code = FTN_EDITSHEETS;
	nm.iItem = m_iCurItem;
	CWnd* pParent = GetParent();
	pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
}


void CFolderTabCtrl::OnEditAddSheet()
{
	NMFOLDERTAB nm;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();
	nm.code = FTN_ADDSHEET;
	nm.iItem = m_iCurItem;
	CWnd* pParent = GetParent();
		//  note that the parent will need to call the AddItem method
		//  in order to complete this user event
	pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
}


void CFolderTabCtrl::OnEditDeleteSheet()
{
	NMFOLDERTAB nm;
	nm.hwndFrom = m_hWnd;
	nm.idFrom = GetDlgCtrlID();
	nm.code = FTN_DELETESHEET;
	nm.iItem = m_iCurItem;
	CWnd* pParent = GetParent();
		//  note that the parent will need to call the RemoveItem method
		//  in order to complete this user event
	pParent->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm);
}


void CFolderTabCtrl::OnEditRenameSheet()
{
		//  get the position for the proposed edit box
	CRect rc = GetTab (m_iCurItem) -> GetRect ();
		//  make the edit box smaller than the tab trapezoid
	rc.top++;
	rc.left += m_cxButtons + CXOFFSET + CXMARGIN;
	rc.right += m_cxButtons - CXOFFSET - CXMARGIN;
	rc.bottom--;
		//  now throw up the transparent edit control
	if ( ! m_editBox)
	{
		m_editBox = new CEdit;
		m_editBox -> Create ( WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 
								rc, this, EditBoxId );
		CFolderTab * tab = GetTab (m_iCurItem);
		m_editBox -> SetWindowText ( tab -> GetText () );
		m_editBox -> SetFocus ();
			//  the limit on the length of the tab names is 40 characters minus 1
		m_editBox -> SetLimitText (40 - 1);
		int len = strlen (tab -> GetText ());
			//  move the cursor to the end of the text without selecting anything
		m_editBox -> SetSel (len, len);
		HWND EditWnd = m_editBox -> GetSafeHwnd ();
		DefEditBoxProc = (WNDPROC) GetWindowLong (EditWnd, GWL_WNDPROC);
		SetWindowLong (EditWnd, GWL_WNDPROC, (long) MyEditBoxProc);
		UserPressedEnterOnTheEditBox = false;
		EditBoxHandle = EditWnd;
	}
}


////////////////////////////////////////////////////////////////
// CFolderButton
//
IMPLEMENT_DYNAMIC(CFolderButton, CButton)
BEGIN_MESSAGE_MAP(CFolderButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CFolderButton::DrawItem(LPDRAWITEMSTRUCT lpDis)
{
	DRAWITEMSTRUCT& dis = *lpDis;
	CDC& dc = *CDC::FromHandle(dis.hDC);
	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(&rc,GetSysColor(COLOR_3DFACE));
	BOOL bDown = dis.itemState & ODS_SELECTED;
	if (bDown) {
		rc += CPoint(1,1);
	}

	CPen pen(PS_SOLID,1,
		dis.itemState & ODS_DISABLED ? GetSysColor(COLOR_3DSHADOW) : RGB(0,0,0));
	CPen* pOldPen = dc.SelectObject(&pen);
	dc.MoveTo(rc.TopLeft());
	dc.LineTo(rc.right,rc.top);
	CRect rc2=rc;
	for (int i=0; i<2; i++) 
	{
		dc.Draw3dRect(&rc2,
			GetSysColor(bDown ? COLOR_3DFACE : COLOR_3DHIGHLIGHT),
			GetSysColor(COLOR_3DSHADOW));
		rc2.right--;
		rc2.bottom--;
	}

		//  this number needs to be odd so that will get 1 pixel at the end
		//  Paul had it set to 7 - Excel appears to have 9
	int arrowHeight = 9;  
		//  this number appears to be (arrowHeight / 2 + 1)
		//  Paul had this set to 4 - Excel appears to have 5
	int arrowWidth = 5;
	int cyMargin = (rc.Height() - arrowHeight) / 2;
	int cxMargin = (rc.Width() - arrowWidth) / 2;

		//  draw the arrows (left or right depending on button)
	int x = 0;
	int incr = 0;
	switch (dis.CtlID)
	{
	case FTBFIRST:
		x = rc.right - cxMargin - 1;
		incr = -1;
		break;
	case FTBPREV:
		x = rc.right - cxMargin - 2;
		incr = -1;
		break;
	case FTBNEXT:
		x = rc.left + cxMargin;
		incr = 1;
		break;
	case FTBLAST:
		x = rc.left + cxMargin - 1;
		incr = 1;
		break;
	}
	int y = rc.top + cyMargin;
	int h = arrowHeight;
	for (int j = 0; j < arrowWidth; j++) 
	{
		dc.MoveTo (x, y);
		dc.LineTo (x, y + h);
		h -= 2;
		x += incr;
		y++;
	}
		//  draw the vertical line for the first and last buttons
	if (dis.CtlID == FTBFIRST) 
	{
			//  the vertical line is before the arrow
		x--;
		y = rc.top + cyMargin;
		dc.MoveTo (x, y);
		dc.LineTo (x, y + arrowHeight);
	}
	if (dis.CtlID == FTBLAST) 
	{
			//  the vertical line is after the arrow
		x++;
		y = rc.top + cyMargin;
		dc.MoveTo (x, y);
		dc.LineTo (x, y + arrowHeight);
	}
	dc.SelectObject(pOldPen);
}


void CFolderButton::OnLButtonDown(UINT nFlags, CPoint pt)
{
	Default();
	SetTimer(1,500,NULL);
	m_iState = 0;
}


void CFolderButton::OnLButtonUp(UINT nFlags, CPoint pt)
{
	KillTimer(1);
	Default();
}


void CFolderButton::OnLButtonDblClk(UINT nFlags, CPoint pt)
{
	SendMessage(WM_LBUTTONDOWN,nFlags,MAKELONG(pt.x,pt.y));
}


void CFolderButton::OnTimer(UINT nIDEvent)
{
	if (IsWindowEnabled()) 
	{
		if (m_iState++ == 0) 
		{
			KillTimer(1);
			SetTimer(1,150,NULL);
		}
		GetParent()->SendMessage(WM_COMMAND, GetDlgCtrlID());
	} 
	else 
	{
		KillTimer(1);
	}
}
