// ScrollSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScrollSettingsDlg dialog

class CScrollSettingsDlg : public CDialog
{
// Construction
public:
	CScrollSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollSettingsDlg)
	enum { IDD = IDD_SCROLL_SETTINGS };
	CString	m_sHorizontalMask;
	BOOL	m_bHorizontalPageAlign;
	BOOL	m_bHorizontalTop;
	BOOL	m_bVerticalLeft;
	CString	m_sVerticalMask;
	BOOL	m_bVerticalPageAlign;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScrollSettingsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
