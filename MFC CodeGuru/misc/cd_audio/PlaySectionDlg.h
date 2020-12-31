// PlaySectionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlaySectionDlg dialog

class CPlaySectionDlg : public CDialog
{
// Construction
public:
	CPlaySectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlaySectionDlg)
	enum { IDD = IDD_PLAYSECTION_DIALOG };
	BYTE	m_nFrameFrom;
	BYTE	m_nFrameTo;
	BYTE	m_nMinuteFrom;
	BYTE	m_nMinuteTo;
	BYTE	m_nSecondFrom;
	BYTE	m_nSecondTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaySectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaySectionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
