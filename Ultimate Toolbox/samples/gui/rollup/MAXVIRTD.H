// maxvirtd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaxVirtDialog dialog
#include "oxrollup.h"

class CMaxVirtDialog : public COXRollup
{
protected:
	virtual void OnCloseRollup();
	virtual void PostNcDestroy();
	
public:
	virtual void GetTitleBarRect(CRect &rcTBarRect);
	virtual LPCTSTR GetTitleBarBitmap();

// Construction
public:
	CMaxVirtDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaxVirtDialog)
	enum { IDD = ID_OVERLOAD_MAX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaxVirtDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaxVirtDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
