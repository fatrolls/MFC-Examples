#ifndef _DLGSHADEBUTTONST_H_
#define _DLGSHADEBUTTONST_H_

#include "BtnST.h"
#include "ShadeButtonST.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgShadeButtonST : public CDialog
{
public:
	CDlgShadeButtonST(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlgShadeButtonST)
	enum { IDD = IDD_SHADED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShadeButtonST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgShadeButtonST)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

private:
	void OnCancel();
	void OnOK();

	CShadeButtonST	m_btnButtons[9];

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
