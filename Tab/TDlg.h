#pragma once
#include "afxcmn.h"


// CTDlg dialog

class CTDlg : public CDialog
{
	DECLARE_DYNAMIC(CTDlg)

public:
	CTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static CTabCtrl m_tab;
};
