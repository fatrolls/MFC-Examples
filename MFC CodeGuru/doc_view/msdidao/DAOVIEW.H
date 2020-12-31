// DoaView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMSDIDaoView : public CFormView
{
protected:
	CMSDIDaoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMSDIDaoView)

// Form Data
public:
	//{{AFX_DATA(CMSDIDaoView)
	enum { IDD = IDD_DATABASE_FORM };
	CString m_strName;
	CString m_strVersion;
	//}}AFX_DATA

// Attributes
public:
	CMSDIDaoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDIDaoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMSDIDaoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMSDIDaoView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DaoView.cpp
inline CMSDIDaoDoc* CMSDIDaoView::GetDocument()
   { return (CMSDIDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
