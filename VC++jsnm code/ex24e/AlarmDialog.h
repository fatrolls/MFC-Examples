#ifndef __ALARMDIALOG_H__
#define __ALARMDIALOG_H__

// AlarmDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog dialog

class CAlarmDialog : public CDialog
{
// Construction
public:
	CAlarmDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmDialog)
	enum { IDD = IDD_ALARMDLG };
	int		m_nHours;
	int		m_nMinutes;
	int		m_nSeconds;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __ALARMDIALOG_H__
