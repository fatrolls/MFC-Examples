// StaticHyperLinkDlg.h : header file
//

#include "CustomizableStaticHyperLink.h"
#include "CustomizableStatic.h"

#if !defined(AFX_STATICHYPERLINKDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_STATICHYPERLINKDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CStaticHyperLinkDlg dialog

class CStaticHyperLinkDlg : public CDialog
{
// Construction
public:
	CStaticHyperLinkDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStaticHyperLinkDlg)
	enum { IDD = IDD_STATICHYPERLINK_DIALOG };
	CCustomizableStatic				m_ctlStaticHint;
	CCustomizableStatic				m_ctlStaticSampleCaption;
	CCustomizableStaticHyperLink	m_ctlStaticSolitaire;
	CCustomizableStaticHyperLink	m_ctlStaticWebUT;
	CCustomizableStaticHyperLink	m_ctlStaticWebDundas;
	CCustomizableStaticHyperLink	m_ctlStaticFax;
	CCustomizableStaticHyperLink	m_ctlStaticEmailSales;
	CCustomizableStaticHyperLink	m_ctlStaticEmailAndrei;
	CCustomizableStaticHyperLink	m_ctlStaticClose;
	CCustomizableStaticHyperLink	m_ctlStaticBillGates;
	CCustomizableStaticHyperLink	m_ctlStaticAbout;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticHyperLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStaticHyperLinkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg LONG OnAboutActivated(UINT wParam, LONG lParam);
	afx_msg LONG OnCloseActivated(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticEmailAndrei();
	afx_msg void OnStnClickedStaticFax();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICHYPERLINKDLG_H__ED8354A8_AC60_11D1_A3D5_0080C83F712F__INCLUDED_)
