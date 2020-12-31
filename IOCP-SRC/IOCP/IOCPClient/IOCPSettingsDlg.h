#if !defined(AFX_IOCPSETTINGSDLG_H__2741F4E9_D544_4F00_8E14_F4265DE3895E__INCLUDED_)
#define AFX_IOCPSETTINGSDLG_H__2741F4E9_D544_4F00_8E14_F4265DE3895E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOCPSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IOCPSettingsDlg dialog

class IOCPSettingsDlg : public CDialog
{
// Construction
public:
	IOCPSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IOCPSettingsDlg)
	enum { IDD = IDD_SETTINGS };
	int		m_iMaxNumberOfConnections;
	int		m_iMaxNrOfFreeBuff;
	int		m_iMaxNrOfFreeContext;
	int		m_iNrOfIOWorkers;
	int		m_iNrOfLogicalWorkers;
	int		m_iPortNr;
	BOOL	m_bReadInOrder;
	BOOL	m_iSendInOrder;
	int		m_iNrPendlingReads;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IOCPSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IOCPSettingsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCPSETTINGSDLG_H__2741F4E9_D544_4F00_8E14_F4265DE3895E__INCLUDED_)
