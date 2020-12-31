// RissSplash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "resource.h"

#include "MySplashThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CSplashThreadDemo, CSplashThread)
	//{{AFX_MSG_MAP(CSplashThreadDemo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSplashThreadDemo::CSplashThreadDemo()
{
	SetBitmapId(IDB_START);
	SetTimerDuration(0);		// invinite
	SetTimerInternal(10);		// repaint just again
	m_postTimerWaits = 2500;	// ms
	m_StartOfStaticText = 0;
}

CSplashThreadDemo::~CSplashThreadDemo()
{
}

int CSplashThreadDemo::InitInstance()
{
	m_posHeaderMin_X	= m_ptHeaderMain.x;
	m_ptHeaderMain.x	= 100000;	// no Header-drawings in first update

	m_bmp1.LoadBitmap(IDB_BITMAPDISCONNECTED);
	m_bmp2.LoadBitmap(IDB_BITMAPCONNECTED);
	BITMAP	bm1,
			bm2;
	m_bmp1.GetBitmap(&bm1);
	m_bmp2.GetBitmap(&bm2);

	m_BmpSize.cx = max(bm1.bmWidth,  bm2.bmWidth);
	m_BmpSize.cy = max(bm1.bmHeight, bm2.bmHeight);
	
	m_BmpStart.x = m_ptHeaderSub.x;
	m_BmpStart.y = m_ptHeaderSub.y + m_szDeltaHeaderSub.cy;

	CSplashThread::InitInstance();

	m_ptHeaderMain.x	= m_SizeBitmapX;
	SetHeaderSize();
	
	return TRUE;
}

void CSplashThreadDemo::OnTimerInternal()
{
	int		startOfText;
	int		delta	= 1;
	CRect	rectAll;
	BOOL	bRepaint = TRUE;

	startOfText = m_ptHeaderMain.x;

	m_ptHeaderMain.x -= delta;
	if( m_ptHeaderMain.x <= m_posHeaderMin_X )
	{
		bRepaint = FALSE;
		m_ptHeaderMain.x = m_posHeaderMin_X;

		// starting to count when first time here!
		if( m_StartOfStaticText == 0)
		{
			m_StartOfStaticText = GetTickCount();

			CRect	rectBitmap;
			rectBitmap.left   = m_BmpStart.x;
			rectBitmap.right  = rectBitmap.left + m_BmpSize.cx;
			rectBitmap.top    = m_BmpStart.y;
			rectBitmap.bottom = rectBitmap.top + m_BmpSize.cy;
			
			// Bitmap invalidate 
			InvalidateRect(&rectBitmap);
		}
		
		// time to delete ?
		if( (GetTickCount()-m_StartOfStaticText) >= m_postTimerWaits ) 
			HideSplashScreen();
	}
	
	if( bRepaint )
	{
		rectAll.left	= startOfText - delta;
		rectAll.right	= startOfText + delta + m_sizeHeader.cx + 2;
		rectAll.bottom	= m_ptHeaderMain.y;
		rectAll.top		= rectAll.bottom - m_sizeHeader.cy;
		
		InvalidateRect(&rectAll);
	}
}

void CSplashThreadDemo::SetHeaderSize(void)
{
	CPaintDC	dc(&m_wndSplash);
	CFont		*pOldFont,
				font;
	CSize		sizeText;
	POSITION	pos;
	double		iUmrechnung		= -dc.GetDeviceCaps(LOGPIXELSY)/72,
				dHeaderMain		= 0.5 + iUmrechnung * m_nHeightHeaderMain;
	CString		str;

	font.CreateFont((int)dHeaderMain, 0,0,0, m_nWeightHeaderMain, m_bItalicHeaderMain, 0,0,0, m_nOutPreHeaderMain, 0, PROOF_QUALITY,0, m_FacenameHeaderMain);
	pos = m_ListTextHeaderMain.GetHeadPosition();
	str = m_ListTextHeaderMain.GetNext(pos);
	pOldFont		= dc.SelectObject(&font);
	m_sizeHeader	= dc.GetTextExtent(str);
	dc.SelectObject(pOldFont);
	font.DeleteObject();
}

void CSplashThreadDemo::DrawPost(CDC *pDC)
{
	CBitmap	*pBmp;

	if( m_StartOfStaticText == 0)
			pBmp = &m_bmp1;
	else	pBmp = &m_bmp2;
	
	DrawTransparentBitmap(pDC, pBmp, (short)m_BmpStart.x, (short)m_BmpStart.y, RGB(255, 255, 255));
}
