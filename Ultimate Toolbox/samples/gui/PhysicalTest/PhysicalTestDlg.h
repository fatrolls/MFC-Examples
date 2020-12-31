// PhysicalTestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhysicalTestDlg dialog

#include "OXPhysicalEditEx.h"

class CPhysicalTestDlg : public CDialog
{
// Construction
public:
	CPhysicalTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPhysicalTestDlg)
	enum { IDD = IDD_PHYSICALTEST_DIALOG };
	CComboBox	m_wndTimeList;
	CComboBox	m_wndTempList;
	CComboBox	m_wndLengthList;
	CComboBox	m_wndAngleList;
	COXTempEdit	m_wndTemp;
	COXTimeEdit	m_wndTime;
	COXLengthEdit	m_wndLength;
	COXAngleEdit	m_wndAngle;
	double	m_dConvertedAngle;
	double	m_dConvertedLength;
	double	m_dConvertedTemp;
	double	m_dConvertedTime;
	//}}AFX_DATA
	double	m_dConvAngle;
	double	m_dConvLength;
	double	m_dConvTemp;
	double	m_dConvTime;
	int		m_nNeededConvAngle;
	int		m_nNeededConvLength;
	int		m_nNeededConvTemp;
	int		m_nNeededConvTime;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhysicalTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPhysicalTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvertAngle();
	afx_msg void OnConvertLength();
	afx_msg void OnConvertTemperature();
	afx_msg void OnConvertTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
