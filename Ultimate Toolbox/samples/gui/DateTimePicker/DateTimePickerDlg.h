// DateTimePickerDlg.h : header file
//

#if !defined(AFX_DATETIMEPICKERDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_)
#define AFX_DATETIMEPICKERDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDateTimeCtrl.h"
#include "OXColorPickerButton.h"
#include "OXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CDateTimePickerDlg dialog

class CDateTimePickerDlg : public CDialog
{
// Construction
public:
	CDateTimePickerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDateTimePickerDlg)
	enum { IDD = IDD_DATETIMEPICKER_DIALOG };
	CComboBox	m_cmbTimeFormat;
	CComboBox	m_cmbDateFormat;
	COXStatic	m_ctlMonthCalFontName;
	CComboBox	m_cmbFirstDay;
	CComboBox	m_cmbDimension;
	COXColorPickerButton	m_btnClrTrailingText;
	COXColorPickerButton	m_btnClrTitleText;
	COXColorPickerButton	m_btnClrTitleBk;
	COXColorPickerButton	m_btnClrText;
	COXColorPickerButton	m_btnClrMonthBk;
	COXColorPickerButton	m_btnClrBk;
	int		m_nFirstDay;
	int		m_nDimension;
	int		m_nScrollRate;
	BOOL	m_bCanParse;
	BOOL	m_bShowNone;
	BOOL	m_bUpDown;
	int		m_nFormat;
	BOOL	m_bRightAlign;
	BOOL	m_bNotoday;
	BOOL	m_bNotodaycircle;
	BOOL	m_bWeeknumbers;
	CString	m_sMonthCalFontName;
	int		m_nDateFormat;
	int		m_nTimeFormat;
	//}}AFX_DATA
	COLORREF	m_clrTrailingText;
	COLORREF	m_clrTitleText;
	COLORREF	m_clrTitleBk;
	COLORREF	m_clrText;
	COLORREF	m_clrMonthBk;
	COLORREF	m_clrBk;

	LOGFONT m_lfMonthCal;
	LOGFONT m_lfDateTimePicker;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimePickerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	COXDateTimeCtrl m_ctlDateTimePicker;

	void GetVars();
	void SetMonthCalColors();
	BOOL RecreateDateTimePicker(DWORD dwAddStyle, DWORD dwRemoveStyle);
	void SetDateFormat();
	void SetTimeFormat();

	int ConvertPointToLogUnit(const int nPointSize, CDC* pDC=NULL);
	int ConvertLogUnitToPoint(const int nLogUnitSize, CDC* pDC=NULL);

	// Generated message map functions
	//{{AFX_MSG(CDateTimePickerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckCanparse();
	afx_msg void OnCheckShownone();
	afx_msg void OnCheckUpdown();
	afx_msg void OnRadioFormat();
	afx_msg void OnCheckRightalign();
	afx_msg void OnButtonCalfont();
	afx_msg void OnSelchangeComboDateformat();
	afx_msg void OnSelchangeComboTimeformat();
	//}}AFX_MSG
	afx_msg void OnDTDropDown(NMHDR *pHdr, LRESULT *pRes);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMEPICKERDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_)
