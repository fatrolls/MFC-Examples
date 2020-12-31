#include "OXSizeCtrlBar.h"
#include "OX3DTabView.h"


class C3DTabViewBar : public COXSizeControlBar
{
	DECLARE_DYNAMIC(C3DTabViewBar);
// Construction
public:
	C3DTabViewBar();

	BOOL Create(CWnd * pParentWnd, const CString& sTitle=_T("3DTabViews"),
		const UINT nID=ID_3DTABVIEWBAR);

// Attributes
public:
	COX3DTabViewContainer m_TabViewContainer;
	CImageList m_ilTabView;

	CTreeCtrl m_treeClass;
	CTreeCtrl m_treeResource;
	CTreeCtrl m_treeFile;

	CImageList m_ilClass;
	CImageList m_ilResource;
	CImageList m_ilFile;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DTabViewBar)
	//}}AFX_VIRTUAL
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

// Implementation
public:
	virtual ~C3DTabViewBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DTabViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
