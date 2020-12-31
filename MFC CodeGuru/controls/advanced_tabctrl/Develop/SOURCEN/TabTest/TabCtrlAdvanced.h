// TabCtrlAdvanced.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlAdvanced window
#ifndef __TABCTRLADVANCED_H__ 
#define __TABCTRLADVANCED_H__ 

#define WM_CTLCOLOR_FIRST	WM_USER+1
#define WM_CTLCOLOR_TABITEM	WM_USER+1
#define WM_CTLCOLOR_DISPLAY WM_USER+2
#define WM_CTLCOLOR_BKGND	WM_USER+3
#define WM_CTLCOLOR_LAST	WM_USER+3

class CTabItemInfo : public CObject
{
	DECLARE_DYNCREATE(CTabItemInfo)
public:
	// Member
	CString		m_strText;
	COLORREF	m_Color;
	// Operation
	CTabItemInfo()
	{
		m_strText="EMPTY";
		m_Color = RGB(192,192,192);
	};
	~CTabItemInfo(){};
};

class CTabCtrlAdvanced : public CTabCtrl
{
// Construction
public:
	CTabCtrlAdvanced();

// Attributes
public:
	// The row in wich an Item or the rc of the Item is.
	// 0 : lowest row directly above the display
	int GetItemRow(int nItem);
	int GetItemRow(LPRECT pItemRec);
	// The Client Area of the TabCtrl
	void GetDisplayRect( LPRECT lpRect );
	// The Region of an Item
	//	outerRgn includes the Border, 
	//	the innerRgn is the whole area which can be used for displaying
	//		the individual Item
	BOOL getItemRgn( int nItem, CRgn& outerRgn, CRgn& innerRgn );
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlAdvanced)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	virtual HBRUSH OnCtlColor(CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, UINT nCtlColor);
// Implementation
public:
	virtual ~CTabCtrlAdvanced();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlAdvanced)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// DrawItem returns the Region used for the Item, so we can add it
	//		to the clipping Region, for minimizing drawing and flickering.
	virtual void DrawItem(CDC* pDC, CRgn& region, LPDRAWITEMSTRUCT lpDrawItemStruct);
	// subfunctions of DrawItem :
	virtual void drawItemBackground( CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct, 
								CRgn& usedRegion);
	virtual void drawItemText(CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//void drawItemIcon(CDC* pDC, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
#endif //__TABCTRLADVANCED_H__ 
/////////////////////////////////////////////////////////////////////////////
