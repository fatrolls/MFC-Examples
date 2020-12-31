// dtsetDlg.h : header file
//

#include "dtime.h"

/////////////////////////////////////////////////////////////////////////////
// CDTSetDlg dialog

class CDTSetDlg : public CDialog
{
// Construction
public:
	CDTSetDlg(CWnd* pParent = NULL);	// standard constructor

  void LoadSettings();
  void SaveSettings();

// Dialog Data
	//{{AFX_DATA(CDTSetDlg)
	enum { IDD = IDD_DTSET };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

  CDateControl m_ctrlJulianEnd;
  CDateControl m_ctrlGregorianBegin;
  CDate m_JulianEnd;
  CDate m_GregorianBegin;
  int m_BeginDayOfWeek;
  CString m_sCDateFormat;
  CString m_sCLDateFormat;
  CString m_sCLTimeSpanFormat;
  CString m_sCLTimeOfDayFormat;

	// Generated message map functions
	//{{AFX_MSG(CDTSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeCDateFormat();
	afx_msg void OnChangeCLDateFormat();
	afx_msg void OnChangeCLTimeOfDayFormat();
	afx_msg void OnChangeCLTimeSpanFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
