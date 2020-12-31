// ex32bView.h : interface of the CEx32bView class
//
/////////////////////////////////////////////////////////////////////////////

#include "valform.h"

class CEx32bCntrItem;

class CEx32bView : public CValidForm
{
protected: // create from serialization only
	CEx32bView();
	DECLARE_DYNCREATE(CEx32bView)

public:
	//{{AFX_DATA(CEx32bView)
	enum { IDD = IDD_EX32B_FORM };
	double	m_dHours;
	CString	m_strEmployee;
	int		m_nJob;
	int		m_nPeriod;
	//}}AFX_DATA

// Attributes
public:
	CEx32bDoc* GetDocument();
	// m_pSelection holds the selection to the current CEx32bCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CEx32bCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CEx32bCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
    virtual void ValidateDlgItem(CDataExchange* pDX, UINT ID);
	//{{AFX_VIRTUAL(CEx32bView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx32bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx32bView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnCancel();
	afx_msg void OnSubmit();
	afx_msg void OnServerAddress();
	afx_msg LONG OnPostComplete(UINT wParam, LONG lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex32bView.cpp
inline CEx32bDoc* CEx32bView::GetDocument()
   { return (CEx32bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
