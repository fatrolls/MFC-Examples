// credits.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog

class CCredits : public CDialog
{
// Construction
public:
	CCredits(CWnd* pParent = NULL);   // standard constructor

	#define     DISPLAY_TIMER_ID		150		// timer id

 	RECT        m_ScrollRect,r;		   // rect of Static Text frame
	int         nArrIndex,nCounter;		   // work ints
	CString     m_szWork;			   // holds display line
	BOOL        m_bFirstTime;
	BOOL        m_bDrawText;
	int         nClip;
	int         nCurrentFontHeight;

	CWnd*       m_pDisplayFrame;

	CBitmap     m_bmpWork;                  // bitmap holder
	CBitmap* 	pBmpOld;                    // other bitmap work members
	CBitmap*    m_bmpCurrent;
	HBITMAP 	m_hBmpOld;

	CSize 		m_size;                     // drawing helpers
	CPoint 		m_pt;
	BITMAP 		m_bmpInfo;
	CDC 		m_dcMem;
	BOOL 		m_bProcessingBitmap;

// Dialog Data
	//{{AFX_DATA(CCredits)
	enum { IDD = IDD_DISPLAY };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCredits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCredits)
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
