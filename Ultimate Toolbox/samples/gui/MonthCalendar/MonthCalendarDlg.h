// MonthCalendarDlg.h : header file
//

#if !defined(AFX_MONTHCALENDARDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_)
#define AFX_MONTHCALENDARDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXMonthCalCtrl.h"
#include "OXColorPickerButton.h"
#include "OXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CMonthCalendarDlg dialog

class CMonthCalendarDlg : public CDialog
{
// Construction
public:
	CMonthCalendarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMonthCalendarDlg)
	enum { IDD = IDD_MONTHCALENDAR_DIALOG };
	COXStatic	m_ctlFontName;
	CComboBox	m_cmbFirstDay;
	CComboBox	m_cmbDimension;
	COXColorPickerButton	m_btnClrTrailingText;
	COXColorPickerButton	m_btnClrTitleText;
	COXColorPickerButton	m_btnClrTitleBk;
	COXColorPickerButton	m_btnClrText;
	COXColorPickerButton	m_btnClrMonthBk;
	COXColorPickerButton	m_btnClrBk;
	BOOL	m_bBoldHolidays;
	BOOL	m_bDayState;
	BOOL	m_bMultiselect;
	BOOL	m_bNotoday;
	BOOL	m_bNotodaycircle;
	BOOL	m_bWeeknumbers;
	int		m_nMaxSel;
	int		m_nScrollRate;
	int		m_nFirstDay;
	int		m_nDimension;
	CString	m_sSelection;
	CString	m_sRangeFrom;
	CString	m_sRangeTo;
	BOOL	m_bInfoTip;
	CString	m_sFontName;
	//}}AFX_DATA
	COLORREF	m_clrTrailingText;
	COLORREF	m_clrTitleText;
	COLORREF	m_clrTitleBk;
	COLORREF	m_clrText;
	COLORREF	m_clrMonthBk;
	COLORREF	m_clrBk;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonthCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	LOGFONT m_lfText;

	COXMonthCalCtrl m_ctlMonthCal;

	void GetVars();
	void GetLatestSelInfo();
	void SetVars();

	int ConvertPointToLogUnit(const int nPointSize, CDC* pDC=NULL);
	int ConvertLogUnitToPoint(const int nLogUnitSize, CDC* pDC=NULL);

	// Generated message map functions
	//{{AFX_MSG(CMonthCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnApply();
	afx_msg void OnRestore();
	afx_msg void OnButtonFontname();
	//}}AFX_MSG
	void OnSelChange(NMHDR *pHdr, LRESULT *pRes);
	void OnSelect(NMHDR *pHdr, LRESULT *pRes);
	void OnGetDayState(NMHDR *pHdr, LRESULT *pRes);
	void OnOXGetDayState(NMHDR *pHdr, LRESULT *pRes);
	void OnOXGetInfoTip(NMHDR *pHdr, LRESULT *pRes);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTHCALENDARDLG_H__3F275489_255F_11D2_889C_0080C83F712F__INCLUDED_)
