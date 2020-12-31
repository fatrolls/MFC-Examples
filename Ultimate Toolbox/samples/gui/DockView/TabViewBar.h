// mysizeba.h : header file
//
// Docktest demo of Dockable Views functionality
// CTabViewBar window

#include "OXSizeCtrlBar.h"
#include "OXTabView.h"


class CTabViewBar : public COXSizeControlBar
{
// Construction
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("TabViews"),
		const UINT nID=ID_TABVIEWBAR);
	DECLARE_DYNAMIC(CTabViewBar);

	CTabViewBar();

// Attributes
public:
	COXTabViewContainer m_TabViewContainer;

	COXTabViewPage<CEdit> edit;
	COXTabViewPage<CListBox> listBox;
	COXTabViewPage<CListCtrl> listCtrl;
	COXTabViewPage<CTreeCtrl> treeCtrl;
	COXTabViewPage<CRichEditCtrl> richEditCtrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewBar)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	protected:
		virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

// Implementation
public:
	virtual ~CTabViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
