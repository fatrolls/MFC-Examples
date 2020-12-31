#ifndef _DLGBASIC_H_
#define _DLGBASIC_H_

#include "BtnST.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgBasic : public CDialog
{
public:
	CDlgBasic(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlgBasic)
	enum { IDD = IDD_BASIC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBasic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBasic)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDisabled();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void OnCancel();
	void OnOK();

	CButtonST	m_btnStandard;
	CButtonST	m_btnHalloween;
	CButtonST	m_btnKeyManager;
	CButtonST	m_btnDisabled;
	CButtonST	m_btnLamp;
	CButtonST	m_btnZip;
	CButtonST	m_btnJpeg;
	CButtonST	m_btnCDRom;
	CButtonST	m_btnTooltip;
	CButtonST	m_btnSearch;
	CButtonST	m_btnBack;
	CButtonST	m_btnNext;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
