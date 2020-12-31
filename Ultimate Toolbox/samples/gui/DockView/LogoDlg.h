// LogoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoDlg dialog

#include "OXSizeDlgBar.h"
#include "OXBitMapButton.h"

class CLogoDlg : public COXSizeDialogBar
{
// Construction
public:
	CLogoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogoDlg)
	enum { IDD = IDD_DIALOGBAR3 };
	COXBitmapButton	m_LogoButton;
	//}}AFX_DATA

	BOOL Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogoDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnOxbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
