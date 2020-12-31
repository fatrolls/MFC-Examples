// SinusFrame.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Sinus.h"
#include "SinusFrame.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSinusFrame

CSinusFrame::CSinusFrame()
{
	m_bInitialized = false;
	m_bRunning		= false;
	m_nTimer			= 0;
	m_nTextPos		= 0;
	m_nSinusPos		= 0;
	m_nPixLeft		= 0;
	m_nSinusOffset = 0;
	m_nSinusSpeed = -3;

	m_pFont			= NULL;
	m_pDCScroll		= NULL;
	m_pDCSinus		= NULL;
	m_pBMScroll		= NULL;
	m_pBMSinus		= NULL;	
	
	const double rad = 2.0*3.141592654/360.0;
	int i; float f;
	for(i=0, f=0.0; i<720; i++, f+=0.5f)
		m_dSinusTable[i] = sin(rad*f);
}

CSinusFrame::~CSinusFrame()
{
	Cleanup();
}


BEGIN_MESSAGE_MAP(CSinusFrame, CStatic)
	//{{AFX_MSG_MAP(CSinusFrame)
	ON_WM_FONTCHANGE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSinusFrame 

void CSinusFrame::Initialize()
{
	ASSERT(::IsWindow(m_hWnd));
	if(m_bInitialized==true)
		return;

	CFont* pOldFont;

	// Font-Ausmaße ermitteln...
	CDC* pDC = GetDC();
	ASSERT(pDC);
	if(m_pFont)
		pOldFont = pDC->SelectObject(m_pFont);

	TEXTMETRIC tm;
	VERIFY(pDC->GetTextMetrics(&tm));
	m_nCharHeight = tm.tmHeight;
	m_nCharWidth  = tm.tmMaxCharWidth;

	GetClientRect(m_rcClient);

	Cleanup();
	m_pDCScroll = new CDC;
	m_pDCSinus	= new CDC;
	m_pBMScroll	= new CBitmap;
	m_pBMSinus	= new CBitmap;
	ASSERT(m_pDCScroll && m_pDCSinus && m_pBMScroll && m_pBMSinus);

	m_rcScroll.SetRect(0, 0, m_rcClient.Width()+m_nCharWidth, m_nCharHeight);
	
	VERIFY(m_pDCScroll->CreateCompatibleDC(pDC));
	VERIFY(m_pBMScroll->CreateCompatibleBitmap(pDC, m_rcScroll.Width(), m_rcScroll.Height()));
	
	m_pDCScroll->SelectObject(m_pBMScroll);
	m_pDCScroll->PatBlt(0, 0, m_rcScroll.Width(), m_rcScroll.Height(), BLACKNESS);
	m_pDCScroll->SetTextColor(RGB(255,255,192));
	m_pDCScroll->SetBkColor(RGB(0,0,0));
	
	if(m_pFont)
		m_pDCScroll->SelectObject(m_pFont);
	
	VERIFY(m_pDCSinus->CreateCompatibleDC(pDC));
	VERIFY(m_pBMSinus->CreateCompatibleBitmap(pDC, m_rcClient.Width(), m_rcClient.Height()));
	
	m_pDCSinus->SelectObject(m_pBMSinus);
	m_pDCSinus->PatBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), BLACKNESS);

	ReleaseDC(pDC);
	
	if(m_pFont)
		pDC->SelectObject(pOldFont);

	m_bInitialized = true;
}

void CSinusFrame::OnFontChange() 
{
	CStatic::OnFontChange();
	m_bInitialized = false;	
}

void CSinusFrame::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	m_bInitialized = false;	
}

void CALLBACK AFX_EXPORT CSinusFrame::TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	ASSERT(hWnd);
	CSinusFrame* pSin = (CSinusFrame*)CWnd::FromHandle(hWnd);
	pSin->Scroll();
}

void CSinusFrame::SetText(LPCTSTR lpszText)
{
	m_strText = lpszText;
	m_nTextPos = 0;
	m_bInitialized = false;	
}

void CSinusFrame::Start()
{
	ASSERT(::IsWindow(m_hWnd));

	if(m_bRunning)
		Stop();

	m_bRunning = true;
	Initialize();
	m_nTimer = SetTimer(1, 15, TimerProc);
	ASSERT(m_nTimer!=0);
}

void CSinusFrame::Stop()
{
	ASSERT(::IsWindow(m_hWnd));

	if(m_bRunning)
	{
		ASSERT(m_nTimer!=0);
		KillTimer(m_nTimer);
		m_bRunning = false;
	}
}

TCHAR CSinusFrame::GetNextChar()
{
	if(m_nTextPos >= m_strText.GetLength())
		m_nTextPos = 0;

	return m_strText[m_nTextPos++];
}

void CSinusFrame::Scroll()
{
	if(m_bInitialized && m_bRunning)
	{
		DoCharBlit();
		DoSinScroll();
		
		CDC* pDC = GetDC();
		pDC->BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), m_pDCSinus, 0, 0, SRCCOPY);
		ReleaseDC(pDC);
	}
	else
		Initialize();
}

void CSinusFrame::DoCharBlit()
{
	if(m_nPixLeft <= 0)
	{
		TCHAR c = GetNextChar();

		m_pDCScroll->PatBlt(m_rcClient.right, m_rcScroll.top, m_rcScroll.right, m_rcScroll.bottom, BLACKNESS);
		CSize sz = m_pDCScroll->GetTextExtent((LPCTSTR)&c, 1);
		m_pDCScroll->TextOut(m_rcClient.right, m_rcScroll.top, (LPCTSTR)&c, 1);

		m_nPixLeft = sz.cx;
	}
}

void CSinusFrame::DoSinScroll()
{
	int nScrollWidth = -2;
	
	// first scroll Scroll-Bitmap
	m_pDCScroll->BitBlt(0, 0, m_rcScroll.Width()-2, m_rcScroll.Height(), m_pDCScroll, 2, 0, SRCCOPY);

	// clear sinus-bitmap
	m_pDCSinus->PatBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), BLACKNESS);

	// get sinustable-startposition
	m_nSinusPos = GetNextSinusOffset();

	for(int i=0; i<m_rcClient.Width(); i++)
	{
		double d = GetNextSinValue();
		
		int y = ((m_rcClient.Height() - 2*m_rcScroll.Height()) >> 1) + (m_rcScroll.Height() >> 1);
		y += (int)(d * y);

		m_pDCSinus->BitBlt(i, y, 1, y+m_rcScroll.Height(), m_pDCScroll, i, 0, SRCCOPY);
	}

	m_nPixLeft += nScrollWidth;
}

void CSinusFrame::OnClose() 
{
	Stop();	
	CStatic::OnClose();
}

double CSinusFrame::GetNextSinValue()
{
	if(++m_nSinusPos >= 720)
		m_nSinusPos = 0;

	return m_dSinusTable[m_nSinusPos];
}

int CSinusFrame::GetNextSinusOffset()
{
	m_nSinusOffset += m_nSinusSpeed;
	
	if(m_nSinusSpeed > 0 && m_nSinusOffset >= 720)
		m_nSinusOffset = 0;
	else if(m_nSinusSpeed < 0 && m_nSinusOffset < 0)
		m_nSinusOffset = 719;

	return m_nSinusOffset;
}

void CSinusFrame::SetFont(CFont * pFont)
{
	ASSERT(pFont);
	m_pFont			= pFont;
	m_nTextPos		= 0;
	m_bInitialized = false;	
}

void CSinusFrame::SetSinusSpeed(int n)
{
	m_nSinusSpeed = n;
}

void CSinusFrame::Cleanup()
{
	delete m_pDCScroll;
	delete m_pDCSinus;
	delete m_pBMScroll;
	delete m_pBMSinus;

	m_pDCScroll		= NULL;
	m_pDCSinus		= NULL;
	m_pBMScroll		= NULL;
	m_pBMSinus		= NULL;	
}
