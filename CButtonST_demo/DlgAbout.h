#ifndef _DLGABOUT_H_
#define _DLGABOUT_H_

#include "BtnST.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgAbout : public CDialog
{
public:
	CDlgAbout(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAbout)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

private:
	void OnCancel();
	void OnOK();

	CButtonST	m_btnSTLogo;
	CButtonST	m_btnFace;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
