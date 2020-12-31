// OXColorBar.cpp : implementation file
//

#include "stdafx.h"
#include "SpinEx.h"
#include "ColorBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorBar

CColorBar::CColorBar()
	{
	m_nRed = m_nGreen = m_nBlue = 0;
	m_pSpecialPalette = NULL;
	}

CColorBar::~CColorBar()
	{
	if ( m_pSpecialPalette )
		delete m_pSpecialPalette;
	}


BEGIN_MESSAGE_MAP(CColorBar, CStatic)
	//{{AFX_MSG_MAP(CColorBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBar message handlers

void CColorBar::SetBarColor(int nRed, int nGreen, int nBlue)
	{
	m_nRed = nRed;
	m_nGreen = nGreen;
	m_nBlue = nBlue;
	RedrawWindow();
	}

void CColorBar::OnPaint()
	{
	//CPalette*	pOldPalette = NULL;
	CPaintDC	dc(this);						// device context for painting
	//if ( dc.GetDeviceCaps(SIZEPALETTE) == 256 )	// get number of entries in the system palette
	//	pOldPalette = SetSpecialPalette(&dc);	// special palette for 256-color display

	COLORREF	bkCol = RGB(m_nRed, m_nGreen, m_nBlue);	// paint color
	CBrush		colBrush(bkCol);						// paint brush

	dc.FillRect(&(dc.m_ps.rcPaint), &colBrush);														
														
	//if ( pOldPalette )
	//	dc.SelectPalette(pOldPalette, FALSE);
	}

CPalette* CColorBar::SetSpecialPalette(CPaintDC* pdc)
// Set special palette in case of computer with 256 colors.
	{
	WORD			m_wEntriesNum = 1;
	CPalette*		pOldPalette = NULL;
	LPLOGPALETTE	pLogPal = (LPLOGPALETTE) new BYTE[2 * sizeof(WORD) + m_wEntriesNum * sizeof(PALETTEENTRY)];

	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_wEntriesNum;
	for ( int nCount = 0; nCount < m_wEntriesNum; nCount++ )
		{
		pLogPal->palPalEntry[nCount].peRed = (BYTE)m_nRed;
		pLogPal->palPalEntry[nCount].peGreen = (BYTE)m_nGreen;
		pLogPal->palPalEntry[nCount].peBlue = (BYTE)m_nBlue;
		pLogPal->palPalEntry[nCount].peFlags = 0;
		}

	if ( m_pSpecialPalette )
		delete m_pSpecialPalette;

	m_pSpecialPalette = new CPalette;
	if ( m_pSpecialPalette->CreatePalette(pLogPal) )
		{
		pOldPalette = pdc->SelectPalette(m_pSpecialPalette, FALSE);
		if ( pOldPalette )
			{
			UINT nMapEntries = pdc->RealizePalette();
			if ( nMapEntries != m_wEntriesNum )
				{
				TRACE1("CColorBar::SetSpecialPalette() : No mapped palette entries (must be %i)\n", m_wEntriesNum);
				ASSERT(FALSE);
				}
			}
		}
	delete[] pLogPal;

	return pOldPalette;
	}
