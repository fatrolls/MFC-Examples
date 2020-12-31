
#include "StdAfx.h"
#include "advWnd.h"

////////////////////////////////////////////////////////////////////////////////
//
//	Class		: CadvWnd
//  Author		: Andreas Leitner (aleitner@usa.net)
//  Description	: A CWnd derived class that is able to redraw itself flicker free
//
////////////////////////////////////////////////////////////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// MFC class creation macro
IMPLEMENT_DYNCREATE(CadvWnd, CWnd)


// MFC message map system
BEGIN_MESSAGE_MAP(CadvWnd, CWnd)
	//{{AFX_MSG_MAP(CadvWnd)
	ON_WM_PAINT()
	ON_WM_WININICHANGE()
	ON_WM_SIZE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CadvWnd::CadvWnd()
{
	// Init Data
	m_pbmpContents = NULL;
	m_bFlickerFree      = FALSE;
	m_iBackgroundMode = BM_DEF_WND_COL;	
}



CadvWnd::~CadvWnd()
{
	if (m_pbmpContents != NULL) delete m_pbmpContents;
}



#ifdef _DEBUG
void CadvWnd::AssertValid() const
{
	CWnd::AssertValid();
}



void CadvWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif //_DEBUG




BOOL CadvWnd::Create(const RECT& rect, CWnd* parent, UINT nID, CCreateContext* /*pCC*/ , DWORD style, DWORD dwExStyle)
{
	HWND hwnd = ::CreateWindowEx(
						dwExStyle,	
						"ADVANCED_WND",
						0,
						style, 
						rect.left, 
						rect.top,
						rect.right,
						rect.bottom,
						parent->GetSafeHwnd(), 
						(HMENU) nID, 
						AfxGetInstanceHandle(),
						0);

	if (!hwnd)
	{
		ASSERT(0);
		return FALSE;
	}
	else
	{
		SubclassWindow(hwnd);
	}


	if (!CreateChildren()) return FALSE;

	return TRUE;
}

BOOL CadvWnd::SubclassDlgItem(UINT nID, CWnd* parent)
{
	if (!CWnd::SubclassDlgItem(nID, parent)) return FALSE;

	if (!CreateChildren()) return FALSE;
	return TRUE;
}


WNDPROC* CadvWnd::GetSuperWndProcAddr()
{
	static WNDPROC NEAR pfnSuper = NULL;
	return &pfnSuper;
}

LRESULT CALLBACK  CadvWnd::DummyWndProc(HWND h, UINT u, WPARAM w, LPARAM l)
{
	return ::DefWindowProc(h, u, w, l);
}

void CadvWnd::RegisterClass()
{
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));
	
	wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW | CS_GLOBALCLASS;
	wc.lpfnWndProc = DummyWndProc;
	wc.hInstance = AfxGetInstanceHandle();
	wc.hCursor = 0;
	wc.lpszClassName = "ADVANCED_WND";
	wc.hbrBackground = NULL; 
	
	if (!::RegisterClass(&wc))
	{
		ASSERT(FALSE);
	}
}

BOOL CadvWnd::CreateChildren()
{
	return TRUE;
}


void CadvWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!IsFlickerFree())
	{ // Draw fast, but with flicker
		if (dc.m_ps.fErase) InternalRedrawBG(&dc, rcClient);
		InternalRedrawFG(&dc, rcClient);
	}
	else
	{ // draw slow, but without flicker
		
		// Update Bitmap

		// Create a MemDC for the bitmap
		CDC* pMemDC;
		CBitmap* pOldBitmap;
		pMemDC = new CDC;
		pMemDC->CreateCompatibleDC(&dc);
		pOldBitmap = pMemDC->SelectObject(m_pbmpContents);

		if (IsContentsChanged())
		{ // Repaint Bitmap
			// After an Direct 3d app needed. Bug?
			pMemDC->SelectStockObject(BLACK_PEN);

			// Do the painting
			InternalRedrawBG(pMemDC, rcClient);
			InternalRedrawFG(pMemDC, rcClient);

			// Set Contents changed back to false, since we updated the bitmap
			SetContentsChanged(FALSE);
		}
		
		// Copy Bitmap
		dc.BitBlt( rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
		pMemDC->SelectObject(pOldBitmap);
		delete pMemDC;
	}
}

void CadvWnd::InternalRedrawFG(CDC* /*pDC*/, CRect /*rcPaint*/)	// (Parameter description)
{ 
	// Nothing to do
}

void CadvWnd::InternalRedrawBG(CDC* pDC, CRect /*rcPaint*/)
{
	// Paint backgroundcolor
	
	// Select Color
	COLORREF colBG;
	if (GetBackgroundMode() & BM_DEF_WND_COL)
		colBG = GetSysColor(COLOR_WINDOW);
	if (GetBackgroundMode() & BM_CUST_COL)
		colBG = GetBackgroundColor();;

	// Paint background color
	CRect rcClip;
	pDC->GetClipBox(rcClip);

	CBrush brBG;
	brBG.CreateSolidBrush(colBG);
	pDC->FillRect(rcClip, &brBG);
	brBG.DeleteObject();
}

const int CadvWnd::GetBackgroundMode()
{
	return m_iBackgroundMode;
}

void CadvWnd::SetBackgroundMode(COLORREF Color, int Mode /*= BM_CUST_COL*/)
{
	m_colBackground = Color;
	m_iBackgroundMode = Mode;
}
	
COLORREF CadvWnd::GetBackgroundColor()
{
	return m_colBackground;
}

BOOL CadvWnd::IsFlickerFree()
{
	return m_bFlickerFree;
}

void CadvWnd::SetFlickerFree(BOOL bFlickerFree)
{
	BOOL bOld = m_bFlickerFree;
	m_bFlickerFree = bFlickerFree;
	if (bOld && !bFlickerFree)
	{
		ASSERT(m_pbmpContents != NULL);
		delete m_pbmpContents;
		m_pbmpContents = NULL;
	}

	if (!bOld && bFlickerFree)
	{
		ASSERT(m_pbmpContents == NULL);
		m_pbmpContents = new CBitmap;
		ReCreateBitmap();
	}
}


void CadvWnd::OnWinIniChange(LPCTSTR lpszSection) 
{
	CWnd::OnWinIniChange(lpszSection);
	
	if (IsFlickerFree())
	{
		ReCreateBitmap();
		Invalidate();
	}
	
}

void CadvWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (IsFlickerFree())
		ReCreateBitmap();
	
}

void CadvWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CWnd::OnPaletteChanged(pFocusWnd);
	
	if (IsFlickerFree())
		ReCreateBitmap();
	Invalidate();
	
}

void CadvWnd::ReCreateBitmap()
{
	ASSERT( m_pbmpContents != NULL);

	CDC* pMemDC;
	CDC* pDC = GetDC();
	CRect rcClient;

	GetClientRect(&rcClient);

	delete m_pbmpContents;
	m_pbmpContents = new CBitmap;
	pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);
	
	m_pbmpContents->CreateCompatibleBitmap( pDC, rcClient.Width(), rcClient.Height());
	delete pMemDC;
	SetContentsChanged();
}

void CadvWnd::SetContentsChanged(BOOL yes /*= TRUE*/)
{
	m_bUpdateContents = yes;
}

BOOL CadvWnd::IsContentsChanged()
{
	return m_bUpdateContents;
}

////////////////////////////////////////////////////////////////////////////////