#include "OXSizeCtrlBar.h"
#include "OXTabView.h"
#include "OXHistoryCtrl.h"


class CTabViewBar : public COXSizeControlBar
{
	DECLARE_DYNAMIC(CTabViewBar);
// Construction
public:
	CTabViewBar();

	BOOL Create(CWnd * pParentWnd, const CString& sTitle=_T("TabView"),
		const UINT nID=ID_TABVIEWBAR);

// Attributes
public:
	COXTabViewContainer m_TabViewContainer;

protected:
	COXTabViewPage<COXHistoryCtrl> m_build;
	COXTabViewPage<COXHistoryCtrl> m_debug;
	COXTabViewPage<COXHistoryCtrl> m_find1;
	COXTabViewPage<COXHistoryCtrl> m_find2;
	COXTabViewPage<COXHistoryCtrl> m_results;
	COXTabViewPage<COXHistoryCtrl> m_SQLdebug;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabViewBar)
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
