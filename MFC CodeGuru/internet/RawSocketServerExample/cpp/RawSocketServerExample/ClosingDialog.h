// ClosingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClosingDialog dialog
#define FINISHClosingDialog (WM_USER + 120)
class CClosingDialog : public CDialog
{
// Construction
public:
	CClosingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClosingDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClosingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClosingDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LONG OnFinishClosingDialog (UINT,LONG);
	DECLARE_MESSAGE_MAP()
};
