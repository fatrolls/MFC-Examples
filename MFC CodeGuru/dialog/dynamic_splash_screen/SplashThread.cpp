#include "stdafx.h"

#include "SplashThread.h"

// 
// Copyright and author: 
// M.Loibl: mloibl@moss.de
// 
// You may handle this code to others only when you do not delete these
// copyright-lines.
// These source files may not be copied except by permission of the author.
// These source files may not be included in source or compiled form as any
// part of a commercial distribution except by permission of the
// author. 
// These files may be used freely for internal corporate use.
// These files may also may be used freely by students for 
// educational purposes.
// No warranty or guarrantee of fitness can be made to these files.
//
// 


//////////////////////////////////////////////////////////////////////////////////////////77
//
// DrawTransparentBitmap
//
//////////////////////////////////////////////////////////////////////////////////////////77

void DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, 
						   COLORREF cTransparentColor)
{
	COLORREF	cColor;
	CBitmap		*pBMAndBack,
				*pBMAndObject, 
				*pBMAndMem, 
				*pBMSave,
				*pBMBackOld, 
				*pBMObjectOld, 
				*pBMMemOld, 
				*pBMSaveOld;
	CDC			*pDCMem, 
				*pDCBack, 
				*pDCObject, 
				*pDCTemp, 
				*pDCSave;
	POINT		ptSize;
	int			mapMode = pDC->GetMapMode(),
				i;
	BITMAP		bitMap;

	pDCTemp = new CDC();
	pDCTemp->CreateCompatibleDC(pDC);
	pDCTemp->SetMapMode(mapMode);
	pDCTemp->SelectObject(pBitmap);

	i			= pBitmap->GetBitmap(&bitMap);
	ptSize.x	= bitMap.bmWidth;
	ptSize.y	= bitMap.bmHeight;
	pDCTemp->DPtoLP(&ptSize, 1);      // Convert from device to logical points

	// Create some DCs to hold temporary data.
	pDCBack = new CDC();	pDCBack->CreateCompatibleDC(pDC);		pDCBack->SetMapMode(mapMode);
	pDCObject = new CDC();	pDCObject->CreateCompatibleDC(pDC);		pDCObject->SetMapMode(mapMode);
	pDCMem  = new CDC();	pDCMem->CreateCompatibleDC(pDC);		pDCMem->SetMapMode(mapMode);
	pDCSave = new CDC();	pDCSave->CreateCompatibleDC(pDC);		pDCSave->SetMapMode(mapMode);

	// Create a bitmap for each DC. DCs are required for a number of GDI functions.

	// Monochrome DC
	pBMAndBack		= new CBitmap();	pBMAndBack->CreateBitmap(abs(ptSize.x), abs(ptSize.y), 1, 1, NULL);
	pBMAndObject	= new CBitmap();	pBMAndObject->CreateBitmap(abs(ptSize.x), abs(ptSize.y), 1, 1, NULL);
	
	pBMAndMem		= new CBitmap();	pBMAndMem->CreateCompatibleBitmap(pDC, abs(ptSize.x), abs(ptSize.y));
	pBMSave			= new CBitmap();	pBMSave->CreateCompatibleBitmap(pDC, abs(ptSize.x), abs(ptSize.y));

	// Each DC must select a bitmap object to store pixel data.
	pBMBackOld   = pDCBack->SelectObject(pBMAndBack);
	pBMObjectOld = pDCObject->SelectObject(pBMAndObject);
	pBMMemOld    = pDCMem->SelectObject(pBMAndMem);
	pBMSaveOld   = pDCSave->SelectObject(pBMSave);

	// Set proper mapping mode.
//	pDCTemp->SetMapMode(pDC->GetMapMode());

	// Save the bitmap sent here, because it will be overwritten.
	pDCSave->BitBlt(0, 0, ptSize.x, ptSize.y, pDCTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	cColor = pDCTemp->SetBkColor(cTransparentColor);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	pDCObject->BitBlt(0, 0, ptSize.x, ptSize.y, pDCTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC back to the original color.
	pDCTemp->SetBkColor(cColor);

	// Create the inverse of the object mask.
	pDCBack->BitBlt(0, 0, ptSize.x, ptSize.y, pDCObject, 0, 0, NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	pDCMem->BitBlt(0, 0, ptSize.x, ptSize.y, pDC, xStart, yStart, SRCCOPY);

	// Mask out the places where the bitmap will be placed.
	pDCMem->BitBlt(0, 0, ptSize.x, ptSize.y, pDCObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	// ??
	pDCTemp->BitBlt(0, 0, ptSize.x, ptSize.y, pDCBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	pDCMem->BitBlt(0, 0, ptSize.x, ptSize.y, pDCTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	pDC->BitBlt(xStart, yStart, ptSize.x, ptSize.y, pDCMem, 0, 0, SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	pDCTemp->BitBlt(0, 0, ptSize.x, ptSize.y - abs(ptSize.y), pDCSave, 0, 0, SRCCOPY);
	
	// Delete the memory bitmaps.
	DeleteObject(pDCBack->SelectObject(pBMBackOld));
	DeleteObject(pDCObject->SelectObject(pBMObjectOld));
	DeleteObject(pDCMem->SelectObject(pBMMemOld));
	DeleteObject(pDCSave->SelectObject(pBMSaveOld));

	delete pBMAndBack;
	delete pBMAndObject;
	delete pBMAndMem;
	delete pBMSave;


	// Delete the memory DCs.
	pDCMem->DeleteDC();			delete pDCMem;
	pDCBack->DeleteDC();		delete pDCBack;
	pDCObject->DeleteDC();		delete pDCObject;
	pDCSave->DeleteDC();		delete pDCSave;
	pDCTemp->DeleteDC();		delete pDCTemp;
}

//////////////////////////////////////////////////////////////////////////////////////////77
//
// CSplashScreen
//
//////////////////////////////////////////////////////////////////////////////////////////77

#define idTimerDuration 999
#define idTimerInternal   1

//
// creation
//

BEGIN_MESSAGE_MAP(CSplashScreen, CWnd)
	//{{AFX_MSG_MAP(CSplashScreen)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSplashScreen::CSplashScreen()
{
}

CSplashScreen::~CSplashScreen()
{
}

BOOL CSplashScreen::Create(void)
{
	if( m_pThread->m_IdBitmap == 0 )
	{
		AfxDebugBreak();
		return FALSE;
	}

	if (!m_pThread->m_bitmap.LoadBitmap(m_pThread->m_IdBitmap))
		return FALSE;

	BITMAP bm;
	m_pThread->m_bitmap.GetBitmap(&bm);

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, m_pThread->m_pParent->GetSafeHwnd(), NULL);
}

void CSplashScreen::HideSplashScreen()
{
	DestroyWindow();
}

void CSplashScreen::PostNcDestroy()
{
	m_pThread->PostNcDestroy();
}

int CSplashScreen::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow();
	
	// Set topmost
	const CWnd *pWnd = (&CWnd::wndTopMost);
	SetWindowPos( pWnd, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);

	// Set a timer to destroy the splash screen.
	if( m_pThread->m_Duration > 0 )
		SetTimer(idTimerDuration, m_pThread->m_Duration, NULL);
	
	if( m_pThread->m_InternalTimer > 0 )
		SetTimer(idTimerInternal, m_pThread->m_InternalTimer, NULL);
	
	OnInitialUpdate();

	return 0;
}

void CSplashScreen::OnTimer(UINT nIDEvent)
{
	if( nIDEvent == idTimerInternal )
		m_pThread->OnTimerInternal();
	
	if( nIDEvent == idTimerDuration )
		// Destroy the splash screen window.
		HideSplashScreen();
}

void CSplashScreen::SetThread(CSplashThread *pThread)
{
	m_pThread = pThread;
}

//
// Painting
//

void CSplashScreen::OnInitialUpdate(void)
{
	BITMAP bm;
	m_pThread->m_bitmap.GetBitmap(&bm);
	m_pThread->m_SizeBitmapX = bm.bmWidth;
	m_pThread->m_SizeBitmapY = bm.bmHeight;
}

void CSplashScreen::OnPaint()
{
	CPaintDC	dc(this);
	
	m_pThread->OnDraw(&dc);
}	


//////////////////////////////////////////////////////////////////////
//
// CSplashThread
//
//////////////////////////////////////////////////////////////////////

//
// statics
//

BOOL CSplashThread::c_bShowSplashWnd = TRUE;

IMPLEMENT_DYNCREATE(CSplashThread, CWinThread)

BEGIN_MESSAGE_MAP(CSplashThread, CWinThread)
	//{{AFX_MSG_MAP(CSplashThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSplashThread::CSplashThread()
{
	m_bAutoDelete = TRUE;

	m_TextVersion		= "Version";
	m_Duration			= 4500;
	m_InternalTimer		= 0;

	m_pFontVersionSub		= NULL;
	m_pFontVersionMain		= NULL;
	m_pFontHeaderSubSmall	= NULL;
	m_pFontHeaderSubBig		= NULL;
	m_pFontHeaderMain		= NULL;
	m_pParent				= NULL;

	SetDefaultsFonts();
	SetDefaultsPositions();
}

void CSplashThread::SetDefaultsFonts()
{
	m_nHeightHeaderMain			= 48;
	m_nWeightHeaderMain			= FW_BOLD;
	m_bItalicHeaderMain			= TRUE;
	m_nOutPreHeaderMain			= OUT_TT_PRECIS;
	m_FacenameHeaderMain		= "Courier New";

	m_nHeightHeaderSubBig		= 26;
	m_nWeightHeaderSubBig		= FW_BOLD;
	m_bItalicHeaderSubBig		= TRUE;
	m_nOutPreHeaderSubBig		= OUT_TT_PRECIS;
	m_FacenameHeaderSubBig		= "Arial";

	m_nHeightHeaderSubSmall		= 18;
	m_nWeightHeaderSubSmall		= FW_BOLD;
	m_bItalicHeaderSubSmall		= TRUE;
	m_nOutPreHeaderSubSmall		= OUT_TT_PRECIS;
	m_FacenameHeaderSubSmall	= "Arial";

	m_nHeightVersionMain		= 12;
	m_nWeightVersionMain		= FW_BOLD;
	m_bItalicVersionMain		= FALSE;
	m_nOutPreVersionMain		= 0;
	m_FacenameVersionMain		= "MS Sans Serif";

	m_nHeightVersionSub			= 8;
	m_nWeightVersionSub			= FW_NORMAL;
	m_bItalicVersionSub			= FALSE;
	m_nOutPreVersionSub			= 0;
	m_FacenameVersionSub		= "MS Sans Serif";
}

void CSplashThread::SetDefaultsPositions()
{
	m_ptHeaderMain			= CPoint(  52,  86);
	m_ptHeaderSub			= CPoint(  52, 121);
	m_ptVersion				= CPoint(  52, 210);
	m_ptVersionsLeft		= CPoint( 121, 210);
	m_ptVersionsRight		= CPoint( 210, 210);
	m_ptCustomizedMain		= CPoint( 255, 210);
	m_ptCustomized			= CPoint( 255, 225);
	m_szDeltaHeaderMain		= CSize(    0,  30);
	m_szDeltaHeaderSub		= CSize(    0,  30);
	m_szDeltaVersionsLeft	= CSize(    0,  15);
	m_szDeltaVersionsRight	= CSize(    0,  15);
	m_szDeltaCustomized		= CSize(    0,  15);
}



CSplashThread::~CSplashThread()
{
}

int CSplashThread::InitInstance()
{
	SetThreadPriority(/*GetThreadPriority()+2*/THREAD_PRIORITY_HIGHEST);
	m_wndSplash.SetThread(this);
	m_TickCountsCreated = GetTickCount();
	
	if (!c_bShowSplashWnd )
	{
		m_wndSplash.PostNcDestroy();
		return FALSE;
	}
	else
	{
		if( !m_wndSplash.Create() )
		{
			m_wndSplash.PostNcDestroy();
			return FALSE;
		}
		else
		{
			m_wndSplash.UpdateWindow();
			return TRUE;
		}
	}
}


//
// Members
//

void CSplashThread::SetTextCustomized(const char *s)	{ m_TextCustomized = s;		}
void CSplashThread::SetTextVersion(const char *s)		{ m_TextVersion = s;		}

void CSplashThread::OnTimerInternal(void)
{
	// Overload in derived classes
}

void CSplashThread::SetBitmapId(UINT idBitmap)			{ m_IdBitmap = idBitmap;	}
void CSplashThread::SetTimerDuration(UINT time)			{ m_Duration = time;		}
void CSplashThread::SetTimerInternal(UINT time)			{ m_InternalTimer = time;	}

void CSplashThread::SetFontHeaderMain(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename)
{
	m_nHeightHeaderMain		= nHeight;
	m_nWeightHeaderMain		= nWeight;
	m_bItalicHeaderMain		= bItalic;
	m_nOutPreHeaderMain		= nOutPrecision;
	m_FacenameHeaderMain	= lpszFacename;
}

void CSplashThread::SetFontHeaderSubBig(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename)
{
	m_nHeightHeaderSubBig	= nHeight;
	m_nWeightHeaderSubBig	= nWeight;
	m_bItalicHeaderSubBig	= bItalic;
	m_nOutPreHeaderSubBig	= nOutPrecision;
	m_FacenameHeaderSubBig	= lpszFacename;
}

void CSplashThread::SetFontHeaderSubSmall(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename)
{
	m_nHeightHeaderSubSmall	= nHeight;
	m_nWeightHeaderSubSmall	= nWeight;
	m_bItalicHeaderSubSmall	= bItalic;
	m_nOutPreHeaderSubSmall	= nOutPrecision;
	m_FacenameHeaderSubSmall= lpszFacename;
}

void CSplashThread::SetFontVersionMain(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename)
{
	m_nHeightVersionMain	= nHeight;
	m_nWeightVersionMain	= nWeight;
	m_bItalicVersionMain	= bItalic;
	m_nOutPreVersionMain	= nOutPrecision;
	m_FacenameVersionMain	= lpszFacename;
}

void CSplashThread::SetFontVersionSub(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename)
{
	m_nHeightVersionSub		= nHeight;
	m_nWeightVersionSub		= nWeight;
	m_bItalicVersionSub		= bItalic;
	m_nOutPreVersionSub		= nOutPrecision;
	m_FacenameVersionSub	= lpszFacename;
}

void CSplashThread::SetStartHeaderMain(CPoint pt)		{ m_ptHeaderMain = pt;				}
void CSplashThread::SetStartHeaderSub(CPoint pt)		{ m_ptHeaderSub = pt;				}
void CSplashThread::SetStartVersion(CPoint pt)			{ m_ptVersion = pt;					}
void CSplashThread::SetStartVersionLeft(CPoint pt)		{ m_ptVersionsLeft = pt;			}
void CSplashThread::SetStartVersionRight(CPoint pt)		{ m_ptVersionsRight = pt;			}
void CSplashThread::SetStartCustomizedMain(CPoint pt)	{ m_ptCustomizedMain = pt;			}
void CSplashThread::SetStartCustomized(CPoint pt)		{ m_ptCustomized = pt;				}
void CSplashThread::SetDeltaHeaderMain(CSize delta)		{ m_szDeltaHeaderMain = delta;		}
void CSplashThread::SetDeltaHeaderSub(CSize delta)		{ m_szDeltaHeaderSub = delta;		}
void CSplashThread::SetDeltaVersionLeft(CSize delta)	{ m_szDeltaVersionsLeft = delta;	}
void CSplashThread::SetDeltaVersionRight(CSize delta)	{ m_szDeltaVersionsRight = delta;	}
void CSplashThread::SetDeltaCustomized(CSize delta)		{ m_szDeltaCustomized = delta;		}

void CSplashThread::AddStringVersion(CString s)
{
	m_ListTextVersions.AddTail(s);
}

void CSplashThread::AddStringVersionRight(CString s)
{
	m_ListTextVersionsRight.AddTail(s);
}

void CSplashThread::AddStringCustom(CString s)
{
	m_ListTextCustomized.AddTail(s);
}

void CSplashThread::AddStringHeaderMain(CString s)
{
	m_ListTextHeaderMain.AddTail(s);
}

void CSplashThread::AddStringHeaderSub(CString s)
{
	m_ListTextHeaderSub.AddTail(s);
}

void CSplashThread::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashThread::SetParent(CWnd *pParent)
{
	m_pParent = pParent;
}


void CSplashThread::PostNcDestroy()
{
	AfxEndThread(1, TRUE);	// ret code, delete
	if( m_pParent )
		m_pParent->SetForegroundWindow();
}

//
//
// "m_HeaderMain" (fontHeaderMain)
// "m_HeaderSub"  (fontHeaderSubBig, fontHeaderSubSmall)
//
//
// Versions (fontVersionMain)  "Main"     "2.0.0.2"    "m_TextCopyright" 
//                              (fontVersionSub)       "m_TextCustomized" (fontVersionMain)     
//

void CSplashThread::OnDraw(CDC *pDC)
{
	double		iUmrechnung		= -pDC->GetDeviceCaps(LOGPIXELSY)/72,
				dHeaderMain		= 0.5 + iUmrechnung * m_nHeightHeaderMain,
				dHeaderSubBig	= 0.5 + iUmrechnung * m_nHeightHeaderSubBig,
				dHeaderSubSmall	= 0.5 + iUmrechnung * m_nHeightHeaderSubSmall,
				dVersionMain	= 0.5 + iUmrechnung * m_nHeightVersionMain,
				dVersionSub		= 0.5 + iUmrechnung * m_nHeightVersionSub;
	UINT		uOldAlign;
	CFont		fontVersionSub,
				fontVersionMain,
				fontHeaderSubSmall,
				fontHeaderSubBig,
				fontHeaderMain,
				*pOldFont;
	COLORREF	oldColor;
	int			oldBkMode;

	fontHeaderMain.		CreateFont((int)dHeaderMain,	0,0,0, m_nWeightHeaderMain,		m_bItalicHeaderMain,	0,0,0, m_nOutPreHeaderMain,		0, PROOF_QUALITY,0, m_FacenameHeaderMain);
	fontHeaderSubBig.	CreateFont((int)dHeaderSubBig,	0,0,0, m_nWeightHeaderSubBig,	m_bItalicHeaderSubBig,	0,0,0, m_nOutPreHeaderSubBig,	0, PROOF_QUALITY,0, m_FacenameHeaderSubBig);
	fontHeaderSubSmall.	CreateFont((int)dHeaderSubSmall,0,0,0, m_nWeightHeaderSubSmall,	m_bItalicHeaderSubSmall,0,0,0, m_nOutPreHeaderSubSmall,	0, PROOF_QUALITY,0, m_FacenameHeaderSubSmall);
	fontVersionMain.	CreateFont((int)dVersionMain,	0,0,0, m_nWeightVersionMain,	m_bItalicVersionMain,	0,0,0, m_nOutPreVersionMain,	0, PROOF_QUALITY,0, m_FacenameVersionMain);
	fontVersionSub.		CreateFont((int)dVersionSub,	0,0,0, m_nWeightVersionSub,		m_bItalicVersionSub,	0,0,0, m_nOutPreVersionSub,		0, PROOF_QUALITY,0, m_FacenameVersionSub);

	m_pFontVersionSub		= &fontVersionSub;
	m_pFontVersionMain		= &fontVersionMain;
	m_pFontHeaderSubSmall	= &fontHeaderSubSmall;
	m_pFontHeaderSubBig		= &fontHeaderSubBig;
	m_pFontHeaderMain		= &fontHeaderMain;
	
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(pDC))
		return;

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	pDC->BitBlt(0, 0, m_SizeBitmapX, m_SizeBitmapY, &dcImage, 0, 0, SRCCOPY);

	oldColor	= pDC->SetTextColor(RGB(0,0,0));
	oldBkMode	= pDC->SetBkMode(TRANSPARENT);
	uOldAlign	= pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pOldFont	= (CFont *) pDC->SelectStockObject(ANSI_FIXED_FONT);

	//
	// real drawing
	//
	DrawEverything(pDC);

	//
	// old Settings
	//
	pDC->SetTextColor(oldColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(uOldAlign);
	pDC->SelectObject(pOldFont);
	dcImage.SelectObject(pOldBitmap);

	fontVersionSub.DeleteObject();
	fontVersionMain.DeleteObject();
	fontHeaderSubSmall.DeleteObject();
	fontHeaderSubBig.DeleteObject();
	fontHeaderMain.DeleteObject();
}

/////////////////////////////
//
// Drawings
//
/////////////////////////////
void CSplashThread::DrawEverything(CDC *pDC)
{
	DrawPre(pDC);
	DrawHeaderMain(pDC);
	DrawHeaderSub(pDC);
	DrawVersionMain(pDC);
	DrawVersionSub(pDC);
	DrawVersionSubRight(pDC);
	DrawCustomizedMain(pDC);
	DrawCustomizedSub(pDC);
	DrawPost(pDC);
}

/////////////////////////////
//
// Header Main
//
/////////////////////////////
void CSplashThread::DrawHeaderMain(CDC *pDC)
{
	POSITION	pos;
	CString		str;
	int			xPos,	yPos,
				dx,		dy;

	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
	pDC->SelectObject(m_pFontHeaderMain);

	xPos = m_ptHeaderMain.x;	dx = m_szDeltaHeaderMain.cx;
	yPos = m_ptHeaderMain.y;	dy = m_szDeltaHeaderMain.cy;
	for(pos = m_ListTextHeaderMain.GetHeadPosition(); pos!=NULL;  )
	{
		str = m_ListTextHeaderMain.GetNext(pos);
		pDC->TextOut(xPos, yPos, str);
		xPos += dx;
		yPos += dy;
	}
}

/////////////////////////////
//
// Header Sub
//
/////////////////////////////
void CSplashThread::DrawHeaderSub(CDC *pDC)
{
	POSITION	pos;
	CString		str;
	int			xPos,	yPos,
				dx,		dy;

	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);
	pDC->SelectObject(m_pFontHeaderMain);

	xPos = m_ptHeaderSub.x;	dx = m_szDeltaHeaderSub.cx;
	yPos = m_ptHeaderSub.y;	dy = m_szDeltaHeaderSub.cy;
	for(pos = m_ListTextHeaderSub.GetHeadPosition(); pos!=NULL;  )
	{
		str = m_ListTextHeaderSub.GetNext(pos);
		DrawBigSmallToggled(pDC, str, xPos, yPos, m_pFontHeaderSubBig, m_pFontHeaderSubSmall);
		xPos += dx;
		yPos += dy;
	}
}

void CSplashThread::DrawBigSmallToggled(CDC *pDC, CString &str, int xStart, int yStart, CFont *pFontBig, CFont *pFontSmall)
{
	// 
	// all capital letters: fontHeaderSubBig
	// all small    -=-     fontHeaderSubSmall
	//
	char		*pText,
				*pPosMax,
				*pPos,
				*pTemp,
				*pPartString;
	BOOL		bBig;
	int			delta;
	CSize		size;
	int			xTemp;
	
	pText		= new char [str.GetLength() + 1];
	pPartString = new char [str.GetLength() + 1];
	
	strcpy(pText, str);
	pPos		= pText;
	pPosMax		= pPos + strlen(pText);
	xTemp		= xStart;
	
	for( ; pPos<pPosMax ; )
	{
		// first one of partstring
		bBig = isupper(*pPos);
		
		// extract part
		pTemp = pPos;
		if( bBig )
		{
			while( /*!islower*/ isupper(*pTemp) && (pTemp<pPosMax) )	// all extra-characters
				pTemp++;
		}
		else
		{
			while( !isupper(*pTemp) && (pTemp<pPosMax) )
				pTemp++;
		}
		strncpy(pPartString, pPos, (pTemp-pPos) );
		*(pPartString +(pTemp-pPos)) = '\0';

		// set Font
		if( bBig )	
		{	
			pDC->SelectObject(pFontBig);
			delta = 2;
		}
		else
		{
			pDC->SelectObject(pFontSmall);
			delta = 0;
		}

		// TextOut
		pDC->TextOut(xTemp, yStart+delta, pPartString, strlen(pPartString));
		
		// set actual position
		size = pDC->GetTextExtent(pPartString, strlen(pPartString));	
		xTemp += size.cx;
		
		pPos += strlen(pPartString);
	}

	delete pText;
	delete pPartString;
}

/////////////////////////////
//
// Version Main
//
/////////////////////////////
void CSplashThread::DrawVersionMain(CDC *pDC)
{
	pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pDC->SelectObject(m_pFontVersionMain);
	pDC->TextOut(m_ptVersion.x, m_ptVersion.y, m_TextVersion);
}

/////////////////////////////
//
// Version Sub
//
/////////////////////////////
void CSplashThread::DrawVersionSub(CDC *pDC)
{
	POSITION	pos;
	CString		str;
	int			xPos,	yPos,
				dx,		dy;

	pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pDC->SelectObject(m_pFontVersionSub);
	
	xPos = m_ptVersionsLeft.x;	dx = m_szDeltaVersionsLeft.cx;
	yPos = m_ptVersionsLeft.y;	dy = m_szDeltaVersionsLeft.cy;
	for(pos = m_ListTextVersions.GetHeadPosition(); pos!=NULL;  )
	{
		str = m_ListTextVersions.GetNext(pos);
		pDC->TextOut(xPos, yPos, str);
		xPos += dx;
		yPos += dy;
	}
}

/////////////////////////////
//
// Version Sub Right
//
/////////////////////////////
void CSplashThread::DrawVersionSubRight(CDC *pDC)
{
	POSITION	pos;
	CString		str;
	int			xPos,	yPos,
				dx,		dy;

	pDC->SetTextAlign(TA_RIGHT | TA_TOP);
	pDC->SelectObject(m_pFontVersionSub);
	
	xPos = m_ptVersionsRight.x;	dx = m_szDeltaVersionsRight.cx;
	yPos = m_ptVersionsRight.y;	dy = m_szDeltaVersionsRight.cy;
	for(pos = m_ListTextVersionsRight.GetHeadPosition(); pos!=NULL; )
	{
		str = m_ListTextVersionsRight.GetNext(pos);
		pDC->TextOut(xPos, yPos, str);
		xPos += dx;
		yPos += dy;
	}
}

/////////////////////////////
//
// Customized Main
//
/////////////////////////////
void CSplashThread::DrawCustomizedMain(CDC *pDC)
{
	pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pDC->SelectObject(m_pFontVersionMain);
	pDC->TextOut(m_ptCustomizedMain.x, m_ptCustomizedMain.y, m_TextCustomized);
}

/////////////////////////////
//
// Customized Sub
//
/////////////////////////////
void CSplashThread::DrawCustomizedSub(CDC *pDC)
{
	POSITION	pos;
	CString		str;
	int			xPos,	yPos,
				dx,		dy;

	pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pDC->SelectObject(m_pFontVersionSub);
	
	xPos = m_ptCustomized.x;	dx = m_szDeltaCustomized.cx;
	yPos = m_ptCustomized.y;	dy = m_szDeltaCustomized.cy;
	for(pos = m_ListTextCustomized.GetHeadPosition(); pos!=NULL; )
	{
		str = m_ListTextCustomized.GetNext(pos);
		pDC->TextOut(xPos, yPos, str);
		xPos += dx;
		yPos += dy;
	}
}

/////////////////////////////
//
// DrawPre
// DrawPost
//
/////////////////////////////
void CSplashThread::DrawPre(CDC *pDC)
{
	// use in your derived classes!
}

void CSplashThread::DrawPost(CDC *pDC)
{
	// use in your derived classes!
}

void CSplashThread::InvalidateRect(LPCRECT lpRect, BOOL bErase)
{
	m_wndSplash.InvalidateRect(lpRect, bErase);
}

void CSplashThread::Invalidate(BOOL bErase)
{
	m_wndSplash.Invalidate(bErase);
}

void CSplashThread::HideSplashScreen(void)
{
	m_wndSplash.HideSplashScreen();
}

DWORD CSplashThread::GetCreationTime(void)
{
	return m_TickCountsCreated;
}
