// CategVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoriesView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CCategoriesView : public CDaoRecordView
{
protected:
	CCategoriesView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCategoriesView)

// Form Data
public:
	//{{AFX_DATA(CCategoriesView)
	enum { IDD = IDD_CATEGORIES };
	//}}AFX_DATA

// Attributes
public:
	CMSDIDaoDoc* GetDocument();
	CCategoriesSet *m_pCategoriesSet;

// Operations
public:
	void InvalidateDlgRect(UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoriesView)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnMove(UINT nIDMoveCommand);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCategoriesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCategoriesView)
	afx_msg void OnPaint();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DaoView.cpp
inline CMSDIDaoDoc* CCategoriesView::GetDocument()
   { return (CMSDIDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
