// mysizeba.h : header file
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:38  $
/////////////////////////////////////////////////////////////////////////////
// CMyListBoxBar window

class CMyBitmapButton : public CMRCBitmapButton
{
public:
	DECLARE_DYNAMIC(CMyBitmapButton);
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP();
};
	

class CMyListBoxBar : public CMRCSizeControlBar
{
// Construction
public:
	BOOL Create(CWnd * pParentWnd);
	DECLARE_DYNAMIC(CMyListBoxBar);

	CMyListBoxBar();

// Attributes
public:
	CListBox  				m_ListBox;
	CMyBitmapButton			m_Button;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListBoxBar)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	protected:
		virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

// Implementation
public:
	virtual ~CMyListBoxBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListBoxBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void PopupMessage();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
