
////////////////////////////////////////////////////////////////////////////////
//
//	Class		: CadvWnd
//  Author		: Andreas Leitner (aleitner@usa.net)
//  Description	: A CWnd derived class that is able to redraw itself flicker free
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __advWnd_H_
#define __advWnd_H_


// Forward Declarations
class CadvWnd;


// Combinable defines for Background mode
#define BM_DEF_WND_COL 1
#define BM_CUST_COL 2

class AFX_EXT_CLASS CadvWnd : public CWnd
{
	DECLARE_DYNCREATE(CadvWnd)


// Default Constructor & destructor
public:
	CadvWnd();
	virtual ~CadvWnd();

// Window Creation and Maintaince
	BOOL Create(const RECT& rect, CWnd* parent, UINT nID, CCreateContext* pCC = 0, 
				   DWORD style = WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VISIBLE, DWORD dwExStyle = /*WS_EX_CLIENTEDGE*/0);
	BOOL SubclassDlgItem(UINT nID, CWnd* parent); // use in Dialog/FormView 
							static void  RegisterClass();
	static LRESULT CALLBACK DummyWndProc(HWND, UINT, WPARAM, LPARAM);
	virtual WNDPROC*  GetSuperWndProcAddr();

	virtual BOOL CreateChildren();


// ClassWizard complient virtual overrides
	//{{AFX_VIRTUAL(CadvWnd)
	//}}AFX_VIRTUAL



// ClassWizard complient message map functions
protected:
	//{{AFX_MSG(CadvWnd)
	afx_msg void OnPaint();
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()



// CObject Debug functions overrides
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif // _DEBUG



// Attributes
public:


protected:
	// if true, it will update with a tmp bitmap
	BOOL     m_bFlickerFree;
	BOOL	 m_bUpdateContents;
	CBitmap* m_pbmpContents; // to get a faster update if flickerfree is on

	int m_iBackgroundMode;  // See BM defines 
	COLORREF m_colBackground;

// Operations
public:
	// (Operation description)
	virtual void InternalRedrawFG(CDC* pDC, CRect rcPaint);  // Overwrite this function
	virtual void InternalRedrawBG(CDC* pDC, CRect rcPaint);
	void ReCreateBitmap();
	void SetContentsChanged(BOOL yes = TRUE);
	BOOL IsContentsChanged();

	const int GetBackgroundMode();
	void SetBackgroundMode(COLORREF Color, int Mode = BM_CUST_COL); // To set the std mode just set col black and change the mode value
	COLORREF GetBackgroundColor();

	BOOL IsFlickerFree();
	void SetFlickerFree(BOOL bFlickerFree);
};
///////////////////////////////////////////////////////////////////////////

#endif  // __advWnd_H_
