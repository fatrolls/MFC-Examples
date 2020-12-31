// example.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExample dialog
#include "oxrollup.h"
#include "resource.h"

class CExample : public COXRollup
{
// Construction
public:
	CExample(CWnd* pParent = NULL);   // standard constructor
	// overridden from base class
	LPCTSTR GetTitleBarBitmap() { return _T("TITLEBAR_BMP"); }

// Dialog Data
	//{{AFX_DATA(CExample)
	enum { IDD = ID_EXAMPLE };
	CString	m_strTestEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExample)
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
