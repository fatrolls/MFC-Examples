#ifndef __SPLASH_THREAD_H__
#define __SPLASH_THREAD_H__

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

//
// DrawTransparentBitmap
//
// Draws a Bitmap in pDC transparent.
//
// pDC                 
// pBitmap             Bitmap to paint
// xStart              Startpos of bitmap
// yStart
// cTransparentColor   This Farbe is used as transparent
//                     e.g.:  RGB(255,255,255) == (0x00FFFFFF) for white 
//
//
// overtaken and changed from: Q79212 
// see also:   Q89375
void DrawTransparentBitmap(CDC *pDC, CBitmap *pBitmap, short xStart, short yStart, 
						   COLORREF cTransparentColor);

//////////////////////////////////////////////////////////////////////
//
// CSplashScreen
//
//////////////////////////////////////////////////////////////////////
// 
// arbeitet mit CSplashThread zusammen, siehe dort
//
class CSplashThread;
class CSplashScreen : public CWnd
{
	friend class CSplashThread;

public:
	CSplashScreen();
	~CSplashScreen();

	virtual void	OnInitialUpdate();
	virtual void	PostNcDestroy();
	void			SetThread(CSplashThread *pThread);

	//{{AFX_VIRTUAL(CSplashScreen)
	//}}AFX_VIRTUAL

protected:

	BOOL	Create(void);
	void	HideSplashScreen();

	CSplashThread	*m_pThread;

	//{{AFX_MSG(CSplashScreen)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
//
// CSplashThread
//
//////////////////////////////////////////////////////////////////////
//
// shows splash-screen!
//
// call it like: :
// 
//	int CFrameMain::OnCreate(LPCREATESTRUCT lpCreateStruct)
//	{
//		CMyThread	*pThread = new CMyThread();	// CMyThread is derived from CSplashThread
//		pThread->Set...
//		pThread->CreateThread();	// self-deleting, do not call "delete pThread"
//		...
//	}
//
//
//
// * the fonts are created before drawing, because 
//   then you have the chance to animate text
// * do the animation with OnTimerInternal(): reset sizes, positions of the text, font ...
// * you could also overload DrawEverything() to set the text-color
//   but don't forget to call CSplashThread::DrawEverything() then
// * do not call "delete pThread", becaus it deletes itself 
//   when calling "HideSplashScreen()"
// 
class CSplashThread : public CWinThread
{
	friend class CSplashScreen;

	DECLARE_DYNCREATE(CSplashThread)
public:
	CSplashThread();
	virtual ~CSplashThread();

	//
	// Setting Text-effects and positions
	//
	virtual void	SetDefaultsFonts(void);			// sets the fonts
	virtual void	SetDefaultsPositions(void);		// sets default positions: please overload to fit to your bitmaps

	//
	// Setting timer
	//
	void			SetTimerDuration(UINT time);
	void			SetTimerInternal(UINT time);

	// 
	// Setting the bitmap (very important!)
	// you could create a SetBitmap(CBitmap *) function here, i was too lazy for that!
	//
	void			SetBitmapId(UINT idBitmap);	

	//
	// setting the font-properties
	//
	void			SetFontHeaderMain(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename);
	void			SetFontHeaderSubBig(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename);
	void			SetFontHeaderSubSmall(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename);
	void			SetFontVersionMain(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename);
	void			SetFontVersionSub(int nHeight, int nWeight, BYTE bItalic, BYTE nOutPrecision, LPCTSTR lpszFacename);
	
	// 
	// Setting text-positions
	//
	void			SetStartHeaderMain(CPoint pt);
	void			SetStartHeaderSub(CPoint pt);
	void			SetStartVersion(CPoint pt);
	void			SetStartVersionLeft(CPoint pt);
	void			SetStartVersionRight(CPoint pt);
	void			SetStartCustomizedMain(CPoint pt);
	void			SetStartCustomized(CPoint pt);
	void			SetDeltaHeaderMain(CSize delta);
	void			SetDeltaHeaderSub(CSize delta);
	void			SetDeltaVersionLeft(CSize delta);
	void			SetDeltaVersionRight(CSize delta);
	void			SetDeltaCustomized(CSize delta);
	
	//
	// setting the text
	//
	void			SetTextCustomized(const char *s);
	void			SetTextVersion(const char *s);
	void			AddStringHeaderMain(CString s);
	void			AddStringHeaderSub(CString s);
	void			AddStringVersion(CString s);
	void			AddStringVersionRight(CString s);
	void			AddStringCustom(CString s);

	//
	// Other settings
	//
	void			SetParent(CWnd *pParent);
	void			HideSplashScreen(void);
	DWORD			GetCreationTime(void);


	//
	// virtual finctions:
	//
	// timer
	virtual void	OnTimerInternal();				// is called to get animation effects (e.g.)
	// Drawings
	virtual void	OnDraw(CDC *pDC);				// set and reset CDC-Settings
	virtual void	DrawEverything(CDC *pDC);		// calls drawing-subfunctions
	virtual void	DrawHeaderMain(CDC *pDC);		// Drawing: Main Header
	virtual void	DrawHeaderSub(CDC *pDC);		// Drawing: Sub- Header
	virtual void	DrawVersionMain(CDC *pDC);		// Drawing: "Version"
	virtual void	DrawVersionSub(CDC *pDC);		// Drawing: Version -Text (left)
	virtual void	DrawVersionSubRight(CDC *pDC);	// Drawing: Version -Text (right)
	virtual void	DrawCustomizedMain(CDC *pDC);	// Drawing: "Customized for"
	virtual void	DrawCustomizedSub(CDC *pDC);	// Drawing: Customized second line
	virtual void	DrawPre(CDC *pDC);				// Drawing: before all other stuff
	virtual void	DrawPost(CDC *pDC);				// Drawing: after all other stuff

	static void		EnableSplashScreen(BOOL bEnable = TRUE);

	//
	// members and internal functions
	//
protected:
	CSplashScreen		m_wndSplash;

	UINT		m_Duration,			// Zeit, wielange Bitmap zu sehen ist; 0 => immer!
				m_InternalTimer;	// interner Timer für Animationen
	UINT		m_IdBitmap;
	CBitmap		m_bitmap;
	CFont		*m_pFontVersionSub,
				*m_pFontVersionMain,
				*m_pFontHeaderSubSmall,
				*m_pFontHeaderSubBig,
				*m_pFontHeaderMain;
	int			m_SizeBitmapX, m_SizeBitmapY;
	CWnd		*m_pParent;

	double		m_nHeightHeaderMain,		m_nHeightVersionMain,	m_nHeightVersionSub,	m_nHeightHeaderSubBig,	m_nHeightHeaderSubSmall;
	int			m_nWeightHeaderMain,		m_nWeightVersionMain,	m_nWeightVersionSub,	m_nWeightHeaderSubBig,	m_nWeightHeaderSubSmall;
	BYTE		m_bItalicHeaderMain,		m_bItalicVersionMain,	m_bItalicVersionSub,	m_bItalicHeaderSubBig,	m_bItalicHeaderSubSmall;
	BYTE		m_nOutPreHeaderMain,		m_nOutPreVersionMain,	m_nOutPreVersionSub,	m_nOutPreHeaderSubBig,	m_nOutPreHeaderSubSmall;
	CString		m_FacenameHeaderMain,		m_FacenameVersionMain,	m_FacenameVersionSub,	m_FacenameHeaderSubBig,	m_FacenameHeaderSubSmall;
	CPoint		m_ptHeaderMain,				// starting-points for text
				m_ptHeaderSub,	
				m_ptVersion,
				m_ptVersionsLeft,
				m_ptVersionsRight,
				m_ptCustomizedMain,
				m_ptCustomized;
	CSize		m_szDeltaHeaderMain,		// size between lines
				m_szDeltaHeaderSub,
				m_szDeltaVersionsLeft,
				m_szDeltaVersionsRight,
				m_szDeltaCustomized;
	CString		m_TextCustomized,
				m_TextVersion;
	CStringList	m_ListTextHeaderMain,
				m_ListTextHeaderSub,
				m_ListTextVersions,
				m_ListTextVersionsRight,
				m_ListTextCustomized;
	DWORD		m_TickCountsCreated;

	void	DrawBigSmallToggled(CDC *pDC, CString &str, int xStart, int yStart, CFont *pFontBig, CFont *pFontSmall);
	void	PostNcDestroy();
	void	InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE );
	void	Invalidate(BOOL bErase = TRUE );

	static BOOL	c_bShowSplashWnd;

	//{{AFX_VIRTUAL(CSplashThread)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSplashThread)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif


